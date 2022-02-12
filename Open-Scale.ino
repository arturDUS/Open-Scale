//////////////////////////////////////////////////////////////////////////////////////
// Version with WEBSOCKETS
// Von: https://randomnerdtutorials.com/esp8266-nodemcu-websocket-server-arduino/
//////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "HX711.h"              // Loadcell library
#include "EEPROM.h"             // Used to store configuration and recipe in flash
#include "OLEDDisplayUi.h"      // Include the UI lib
#include <ESP8266WiFi.h>        // Load Wi-Fi library
#include <Arduino_JSON.h>       // Process JSON Objects

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define MAX_ANZ_DISPLAY_ZEICHEN 7   // Maximale Anzahl an Zeichen die beim Editieren im Display angezeigt werden können

// Load images
#include "images.h"
// Zeichebsatz
#include "font.h"
// Menuetexte
#include "Menu.h"

////////////////////////////////////
// Website
#include "index.h"
////////////////////////////////////

// Klassen definieren
// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h
OLEDDisplayUi ui     ( &display );

// LoadCell Sensor einrichten:
HX711 scale;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 0;
const int LOADCELL_SCK_PIN = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// EEPROM Daten / Konfigurationswerte
//////////////////////////////////////////////////////////////////////////
// Waagensettings
// Werden die Settings erweitert(zusätzliches Feld) muss im Startup der Identifier geändert werden damit einmalig die Standradkonfiguration gesetzt wird!
typedef struct {
  char ConfState[4];                      // Config State in EPROM: if not "SeT\0", write default values to EPROM
  char Name[16] = "\0";         // Name der Waage
  char WiFiSSID[32]="\0";           // WiFi SSID
  char IP[15];                            // Static WiFi IP Adress when connecting as Client to WiFi
  char APIP[15]="\0";                     // IP address in accesspoint mode  https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
  char APgateway[15]="\0";     // gateway Ip address in accesspoint mode
  char APsubnetmask[15]="\0";// subnet mask in accesspoint mode
  char WiFiPWD[32]="\0";  // WiFi Passwort in Clientmode
  uint8_t WiFiMode=0;                   // 0:Wifi not configured, 1:Wifi disabled on startup, 2: 1:Connect to existing WiFi, 2:Accesspoint mode
  uint8_t Defaultmode=0;                // Default Mode to start with (0: Standard weighing, 1: Component weighing, 2:Count scale, 3:Check scale)
  float ScaleMaxRange=0;
  float ScaleSteps=0.1;
  float ScaleTolerance=10;
  char Unit[5] = "g\0";
  float Kalibrierwert;                  // Wird nur für die Kalibrierung benötigt
} TSettings;                            // Länge
TSettings settings;                     // Gesamtlänge: 193 Byte ACHTUNG! Maximal 255Byte!!

//////////////////////////////////////////////////////////////////////////
// Rezepte für z.B. Epoxymischverhältnisse oder einfache chemische Verbindungen
typedef struct {
  char Name[20] ="Rezeptname Small\0";  // Rezeptname
  int Nummer = 0;                 // Rezeptnummer [0..10]
  int Anzahl_Komponenten = 0;     // Anzahl der Komponennten [1..10]
  float K1 = 0;                   // Gewicht Komponennte 1
  char K1_Name[25];
  float K2 = 0;                   // Gewicht Komponennte 2
  char K2_Name[25];
  float K3 = 0;                   // Gewicht Komponennte 3
  char K3_Name[25];
  float wiegetoleranz = 5;        // wiegetoleranz um den Sollwert +/-
} TRezept_Small;          
TRezept_Small rezept_small[5];    // Gesamtlänge: 640 Byte

// Rezepte für z.B. Gewürzmischungen oder komplexe chemische Verbindungen
typedef struct {
  char Name[20] ="Rezeptname Big\0";  // Rezeptname
  int Nummer = 0;                 // Rezeptnummer [0..10]
  int Anzahl_Komponenten = 0;     // Anzahl der Komponennten [1..10]
  float K1 = 0;                   // Gewicht Komponennte 1
  char K1_Name[25];
  float K2 = 0;                   // Gewicht Komponennte 2
  char K2_Name[25];
  float K3 = 0;                   // Gewicht Komponennte 3
  char K3_Name[25];
  float K4 = 0;                   // Gewicht Komponennte 4
  char K4_Name[25];
  float K5 = 0;                   // Gewicht Komponennte 5
  char K5_Name[25];
  float K6 = 0;                   // Gewicht Komponennte 6
  char K6_Name[25];
  float K7 = 0;                   // Gewicht Komponennte 7
  char K7_Name[25];
  float K8 = 0;                   // Gewicht Komponennte 8
  char K8_Name[25];
  float K9 = 0;                   // Gewicht Komponennte 9
  char K9_Name[25];
  float K10 = 0;                  // Gewicht Komponennte 10
  char K10_Name[25];
  float wiegetoleranz = 5;        // wiegetoleranz um den Sollwert +/-
} TRezept_Big;          
TRezept_Big rezept_big[3];        // Gesamtlänge: 1056 Byte

//////////////////////////////////////////////////////////////////////////
// Scale mode
enum WIEGEMOD
{ STDWAAGE,   // Simple weighing function with gross weighing
  REZEPT,     // A recipe drven component weighing of 1 to 8 components
  STUECKZAEHL, // Count scale: Count parts depending on theire specific wight
  CHECK       // Check scale: Check if weight is within defined borders
} modus;

//////////////////////////////////////////////////////////////////////////
// Enummeration um die Rückmeldung aus der Webseite weiter zu verarbeiten
enum WEBCMD
{ NOTHING,
  TARE, 
  CALIBRATE
} WebCmd;

//////////////////////////////////////////////////////////////////////////
// Enummeration for WiFi Status
enum WIFIStatus
{ DISABLED,
  ENABLED, 
  CONNECTED,
  WEBSERVERACTIVE,
  CLIENTCONNECTED
} WiFiStatus;

//////////////////////////////////////////////////////////////////////////
// Globale Variablen
float SollWert;
float IstWert;
float Toleranz;
float MaxWert;

struct sWIFIDATA {
  float Actual;      // Scale reading (after taring)
  float Set;         // Target value for weighing
  float Tolerance;   // Tolerance value for the actual weighing
  float MaxWeighing; // The maximum weighing value of the scale
  uint8_t Button;    // Pressed Button on the scale
  uint8_t Mode;      // The current weighing mode
} value;

//////////////////////////////////////////////////////////////////////////
// Funktionsprototypen
int8_t getkey(void);  // Ließt den AD-Wandler aus und gibt zurück welche Taste gedrückt wurde. (Über Spannungsteiler)
void ReadSettings(void);
void WriteSettings(void);
void KalibrierMenu(void);
void drawWeighingBar(int posy, float min, float max, float akt);
void RangeBar(int posy, float min, float max, float akt);
float EnterValue(char x, char y, float NumberMin, float NumberMax, char d, float v, String Beschreibung);
uint8_t ConfigMenu(uint8_t s);
void CheckWiFi(void);
void startAPMode(void);
void SendConfigToClient(void);
void SetDefaultConfig(void);

//////////////////////////////////////////////////////////////////////////
// Webserver Funktionen
void notifyClients();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len);
void initWebSocket();
String processor(const String& var);
             

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void setup() {
  long t;

  value.Actual = 0;
  value.Set = 1000;
  value.Tolerance = 5;
  value.MaxWeighing = 1000;
  value.Button = 0;
  value.Mode = 0;
  
  Serial.begin(115200);

  // Initialising the UI will init the display too.
  display.init();

  // Waagensensor konfigurieren und starten
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  display.flipScreenVertically();

  display.setTextAlignment(TEXT_ALIGN_LEFT);

  if (scale.wait_ready_timeout(1000)) {
  } else {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(10, 16, "HX711 FEHLER!");
    display.setFont(ArialMT_Plain_10);
    display.drawString(10, 36, "Weiter mit Taste");
    display.display();
    while(getkey()==0) delay(50);
  }

  // Konfiguration aus EEPROM Auslesen. Wenn initial dann die Standard Konfiguration laden
  ReadSettings();
  if(strcmp(settings.ConfState, "V01")!=0)    // Der Wert muss bei jeder Konfigurationserweiterung (zusätzliches Feld) geändert werden!!!!!!!!!
  {  SetDefaultConfig();                      // Defaultwerte setzen
     strcpy(settings.ConfState, "V01\0");
     ConfigMenu(1);                           // Konfigurationsmenü aufrufen
     WriteSettings();                         // Konfiguration in das EPROM schreiben
     Serial.println("Standradkonfiguration gespeichert!");
  }
  
  scale.set_scale(settings.Kalibrierwert);  // Kalibrierwert auslesen

  display.clear();
  display.drawXbm(5, 5, Splash_width, Splash_height, Splash);
  display.display();
  // Enable WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(settings.WiFiSSID, settings.WiFiPWD);   // Start WifiMode
  WiFiStatus = ENABLED;                              // Wifi is enabled
  // Show Splash for 1 seconds
  while(getkey()!=0) delay(100);
  t = millis() + 1000;
  while( t> millis() && getkey()==0){
    delay(100);
  }
  // Tare the scale
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(10, 20, "Tarieren");
  display.display();
  scale.tare();   // Execute the scale tareing

}

void CheckWiFi(){
  String temp;
  
  if(WiFi.status() != WL_CONNECTED)
  { WiFiStatus = ENABLED; 
  } else
  { if(WiFiStatus < CONNECTED) {
      temp = WiFi.localIP().toString();
      Serial.print("WiFi connected. Scale IP-Address: "); Serial.println(temp);
      strcpy(settings.IP, temp.c_str());
      initWebSocket();
      // Route for root / web page
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
      });
      // Start webserver
      server.begin();
      WiFiStatus = WEBSERVERACTIVE;
    } else {
      // Webanfragen beantworten
      ws.cleanupClients();
      // If something has changed, that has to be transmitted
      notifyClients();
    }
  } 
}

void loop() {
  long int r;
  float G, oldG;
  int8_t t;  // Taste die gedrückt wurde

  r = scale.get_units(2); //scale.get_value(5); //scale.read();  // Waage auslesen
  G = r;
  G/=10;
  value.Actual = G;  // Aktuell gelesenes Gewicht als globales Gewicht auf Webseite anzeigen

  CheckWiFi(); // Checks if WiFi is available

  // Displayanzeige aktualisieren
  display.clear();
  drawWeighingBar(15, 0, 1000, G);
  display.setFont(ArialMT_Plain_24);
  display.drawString(115, 35, "g"); 
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.setFont(Roboto_Slab_Bold_34);      // display.setFont(DSEG7_Modern_Bold_30);    //display.setFont(ArialMT_Plain_24);
  display.drawString(110, 26, String(G,1));
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  // write the buffer to the display
  display.display();

  // Tasten auswerten
  t = getkey();
  switch (t)
  { case -1:  // Tare / Tarieren beim kurzen Tastendruck loslassen
      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 30, "TARIEREN");
      display.display();
      scale.tare();
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break; 
    case 11:
      ConfigMenu(3);   // Configuration / Konfiguration
      break;
    case 12:
      break;
    case 13:
      break;
    case 14:
      break; 
    default:
      break;
  }

  // ein Webkommando auswählen
  switch(WebCmd)
  { case TARE:
      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 30, "TARIEREN");
      display.display();
      scale.tare();
      break;
    case CALIBRATE:
      // KalibrierMenu();  
      break;
    default:
      break;
  }
  WebCmd = NOTHING;
  
  delay(100);
}


void notifyClients() {
  static sWIFIDATA oldvalue;
  char S[40];
  JSONVar myObject;
  
  // Check is something has changed
  if(value.Actual != oldvalue.Actual ||
     value.Set != oldvalue.Set ||
     value.Tolerance != oldvalue.Tolerance ||
     value.MaxWeighing != oldvalue.MaxWeighing ||
     value.Button != oldvalue.Button ||
     value.Mode != oldvalue.Mode) {

      // Store the new value
      oldvalue.Actual = value.Actual;
      oldvalue.Set = value.Set;
      oldvalue.Tolerance = value.Tolerance;
      oldvalue.MaxWeighing = value.MaxWeighing;
      oldvalue.Button = value.Button;
      oldvalue.Mode = value.Mode; 

      // Prepare the JSON String
      myObject["Type"] = "ACTUALS";
      dtostrf(value.Actual, 4, 1, S);
      myObject["IstWert"] = S;
      dtostrf(value.Set, 4, 1, S);
      myObject["SollWert"] = S;
      dtostrf(value.Tolerance, 4, 1, S);
      myObject["Toleranz"] = S;
      dtostrf(value.MaxWeighing, 4, 1, S);
      myObject["MaxWert"] = S; 
      myObject["Button"] = value.Button;
      myObject["Mode"] = value.Mode; 

      // Send the JSON String
      String jsonString = JSON.stringify(myObject);
      ws.textAll(jsonString); 
     }
}

void SendConfigToClient() {
  char S[40];
  JSONVar myObject;

  myObject["Type"] = "CONFIG";
  myObject["Name"] = settings.Name;
  myObject["SSID"] = settings.WiFiSSID;
  myObject["APIP"] = settings.APIP;
  myObject["APgateway"] = settings.APgateway;
  myObject["APsubnetmask"] = settings.APsubnetmask;
  myObject["PWD"] = ""; //settings.WiFiPWD;  // Das Passwort wird nicht an den Clienten geschickt. Passwort wird nur in eine Richtugn ausgetauscht!
  myObject["WiFiMode"] = settings.WiFiMode;
  myObject["Defaultmode"] = settings.Defaultmode;
  myObject["IP"] = "";
  dtostrf(settings.ScaleMaxRange, 4, 1, S);
    myObject["ScaleMaxRange"] = S;
  dtostrf(settings.ScaleSteps, 4, 1, S);
    myObject["ScaleSteps"] = S;
  dtostrf(settings.ScaleTolerance, 4, 1, S);
    myObject["ScaleTolerance"] = S;
  myObject["ScaleUnit"] = settings.Unit;

  // Send the JSON String
  String jsonString = JSON.stringify(myObject);
  Serial.print("Config gesendet an Clienten: "); Serial.println(jsonString);
  ws.textAll(jsonString);
}

void SendConfigOK() {
  char S[40];
  JSONVar myObject;

  myObject["Type"] = "CONDIF_SAVE_OK";
  myObject["ReturnCode"] = 0;
  // Send the JSON String
  String jsonString = JSON.stringify(myObject);
  ws.textAll(jsonString);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = '\0';
    Serial.print("Länge Antwort:"); Serial.println(len);
    Serial.print("Inhalt:"); Serial.println((char*)data);
    if (strcmp((char*)data, "tare") == 0) {
      WebCmd = TARE;
      //notifyClients();
    } else if (strcmp((char*)data, "cali") == 0) {
      WebCmd = CALIBRATE;
    } else {
      // Schauen ob es ein JSON-String ist
       JSONVar myObject = JSON.parse((char *)data);
       if(myObject.hasOwnProperty("Type")) {
         if(strcmp((const char*) myObject["Type"], "CONFIG") == 0) {
          // Es ist ein JSON-String der die configuration enthaält.
          if (myObject.hasOwnProperty("Name")) {strcpy(settings.Name, (const char*)myObject["Name"]);};
          if (myObject.hasOwnProperty("SSID")) {strcpy(settings.WiFiSSID, (const char*)myObject["SSID"]); };
          if (myObject.hasOwnProperty("APIP")) {strcpy(settings.APIP, (const char*)myObject["APIP"]);  };
          if (myObject.hasOwnProperty("APgateway")) {strcpy(settings.APgateway, (const char*)myObject["APgateway"]);  };
          if (myObject.hasOwnProperty("APsubnetmask")) {strcpy(settings.APsubnetmask, (const char*)myObject["APsubnetmask"]);  };
          if (myObject.hasOwnProperty("PWD")) {
            char pwd[32];
            strcpy(pwd, (const char*)myObject["PWD"]);
            if(strlen(pwd) > 4) {
              // Es wurde ein neues Passwort empfangen
              strcpy(settings.WiFiPWD, pwd);
              Serial.print("Neues WiFi-Passwort gesetzt: "); Serial.println(pwd);
              }
            };
          if (myObject.hasOwnProperty("WiFiMode")) {settings.WiFiMode = (int)myObject["WiFiMode"];};
          if (myObject.hasOwnProperty("Defaultmode")) {settings.Defaultmode = (int)myObject["Defaultmode"];};
          if (myObject.hasOwnProperty("ScaleMaxRange")) {settings.ScaleMaxRange = atof(myObject["ScaleMaxRange"]);};
          if (myObject.hasOwnProperty("ScaleSteps")) {settings.ScaleSteps = atof(myObject["ScaleSteps"]);};
          if (myObject.hasOwnProperty("ScaleTolerance")) {settings.ScaleTolerance = atof(myObject["ScaleTolerance"]);};  
          if (myObject.hasOwnProperty("ScaleUnit")) {strcpy(settings.Unit, (const char*)myObject["ScaleUnit"]);};        
          WriteSettings();  // Konfiguration in das EEPROm schreiben
          SendConfigOK();   // Zurückmelden das die Konfiguration erfolgreich gespeichert wurde.
         }
       }  
    }
  }
}

// Loads the default values
void SetDefaultConfig(void) {
  strcpy(settings.Name, "OpenScale\0");             // Will also be used as SSID if scale is in AP-Mode
  strcpy(settings.WiFiSSID, "\0");
  strcpy(settings.APIP, "192.168.1.4\0");
  strcpy(settings.APgateway, "192.168.1.1\0");
  strcpy(settings.APsubnetmask, "255.255.255.0\0"); 
  strcpy(settings.WiFiPWD, "\0");                   // In AP Mode no password is required.
  settings.WiFiMode = 2;                            // Accesspoint Mode
  settings.Defaultmode = 0;                         // Standard Weighing
  settings.ScaleMaxRange = 1000;                    // 1000g Scale
  settings.ScaleSteps = 0.1;                        // 0.1g Steps
  settings.ScaleTolerance = 5;                      // Tolerance for weighing 5%
  strcpy(settings.Unit, "g\0");                     // Default Unit is g (gramms)
}

//////////////////////////////////////////////////////////////////////////////////
// Siehe: https://github.com/me-no-dev/ESPAsyncWebServer
// Unter dem Abschnitt "Async WebSocket Event"
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        SendConfigToClient(); // Den Clienten die Konfiguration mitteilen
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}


void startAPMode()
{ IPAddress local_IP;
  IPAddress gateway(192,168,4,9);
  IPAddress subnet(255,255,255,0);

  if(local_IP.fromString(settings.APIP)) {              // try to parse into the IPAddress
    Serial.print("Setting soft-AP configuration ... ");
    if(WiFi.softAPConfig(local_IP, gateway, subnet)){
      Serial.println("Ready");
      Serial.print("Setting soft-AP ... ");
      if(WiFi.softAP(settings.Name)){                   // The configured scale name will be the accesspoint name
        Serial.println("Ready");
        Serial.print("Soft-AP IP address = "); Serial.println(WiFi.softAPIP());
      } else {
        Serial.println("Failed!");
      }
    } else {
      Serial.println("Failed!");
    }
  } else {
    Serial.println("unparsable IP");
  }
}


void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    // Nothing
  }
  return String();
}

uint8_t ConfigMenu(uint8_t s)
{ int m_TL;   // oberste Zeile im Display
  int m_Akt;  // Aktuell ausgewähltes Menu

  uint8_t choice=0; // ausgewältes Menu
  int8_t StartIndex=0;
  int8_t AuswahlDisplay=0;
  int8_t AuswahlMenuItems=0;
  int8_t key=0;
  uint8_t p, i;
  String temp;

  while(choice==0)
  {  display.clear();
     display.setFont(ArialMT_Plain_10);
     display.drawString(0,0, "Konfiguration:");
     display.drawHorizontalLine(0, 11, 128);

    //StartIndex = (AuswahlMenuItems > 3) ? (AuswahlMenuItems - 3) : 0;    
    //AuswahlDisplay =  (AuswahlMenuItems > 3) ? 3 : AuswahlMenuItems;
    
     // Menutext anzeigen
    p = 13;                // Erste Y-Position
    for(i=0; i<4; i++) // 4 Zeilen können angezeigt werden
    { 
      if(i == AuswahlDisplay)
      { display.fillRect(8, p, 108, 12);
        display.setColor(BLACK);
        display.drawString(10, p, sConfigMenu[i+StartIndex]);  // Stelle i ausgeben 
        display.setColor(WHITE);
      } else
      { display.drawString(10, p, sConfigMenu[i+StartIndex]);  // Stelle i ausgeben
      }
      // Anwelcher Position kommt der nächste Menüeintrag?
      p=p+12;
    }

    // Tasten auswerten
    display.display();
    while(getkey()>0) delay(50); // Warten das die Taste losgelassen wird
    while((key=getkey()) == 0) delay(50);

    if(key==2){ // Runter
      // Auswahl in der Gesamtliste
      if(++AuswahlMenuItems > 10) AuswahlMenuItems=0; // Von Vorne anfangen   

      // Auswahl im Display
      if(AuswahlDisplay == 3){ // Ist aktuell die unterste Zeile markiert
        if((StartIndex+3) == 10){ // Der letzte Bereich wird bereits angezeit also an den Anfang springen
          StartIndex = 0;
          AuswahlDisplay = 0;
        } else{
          StartIndex++; 
        }
      } else{  // Nur den ausgewählen Menüeintrag verschieben
        AuswahlDisplay++;
      }      
    }
    
    if(key==3){ // Hoch
      // Auswahl in der Gesamtliste
      if(--AuswahlMenuItems < 0) AuswahlMenuItems=10; // Ans Ende springen 

      // Auswahl im Display
      if(--AuswahlDisplay < 0){ // Ist aktuell die obere Zeile markiert
        if(--StartIndex < 0){ // Wenn wir beim ersten Menüeintrag sind am Ende der Auswahl anfangen
          StartIndex = 10 - 3; // Anzahl Menueinträge minus Anzahl angezeigte Menüeinträge
          AuswahlDisplay = 3;
        } else {
          AuswahlDisplay = 0;
        } 
      } 
    }

    if(key==4){ // Blaue Taste: Auswahl
      switch(AuswahlMenuItems) {
        case 0: //Scale Name
          EnterText(6, 35, settings.Name, 15, "ABCDEFGHIJKLMNOPQRSTUVWabcdefghijklmnopqrstuvwxyz_", sConfigMenu[0]).toCharArray(settings.Name, 16);
        break;
        case 1: //Delault Mode
          settings.Defaultmode = ChoiceMenu(aConfigStdMode, 4, settings.Defaultmode, sConfigMenu[1]);
        break;
        case 2: //Wifi SSID
          EnterText(6, 35, settings.WiFiSSID, 31, "ABCDEFGHIJKLMNOPQRSTUVWabcdefghijklmnopqrstuvwxyz_", sConfigMenu[2]).toCharArray(settings.WiFiSSID, 32);
        break;
        case 3: //Wifi Passwort
          EnterText(6, 35, settings.WiFiPWD, 31, "1234567890ABCDEFGHIJKLMNOPQRSTUVWabcdefghijklmnopqrstuvwxyz _<>|,.;:-#'+*!$%&/()=?^°@~{}", sConfigMenu[3]).toCharArray(settings.WiFiPWD, 32);
        break;
        case 4: //AP-IP Adresse
          EnterText(6, 35, settings.APIP, 15, ".0123456789", sConfigMenu[4]).toCharArray(settings.APIP, 15);
        break;
        case 5: //WiFi Mode
          settings.WiFiMode = ChoiceMenu(sConfigWiFiModes, 3, settings.WiFiMode, sConfigMenu[5]);
        break;
        case 6: //Scale Max Range
          settings.ScaleMaxRange = EnterValue(0, 35, 0, 50000, 0, settings.ScaleMaxRange, sConfigMenu[6]);
        break;
        case 7: //Scale Steps
          settings.ScaleSteps = EnterValue(0, 35, 0.001, 10, 3, settings.ScaleSteps, sConfigMenu[7]);
        break;
        case 8: //Scale Tolerance
          settings.ScaleTolerance = EnterValue(0, 35, 0, 100, 1, settings.ScaleTolerance, sConfigMenu[8]);
        break;
        case 9: //Scale Unit
          EnterText(6, 35, settings.Unit, 3, "ABCDEFGHIJKLMNOPQRSTUVWabcdefghijklmnopqrstuvwxyz/", sConfigMenu[9]).toCharArray(settings.Unit, 5);
        break;
        case 10: // Scale Calibration
          KalibrierMenu();
        break;
        default:
        break;
      }
      
    }

    if(key==-1){ // kurzer roter Tastendruck (SAVE)
      WriteSettings(); // Werte speichern
      DisplaySaveOrCancel(1);
      return 0; // verlassen
    }

    if(key==11){ // Langer roter Tastendruck (CANCEL)
      DisplaySaveOrCancel(0);
      return 0; // verlassen ohne speichern
    }
  }
}

void DisplaySaveOrCancel(uint8_t s){
  long timeout=millis()+2000;
  
  display.clear();
  display.setFont(ArialMT_Plain_16);
  if(s==1){
    display.drawString(0, 10, "Erfolgreich");
    display.drawString(0, 30, "gespeichert!");
  } else {
    display.drawString(0, 0, "Änderungen");
    display.drawString(0, 20, "wurden");
    display.drawString(0, 40, "verworfen!");
  }
  display.display();
  
  while(getkey()>0 || millis()<timeout) delay(100); // Warten das die Taste losgelassen wird
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Stellt Radiobuttons dar
// Anz: Anzhal Einträge
// selected: selektierter Eintrag
uint8_t ChoiceMenu(const char(* List)[14], uint8_t Anz, uint8_t selected, String Beschreibung)
{ char back=0;            // 0: Editieren, 1:verwerfen und abbrechen, 2:speichern und übernehmen
  uint8_t sel, p, i=0;
  int8_t key;
  int8_t StartIndex=0;
  int8_t AuswahlDisplay=0;
  int8_t AuswahlMenuItems=0;
  int8_t selectedDisplayed;

  while(getkey()!=0) delay(100); // Warten das die Taste losgelassen wird

  sel = selected;
  
  // solange im Edit Modus bleiben bis zurück gegangen werden soll
  while(!back)
  { 
    // Überschrift ausgeben
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(0,0, Beschreibung);
    display.drawHorizontalLine(0, 11, 128);

    // Menutext anzeigen
    p = 13;                // Erste Y-Position
    for(i=0; i<((Anz>3)?4:Anz); i++) // 4 Zeilen können maximal angezeigt werden
    { 
      if(i == AuswahlDisplay)
      { display.fillRect(8, p, 108, 12);
        display.setColor(BLACK);
        display.drawString(25, p, List[i+StartIndex]);  // Stelle i ausgeben 
        display.drawCircle(15,p+5,5);
        if(i+StartIndex == sel){ // Punkt in den Radiobutton zeichnen
          display.fillCircle(15,p+5,3);
        }
        display.setColor(WHITE);
      } else
      { display.drawString(25, p, List[i+StartIndex]);  // Stelle i ausgeben
        display.drawCircle(15,p+5,5);
        if(i+StartIndex == sel){ // Punkt in den Radiobutton zeichnen
          display.fillCircle(15,p+5,3);
        }
      }
      // Anwelcher Position kommt der nächste Menüeintrag?
      p=p+12;
    }  

    // Tasten auswerten
    display.display();    
    while(getkey()>0) delay(50); // Warten das die Taste losgelassen wird
    while((key=getkey()) == 0) delay(50);

    if(key==2){ // Runter
      // Auswahl in der Gesamtliste
      if(++AuswahlMenuItems > Anz-1) AuswahlMenuItems=0; // Von Vorne anfangen   

      // Auswahl im Display
      if(AuswahlDisplay == ((Anz>3)?3:Anz-1)){ // Ist aktuell die unterste Zeile markiert
        if((StartIndex+((Anz>3)?3:Anz-1)) == Anz-1){ // Der letzte Bereich wird bereits angezeit also an den Anfang springen
          StartIndex = 0;
          AuswahlDisplay = 0;
        } else{
          StartIndex++; 
        }
      } else{  // Nur den ausgewählen Menüeintrag verschieben
        AuswahlDisplay++;
      }      
    }
    
    if(key==3){ // Hoch
      // Auswahl in der Gesamtliste
      if(--AuswahlMenuItems < 0) AuswahlMenuItems=9; // Ans Ende springen 

      // Auswahl im Display
      if(--AuswahlDisplay < 0){ // Ist aktuell die obere Zeile markiert
        if(--StartIndex < 0){ // Wenn wir beim ersten Menüeintrag sind am Ende der Auswahl anfangen
          StartIndex = ((Anz>4)?(Anz-4):0); // Anzahl Menueinträge minus Anzahl angezeigte Menüeinträge
          AuswahlDisplay = ((Anz>3)?3:Anz-1);
        } else {
          AuswahlDisplay = 0;
        } 
      } 
    }

    if(key==4){ // Blaue Taste: Auswahl
      sel = AuswahlMenuItems;
    }
    
    if(key==-1){ // kurzer roter Tastendruck (Übernehmen)
      return sel; // verlassen
    }

    if(key==11){ // Langer roter Tastendruck (Abbrechen)
      return selected; // verlassen ohne Änderung
    }
    
  }
  
}



/////////////////////////////////////////////////////////
// Stellt eine Funktion zur eingabe von Dezimalzahlen mit 4 Tastern bereit
// Parameter
// Position im Display (x,y)
// maximale länge des Strings: lMax
// aktueller String: t
// erlaubte Zeichen: ac
/////////////////////////////////////////////////////////
String EnterText(int x, int y, String t, uint8_t lMax, String ac, String Beschreibung)
{ char back=0;            // 0: Editieren, 1:verwerfen und abbrechen, 2:speichern und übernehmen
  int i, p;
  int8_t key;             // Tasten
  String T = t;           // Neuer, editierter Text
  int CursorPosDisplay=0; // Position des Cursors im Display 0..Maxmial anzeigbare Zeichen
  int CursorPosString=0;  // Position des Cursors im String 0..Maximale Stringlänge
  int StartIndex=0;       // Erstes Zeichen im Display
  int lString=0;          // Länge des aktuellen Strings
  
  while(getkey()!=0) delay(100); // Warten das die Taste losgelassen wird
  
  // solange im Edit Modus bleiben bis zurück gegangen werden soll
  while(!back)
  { // Überschrift ausgeben
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0,0, Beschreibung);
    display.drawHorizontalLine(0, 18, 128);
    display.setFont(DialogInput_plain_24);

    // Länge des aktuellen Strings ermitteln
    lString = T.length();

    // Erstes Zeichen das angeziegt wird ermitteln (Position im String)
    StartIndex = (CursorPosString > (MAX_ANZ_DISPLAY_ZEICHEN-1)) ? (CursorPosString - MAX_ANZ_DISPLAY_ZEICHEN + 1) : 0; 
    
    // Cursorposition im Display ermitteln
    CursorPosDisplay = (CursorPosString > (MAX_ANZ_DISPLAY_ZEICHEN-1)) ? MAX_ANZ_DISPLAY_ZEICHEN-1 : CursorPosString;
    
    // Jetzt den Text im Display ausgeben
    p = x+6;                                        // Erste X-Position
    for(i=0; i<((lString>MAX_ANZ_DISPLAY_ZEICHEN)?MAX_ANZ_DISPLAY_ZEICHEN:lString); i++)
    { if(i == CursorPosDisplay)
      { display.fillRect(p, y, 14, 31);
        display.setColor(BLACK);
        display.drawString(p, y,  T.substring(i+StartIndex, i+StartIndex+1));  // Stelle i ausgeben 
        display.setColor(WHITE);
      } else
      { display.drawString(p, y, T.substring(i+StartIndex, i+StartIndex+1));   // Stelle i ausgeben 
      }
      // Anwelcher Position kommt das nächste Zeichen?
      p=p+15;                                       // Zeichenabstand 15 Pixel
    }
    if(StartIndex>0){
      // Vor dem Text < zeichnen um zu zeigen das da noch was ist.
      display.setFont(ArialMT_Plain_16);
      display.drawString(-1,y+6, "<");
      display.setFont(DialogInput_plain_24);
    }
    if((lString-StartIndex-MAX_ANZ_DISPLAY_ZEICHEN)>0){
      // Nach dem Text > zeichnen um zu zeigen das da noch was ist.
      display.setFont(ArialMT_Plain_16);
      display.drawString(120,y+6, ">");
      display.setFont(DialogInput_plain_24);
    }

    // Tasten auswerten
    display.display();
    while(getkey()>0) delay(50); // Warten das die Taste losgelassen wird
    while((key=getkey()) == 0) delay(50);

    // Zeichenindex der aktuellen 
    i = ac.indexOf(T.substring(CursorPosString, CursorPosString+1)); // Position im erlaubte Zeichen String
    if(i==-1) i=0; // Wenn das Zeichen nicht gefunden wurde, das erste Zeichen im erlaubte Zeichen String nehmen
    
    // <Schwarze> Tasten: Zeichen an der aktuellen Position ändern
    if(key == -2){   
      i = (--i>=0)?i:ac.length()-1;   // [-] Taste
    }
    if(key == -3){  
      i = (++i<ac.length())?i:0;   // [+] Taste
    }

    // Jetzt den String neu zusammen bauen
    T = ((CursorPosString>0)?T.substring(0, CursorPosString):"") + ac.substring(i,i+1) + T.substring(CursorPosString+1);
    
    // Langer, schwarzer Tastendruck ([-]-Taste)löscht das Zeichen an der aktuellen Position 
    if(key == 12){
      if(lString>0){ // Es kann nur was gelöscht werden wenn der String länger als 0 Zeichen ist
        T = ((CursorPosString>0)?T.substring(0, CursorPosString):"") + ((CursorPosString<lString)?T.substring(CursorPosString+1):"");
      }
    }
    
    // Langer, schwarzer Tastendruck ([+]-Taste) fügt ein Zeichen an der aktuellen Position ein 
    if(key == 13) {
      if(lString<lMax){ // Es können nur Zeichen eingefügt werden wenn der String noch nicht seine maximale Länge hat.
        T = ((CursorPosString>0)?T.substring(0, CursorPosString):"") + ac.substring(0,1) + ((CursorPosString<lString)?T.substring(CursorPosString):"");
      }
    }
    
    // <Blaue> Taste: durch die Stellen rotieren
    if(key == -4){ // nach rechts nach kurzem Tastendruck (beim loslassen)
      if(++CursorPosString >= lString) CursorPosString=0; // Von Vorne anfangen
    }
    if(key == 14){ // nach links bei langem Tastendruck
      if(--CursorPosString < 0) CursorPosString=lString-1; // Ans Ende springen
    }

    // <Rote> Taste: Zurück
    if(key == 11) back = 1;  // Änderungen verwerfen
    if(key == -1)  back = 2;  // Wert übernehmen
  }
  
  if(back == 1) return t;
  else return T;
}


/////////////////////////////////////////////////////////
// Stellt eine Funktion zur eingabe von Dezimalzahlen mit 4 Tastern bereit
// Parameter
// Position im Display (x,y)
// kleinster Wert: NumberMin
// größter Wert: NumberMax
// Anzahl Dezimalstellen: d
// aktueller Wert: v
/////////////////////////////////////////////////////////
float EnterValue(int x, int y, float NumberMin, float NumberMax, int d, float v, String Beschreibung)
{ char back=0;      // 0: Editieren, 1:abbrechen, 2:speichern und übernehmen
  int lMax=0;       // Länge des Strings: Ganzzahl + Komma + Nachkommazahl = Länge des Strings
  int ld=0;         // Anzahl Dezimalstellen
  int ldg=0;        // 
  int i, p, SP;
  int8_t t;           // Tasten
  float V = v;      // Neuer, editierter Wert
  long prev;
  long NMax = abs((long)NumberMax);
  int neg=0;        // Sind auch negative zahlen erlaubt? (0: nein, 1: ja)
  char S[30];       // Enthällt die einzelnen Stellen der Zahl
  //char *pS;
  int PosCursor=0;  // Position vom Cursor
  long ToggleTime=0; // millis() zum umschalten der Blinkanzeige
  char DisplayNumber=1; // Muss das ins Display geschrieben werden?

  //Serial.println();
  //Serial.println();
  // Dezimale Ganzzahlen herausfinden
  while(NMax > 0)
  { NMax = NMax / 10;
    lMax++;
  }
  //Serial.print("Anzahl Ganzzahlen Max:"); Serial.println(lMax);  // Debugausgabe

  ldg=lMax;
  // Nachkommazahlen herausfinden (inkl. Komma)
  if(d>0) lMax = 1 + lMax + d;
    
  // Werden auch negative Zahlen eingegeben?
  if(NumberMin<0)
  { lMax = 1 + lMax;  //Ja, auch neagitve Zahlen
    neg = 1;
  }
  // Serial.print("Anzahl Stellen Max:"); Serial.println(lMax);  // Debugausgabe
  // in lMAX steht jetzt die maximale Anzahl an Stellen. Die kann nun zum ausgeben der einzelnen Zeichen genutzt werden

  while(getkey()!=0) delay(100); // Warten das die Taste losgelassen wird
  
  // solange im Edit Modus bleiben bis zurück gegangen werden soll
  while(!back)
  { prev = abs((long)V);
    // Werte der aktuellen Zahl ermitteln
    // Anzahl Stellen Dezimale Ganzzahlen herausfinden
    ld=0;
    while(prev > 0)
    { prev = prev / 10;
      ld++;
    }
    //Serial.print("Anzahl Ganzzahlen Akt:"); Serial.println(ld);  // Debugausgabe
    
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0,0, Beschreibung);
    display.drawHorizontalLine(0, 18, 128);
    display.setFont(DialogInput_plain_24);
    // jetzt die einzelnen Stellen im Displaybereich ausgeben
    // Zahl in die Stellen aufteilen
    i=0;
    SP=0;  // Position im String
    if(neg==1){ 
      S[SP++] = (V<0)?'-':'+';                    // Wenn eine negative Zahl eingegeben werden kann auch dsa Vorzeichen darstellen
    }
    ld = lMax - d - 1 - ld - ((neg==1 && d>0)?1:0);// Anzahl aufzufüllender 0en berechnen
    //Serial.print("Anzahl Aufzufüllender 0en:"); Serial.println(ld);  // Debugausgabe
    while(ld-->0) S[SP++] = '0';                  // Führende 0 en eintragen (String mit '0' auffüllen)
    if(d>0) dtostrf(abs(V), ldg, d, &S[SP]);      // Zahl in String umwandeln: bei Dezimalzahl
    else itoa(abs(V), &S[SP], 10);                // Zahl in String umwandeln: bei Ganzzahl
    S[lMax]='\0';                                 // String abschließen
    //Serial.print("Resultierender String:"); Serial.println(S);  // Debugausgabe

    // Jetzt die Zahl im Display ausgeben
    p = x;                                        // Erste X-Position
    for(i=0; i<lMax; i++)
    { if(DisplayNumber==1)                        // Wenn die Zahl angezeigt werden soll (Blinken)
      { if(i == PosCursor)
        { display.fillRect(p, y, 14, 31);
          display.setColor(BLACK);
          display.drawString(p, y, (String)S[i]);     // Stelle i ausgeben 
          display.setColor(WHITE);
        } else
        { display.drawString(p, y, (String)S[i]);     // Stelle i ausgeben 
        }
      }
      // Anwelcher Position kommt das nächste Zeichen?
      p=p+15;                                         // Zeichenabstand für Zahlen
    }    

    // Tasten auswerten
    t = getkey();

    // wenn ich mich an einer Zahlen-Stellel befinde, mit hoch und runter den Wert ändern
    if(S[PosCursor] != '-' &&
       S[PosCursor] != '+' &&
       S[PosCursor] != '.')
    { ld = S[PosCursor]-48;  // ASCII 48 = '0'
      if(t == 2)
      { if(ld < 9) ld++;
        else ld=0;
      }
      if(t == 3)
      { if(ld > 0) ld--;
        else ld=9;
      }
      S[PosCursor] = ld+48;  // ASCII 48 = '0'
    }

    // Befinde ich mich beim Vorzeichen, dann bei Tastendruck (hoch/runter) das Vorzeichen ändern
    if(S[PosCursor] == '-' && (t==2 || t==3))
      S[PosCursor] = '+';
    else if(S[PosCursor] == '+' && (t==2 || t==3))
      S[PosCursor] = '-';

    // Blaue Taste: surch die Stellen rotieren
    if(t == 4)
    {   PosCursor++;
        if(S[PosCursor]=='.') PosCursor++; // Komma überspringen
        if(PosCursor >= lMax) PosCursor = 0; 
    }

    // Rote Taste: Abbrechen
    if(t == 1) back = 1;

    // Jetzt den Wert zurück in die Variable schreiben
    if(d>0) V = atof(S);
    else V = atoi(S); 

    //RangeBar(23, NumberMin, NumberMax, V);

    if(V<NumberMin || V>NumberMax) // Display blinken lassen wenn Wert ausserhalb der Grenzen
    { if(millis() > ToggleTime)
      { DisplayNumber = (DisplayNumber == 0)?1:0; //Umschalten
        ToggleTime = millis()+300;
      }
    } else DisplayNumber = 1;

    display.display();
    delay(80);
  }

  if(V>NumberMax) V = NumberMax;
  if(V<NumberMin) V = NumberMin;
  
  if(back == 1) return v;
  else return V;
}


void RangeBar(int posy, float min, float max, float akt)
{ int posx;
  
  //Min Markierung zeichnen
  display.drawVerticalLine(14, posy+3, 6);
  //Max Markierung zeichnen
  display.drawVerticalLine(114, posy+3, 6);

  // Beschriften
  display.setFont(ArialMT_Plain_10);

  if(akt < min)
  { //Zu Klein!
    display.drawHorizontalLine(7, posy+5, 12);
    display.drawHorizontalLine(108, posy+5, 12);
    display.drawString(0, posy, "<");
    display.drawString(20, posy, "Min:");
    display.drawString(50, posy, String(min,1));
  } else
  if(akt > max)
  { //Zu Groß!
    display.drawHorizontalLine(7, posy+5, 12);
    display.drawHorizontalLine(108, posy+5, 12);
    display.drawString(122, posy, ">");
    display.drawString(20, posy, "Max:");
    display.drawString(50, posy, String(max,1));
  } else
  { //Aktuelle Markierung zeichnen
    display.drawHorizontalLine(7, posy+5, 114);
    posx = (int)((akt-min) * 100 / (max-min));
    display.fillRect(posx-2+14, posy+3, 4, 6);
  }
}


void drawWeighingBar(int posy, float min, float max, float akt)
{ int width = (int)((akt-min) * 100 / (max-min));
  
  //Rahmen zeichnen
  display.drawRect(0, posy+2, 128, 10);  
  //100% Markierung zeichnen
  display.drawVerticalLine(100, posy, 14);
  //Balken zeichnen
  display.fillRect(2, posy+4, width, 5);

  // Beschriften
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, posy-9, String(min, 1));
  display.drawString(85,posy-9, String(max, 1));
}


int8_t getkey(void)
{ unsigned int a = analogRead(A0);  // AD-Wert einlesen
  int8_t k;
  static int8_t prev_k;
  static long int m_start;
  char b[60];

  // Wert geht von 0 bis 1024
  // Tastenabstand bei 4 Tastern (Abhängig vom Spannungsteiler) 1024/5 = 205 (Bereich +-50)
  // Keine Taste gedrückt Wert > 1000
  // Taste 1 -> (235 : Bereich 185 - 285)
  // Taste 2 -> (390 : Bereich 340 - 440)
  // Taste 3 -> (585 : Bereich 535 - 635)
  // Taste 4 -> (775 : Bereich 725 - 825)

  // Single Tastendruck
  if(a > 930) k = 0;  // Keine Taste gedrückt
  if(a>725 && a<825) k = 1;
  if(a>535 && a<635) k = 2;
  if(a>340 && a<440) k = 3;
  if(a>185 && a<285) k = 4;

  if(k != prev_k)
  { if(k==0 && prev_k>0 && prev_k<10)
    { k = -prev_k;
      prev_k = 0;
      return k;
    } else 
    { m_start = millis();  // Zeitpunkt merken
      prev_k = k;
      value.Button = k;
      return k;
    }
  } else
  { if((k != 0) && (millis()-m_start > 700))
    { prev_k = k;
      k=k+10;
      value.Button = k;
      return k;  
    } else return 0;
  }
}


//////////////////////////////////////////////////////////////
// Folgende Daten müssen in das EEPROM geschrieben werden (Max 4096Byte = 4kByte)
// TSettings settings;             100 Byte
// TRezept_Small rezept_small[5];  640 Byte
// TRezept_Big rezept_big[3];     1056 Byte

// Konfiguration / Settings aus EEPROM Auslesen //////////////////////////////////////
void ReadSettings(void)
{ EEPROM.begin(5120);         // Puffergröße die verwendet werden soll
  EEPROM.get(0, settings);    // Anfangsadresse bei der die definierte Struktur abgelegt ist
  EEPROM.end();               // schließen der EEPROM Operation
}
void ReadRezept_small(void)
{ EEPROM.begin(5120);         // Puffergröße die verwendet werden soll
  EEPROM.get(256, rezept_small);    // Anfangsadresse bei der die definierte Struktur abgelegt ist
  EEPROM.end();               // schließen der EEPROM Operation
}
void ReadRezept_big(void)
{ EEPROM.begin(5120);         // Puffergröße die verwendet werden soll
  EEPROM.get(800, rezept_big);    // Anfangsadresse bei der die definierte Struktur abgelegt ist
  EEPROM.end();               // schließen der EEPROM Operation
}

// Konfiguration / Settings im EEPROIM Speichern /////////////////////////////////////
void WriteSettings(void)  // Max 255Byte!
{ EEPROM.begin(5120);
  EEPROM.put(0, settings); //Schreiben einer zweiten Struktur ab Adresse 0
  EEPROM.commit();
  EEPROM.end();
}

void WriteRezept_small(void)
{ EEPROM.begin(5120);
  EEPROM.put(256, rezept_small); //Schreiben einer zweiten Struktur ab Adresse 0
  EEPROM.commit();
  EEPROM.end();
}

void WriteRezept_big(void)
{ EEPROM.begin(5120);
  EEPROM.put(800, rezept_big); //Schreiben einer zweiten Struktur ab Adresse 0
  EEPROM.commit();
  EEPROM.end();
}


// Kalibriermenü
// KALIBRIEREN
void KalibrierMenu(void)
{  long k;
   float kali;  
   int8_t t; // Taste die gedrückt wurde
  display.setFont(ArialMT_Plain_16);
  
  // 1. Waage entlasten
  display.clear();
  display.drawString(0, 0, "Kalibrieren");
  display.drawString(0, 18, "Waage leeren");  
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 36, "Weiter mit Taste..");
  display.display();
  while(getkey()!=0) delay(100);
  while(getkey()==0) delay(100); // Warte auf Tastendruck

  // 2. Kalibrierung starten
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0, 0, "Kalibrieren");
  display.drawString(0, 18, "Waage tarieren");  
  display.display();
  scale.set_scale();
  scale.tare();

  // 3a. Kalibriergewicht aufsetzen
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0, 0, "Kalibrieren");
  display.drawString(0, 18, "Kalibr.gew.: 200,0g");  
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 36, "Weiter mit Taste..");
  display.display();
  while(getkey()!=0) delay(100);
  while(getkey()==0) delay(100); // Warte auf Tastendruck

  // 3b. Waage einlesen
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0, 0, "Kalibrieren");
  display.drawString(0, 18, "Kalibr.gew.: 350,0g"); 
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 36, "... Lese Waage ...");
  display.display();
  k = scale.get_units(10);
  kali = (float)k / 2000;
  
  scale.set_scale(kali);

  // Fertig! Nun den Waagenwert anzeigen
  while(getkey()!=0) delay(100);
  while((t = getkey())!= 4) // Wenn die blaue Taste gedrückt wird, wird die Kalibrierung gespeichert
  { // Aktuell berechneten Wert anzeigen
    display.setFont(ArialMT_Plain_16);
    display.clear();
    display.drawString(0, 0, "Kalibrieren");
    display.drawString(0, 16, "Wert:");
    display.drawString(60,16, String(kali, 2));
    
    k = scale.get_units(2); // Wert messen

    display.setFont(ArialMT_Plain_24);
    display.drawString(115, 35, "g"); 
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.setFont(Roboto_Slab_Bold_34);
    display.drawString(110, 26, String((float)k/10,1));
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    // write the buffer to the display
     display.display();

    // Durch die beiden schwarzen Tasten kann die Kalibrierung angepasst werden
    if(t==2) // + gedrückt
    { kali = kali + 0.01;
      scale.set_scale(kali);
    }
    if(t==3) // - gedrückt
    { kali = kali - 0.01;
      scale.set_scale(kali);
    }    
    delay(100);
  }

  settings.Kalibrierwert = kali;
  WriteSettings();  // Neuen Kalibrierwert zurück in das EEPROm schreiben
}









/****************************************************************************************
 * Beispiele für HX711
 ****************************************************************************************/
/*

/*

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}


 */


/****************************************************************************************
 * Beispiele für Display
 ****************************************************************************************/
/*
 * 
 * #define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo, drawImageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
}

void drawTextFlowDemo() {
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

void drawTextAlignmentDemo() {
    // Text alignment demo
  display.setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
  for (int i=1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
}

void drawProgressBarDemo() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void drawImageDemo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}
*/
