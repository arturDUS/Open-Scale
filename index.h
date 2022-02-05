const char index_html[] PROGMEM = R"========(

<!DOCTYPE HTML><html>
<head>
  <title>Component Scale</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
    width:100%%;
  }
  body {
    margin: 0;
  }
  .content {
    padding-left: 30px;
    padding-right: 30px;
    padding-top: 5px;
    max-width: 1200px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    max-width: 300px;
    outline: none;
    color: rgb(0,0,0);/*#fff;*/
    background-color: rgb(180,180,180);/*#0f8b8d;*/
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: rgb(220,220,220); /*#0f8b8d;*/
     box-shadow: 2 2px rgb(20,20,20); /*#CDCDCD;*/
     transform: translateY(2px);
   }
   .tinybutton {
    padding: 1px 20px;
    font-size: 50px;
    text-align: center;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    /*width: 50px;*/
    outline: none;
    color: rgb(255, 255, 255);/*#fff;*/
    background-color: #143642;/*#0f8b8d;*/
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }

   .state {
     /*font-size: 1.5rem;*/
     font-size: 2.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
   option.service-small {
    font-size: 24px;
    padding: 2px;
   }
   .listsize {
     width: 200px;
     height: 135px;
   }
   table {
    color:#000000;
    background-color: #F8F7F9;
    /*max-width: 100%%;*/
   }
   td {
    font-size: 24px;
    padding: 5px;
   }

/* The Modal (background) */
.modal {
  display: none; /* Hidden by default */
  position: fixed; /* Stay in place */
  z-index: 1; /* Sit on top */
  padding-top: 100px; /* Location of the box */
  left: 0;
  top: 0;
  width: 100%%; /* Full width */
  height: 100%%; /* Full height */
  overflow: auto; /* Enable scroll if needed */
  background-color: rgb(0,0,0); /* Fallback color */
  background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
}

/* Modal Content */
.modal-content {
  background-color: #fefefe;
  margin: auto;
  padding: 20px;
  border: 1px solid #888;
  max-width: 500px;
  font-size: 32px;
}

/* The SAVE Button */
.save {
  color: #aaaaaa;
  float: right;
  font-size: 42px;
  font-weight: bold;
}

.save:hover,
.save:focus {
  color: #000;
  text-decoration: none;
  cursor: pointer;
}

/* The CANCEL Button */
.cancel {
  color: #aaaaaa;
  float: left;
  font-size: 42px;
  font-weight: bold;
}

.cancel:hover,
.cancel:focus {
  color: #000;
  text-decoration: none;
  cursor: pointer;
}

/* The Close Button */
.close {
  color: #aaaaaa;
  float: right;
  font-size: 42px;
  font-weight: bold;
}

.close:hover,
.close:focus {
  color: #000;
  text-decoration: none;
  cursor: pointer;
}

/* The container */
.container {
  display: block;
  position: relative;
  padding-left: 35px;
  margin-bottom: 5px;
  cursor: pointer;
  font-size: 32px;
  -webkit-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}

/* Hide the browser's default radio button */
.container input {
  position: absolute;
  opacity: 0;
  cursor: pointer;
}

/* Create a custom radio button */
.checkmark {
  position: absolute;
  top: 0;
  left: 0;
  height: 30px;
  width: 30px;
  background-color: #eee;
  border-radius: 50%%;
}

/* On mouse-over, add a grey background color */
.container:hover input ~ .checkmark {
  background-color: #ccc;
}

/* When the radio button is checked, add a blue background */
.container input:checked ~ .checkmark {
  background-color: #2196F3;
}

/* Create the indicator (the dot/circle - hidden when not checked) */
.checkmark:after {
  content: "";
  position: absolute;
  display: none;
}

/* Show the indicator (dot/circle) when checked */
.container input:checked ~ .checkmark:after {
  display: block;
}

/* Style the indicator (dot/circle) */
.container .checkmark:after {
  top: 11px;
  left: 11px;
  width: 8px;
  height: 8px;
  border-radius: 50%%;
  background: white;
}

.TextInBox {
  background-color: lightgrey;
  border: 2px solid black;
  padding: 6px;
  margin: 2px;
  width: 200px;
  height: 50px;
  text-align: right;
}
 .AlignHorizontal {
  display: flex;
  justify-content: center;
  align-items: center;
 }
.inputFeld [type="text"] { font-size:1.1em; padding:3px; width:140px}
.trapezoid-down {
  border-left: 20px solid transparent;
  border-right: 20px solid transparent;
  border-top: 15px solid rgb(200,200,220);
  width: 200px;
  text-align: center;
  margin: auto;
}

</style>
  </style>

  <title>Waage</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:">
</head>
<body>
  <div class="topnav" id="Menurow"> 
    <table width="100%%">
      <tr>
        <td width="20%%" align="left">
          <button id="btn_betriebsmodus" class="tinybutton">&#9776;</button> <!--&#Xi-->
        </td>
        <td width="60%%" align="center">
          <h1>DIY Scale</h1>
        </td>
        <td width="20%%" align="right">
          <button id="btn_einstellungen" class="tinybutton">&#9881;</button> <!--&#128736;-->
        </td>
      </tr>
    </table>
  </div> 

  <!-- Trapezsymbol: Wenn mit Maus da drüber gefahren wird, wird die Menüzeile aufgemacht-->
  <div class="trapezoid-down" id="MenuHook" ></div>
  
  <div class="content">
    <div class="card" id="ComponentWeighingDialog">
      <canvas id="DualWiegebalken" width="800em" height="350em" style="border:1px solid #000000;" >
        Ihr Browser kann kein Canvas! 
        <!-- Insert fallback content here -->
      </canvas>
      <p> <button id="btn_tarieren" class="button">Tarieren</button>
        <button id="btn_ok" class="button">OK</button>
      </p>
    </div>

    <div class="card" id="StandardWeighingDialog">
     <!-- <div class="box" id="base"> -->
        <table align="center">
          <tr>
            <td align=right>
              Historie
            </td>
            <td rowspan="2">
              <select id="lstValue" class="listsize" multiple>
                <!-- <option class="service-small">Volunteering</option>
                  <option class="service-small">Partnership &amp; Support</option>
                  <option class="service-small">Business Services</option>
                  -->
              </select>
            </td>
            <td rowspan="2" valign=middle>
              <div>
                <label style="font-size:22px" class="container" align="left"> Additiv
                  <input type="radio" name="STD_Type" checked="checked" onclick="std_type_click()">
                  <span class="checkmark"></span>
                </label> <br>
        
                <label style="font-size:22px" class="container" align="left"> Einzel
                  <input type="radio" name="STD_Type" onclick="std_type_click()">
                  <span class="checkmark"></span>
                </label> <br>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <button id="std_btn_clear" class="button">Löschen</button>
            </td>
          </tr>
        </table>
     <!-- </div> -->
      <canvas id="StandardWiegebalken" width="800em" height="350em" style="border:1px solid #000000;" >
        Ihr Browser kann kein Canvas! 
        <!-- Insert fallback content here -->
      </canvas>
      <p> <button id="std_btn_tarieren" class="button">Tarieren</button>
        <button id="std_btn_ok" class="button">OK (Übernehmen)</button>
      </p>
    </div>


    <div class="card" id="CountScaleDialog">
      <div>
        <span style="font-size:250px; font-weight: bold; color: rgb(14, 68, 14)" id="CountScale_Anz">----</span>
        <span style="font-size:48px; color: rgb(0, 0, 0)" align="right"> Stück</span>
      </div>
      <div>
        <span style="font-size:24px" align="left">Ist:</span>
        <span id="CountScale_IstWert" style="font-size: 32px; font-weight: bold">100.2</span>
        <span style="font-size: 24px">g</span>
      </div>
      <p> </p>
      <div>
        <button id="CS_btn_Definieren" class="tinybutton">&#10000;</button>
      </div>
      <p> </p>
      <div>
        <button id="CS_btn_tarieren" class="button">Tarieren</button>
      </div>
    </div>



    <div class="card" id="CheckScaleDialog">
      <div>
        <span style="font-size:250px; font-weight: bold; color: rgb(14, 68, 14)" id="CheckScale_OKNOK">---</span>
      </div>
      <canvas id="CheckScaleDrawArea" width="600em" height="170em" style="border:1px solid #000000;" >
        Ihr Browser kann kein Canvas! 
        <!-- Insert fallback content here -->
      </canvas>
      <div>
        <span style="font-size:24px" align="left">Ist:</span>
        <span id="CheckScale_IstWert" style="font-size: 32px; font-weight: bold">100.2</span>
        <span style="font-size: 24px">g</span>
      </div>
      <p> </p>
      <div>
        <button id="CNTR_btn_Definieren" class="tinybutton">&#10000;</button>
      </div>
      <p> </p>
      <div>
        <button id="CNTR_btn_tarieren" class="button">Tarieren</button>
      </div>

    </div>

  </div>

<!-------------------------------------------------------------------------------------->
<!-- Subdialoge ------------------------------------------------------------------------>

<!-- Betriebsmodus Auswahl Dialog -->
<div id="BetriebsmodusAuswahl" class="modal">
  <!-- Modal content -->
  <div class="modal-content">

    <span class="close" id="x_btn_BMA">&#10004;</span> 
    <form align="left">
      <p style="font-size: 42px; font-weight: bold; ">Betriebsmodus</p> 
        <label class="container"> Standard
          <input type="radio" name="Betriebsmodus" onclick="close_modal_BMA_click()">
          <span class="checkmark"></span>
        </label> <br>

        <label class="container"> Komponennten
          <input type="radio" name="Betriebsmodus" onclick="close_modal_BMA_click()">
          <span class="checkmark"></span>
        </label> <br>

        <label class="container"> Zählen
          <input type="radio" name="Betriebsmodus" onclick="close_modal_BMA_click()">
          <span class="checkmark"></span>
        </label> <br>

        <label class="container"> Kontrollwaage
          <input type="radio" name="Betriebsmodus" onclick="close_modal_BMA_click()">
          <span class="checkmark"></span>
        </label> <br>       
    </form>
  </div>
</div>

<!-- Einzelgewichtsbestimmung Dialog -> Zählwaage-->
<div id="Einzelgewichtsbestimmung" class="modal">
  <!-- Modal content -->
  <div class="modal-content">
    <div>
      <!-- <span class="cancel" id="abr_btn_EGB">&#10008;</span> -->
      <span >Einzelgewichtsbestimmung</span>
      <span class="save" id="x_btn_EGB">&#10004;</span>
    </div>
    <p></p>
    <table width="500px">
      <tr>
        <td style="font-size:24px" align="right">Ist:</td>
        <td style="border:2px solid black">
          <span id="EGB_IstWert" style="font-size: 48px; font-weight: bold">100.2</span>
          <span >g</span>
        </td>
        <td>
          <button id="EGB_btn_Tare" class="tinybutton">-T-</button>
        </td>
      </tr>
      <tr>
        <td style="font-size:24px" align="right">Gewicht:</td>
        <td class="inputFeld"> 
          <input placeholder="Gewicht" type="text" id="EGB_Gewicht" pattern="[g0-9]." onchange="EGB_GewichtChange()">
        </td>
        <td>
          <button id="EGB_btn_Uebern" class="tinybutton"><<</button>
        </td>
      </tr>
      <tr>
        <td style="font-size:24px" align="right">Anzahl:</td>
        <td class="inputFeld">
          <input placeholder="Anzahl" type="text" id="EGB_Anzahl" pattern="[0-9]" onchange="EGB_AnzahlChange()">
        </td>
        <td> </td>
      </tr>
      <tr>
        <td style="font-size:24px" align="right"> Einz.gew.:</td>
        <td style="font-size:34px; font-weight: bold" id="EGB_EinzGewicht" colspan="2">---</td>
      </tr>
   </table>
  </div>
</div>

<!-- Kontrollgrenzenbestimmungs Dialog -> Kontrollwaage-->
<div id="Kontrollgrenzenbestimmung" class="modal">
  <!-- Modal content -->
  <div class="modal-content">
    <div>
      <span class="h2">Kontroll Grenzen</span>
      <span class="save" id="x_btn_KGB">&#10004;</span>
    </div>
    <p></p>
    <table width="500px">
      <tr>
        <td style="font-size:24px" align="right">Ist:</td>
        <td style="border:2px solid black">
          <span id="KGB_IstWert" style="font-size: 48px; font-weight: bold">100.2</span>
          <span >g</span>
        </td>
        <td>
          <button id="KGB_btn_Tare" class="tinybutton">-T-</button>
        </td>
      </tr>
      <tr>
        <td style="font-size:24px" align="right">Min Gewicht:</td>
        <td class="inputFeld"> 
          <input placeholder="Min" type="text" id="KGB_MinGewicht" pattern="[0-9]." onchange="KGB_MinGewichtChange()">
        </td>
        <td>
          <button id="KGB_btn_MinGewichtUebern" class="tinybutton"><<</button>
        </td>
      </tr>
      <tr>
        <td style="font-size:24px" align="right">Max Gewicht:</td>
        <td class="inputFeld">
          <input placeholder="Max" type="text" id="KGB_MaxGewicht" pattern="[0-9]." onchange="KGB_MaxGewichtChange()">
        </td>
        <td> 
      <button id="KGB_btn_MaxGewichtUebern" class="tinybutton"><<</button>
    </td>
      </tr>
   </table>
  </div>
</div>

<!-- Configuration Dialog -->
<div id="Konfiguration" class="modal">
  <!-- Modal content -->
  <div class="modal-content">
    <div>
      <span class="h2">Konfiguration</span>
      <span class="save" id="x_btn_config">&#10008;</span>
    </div>
    <p></p>
    <div style="height:300px; overflow:auto;">
    <table style="width:480px;">
      <tr> <!-- Zeile 1: Name-->
        <td style="font-size:22px" align="right">Scale Name</td>
        <td align="left" width="250px">
          <input style="font-size:22px" placeholder="Name" type="text" id="CFG_iName">
          <!-- <span >g</span> -->
        </td>
      </tr>

      <tr> <!-- Zeile 2: Actual IP Address-->
        <td style="font-size:22px" align="right">IP *</td>
        <td align="left">
          <!-- <input placeholder="Name" type="text" id="CFG_iName" pattern="[0-9][a-Z]"> -->
          <span style="font-size:16px; font-weight:bold" align="right" id="CFG_IPNumber"></span>
        </td>
      </tr>

      <tr> <!-- Zeile 3: Startup Mode-->
        <td style="font-size:22px" valign=top align="right">Startup Scale Mode</td>
        <td align="left">
          <!-- <input placeholder="Name" type="text" id="CFG_iName""> -->
          <!-- <span style="font-size:16px" align="right" id="CFG_IPNumber"></span> -->
          <label style="font-size:22px" class="container" align="left"> Standard
            <input type="radio" name="CFG_stdBM">
            <span class="checkmark"></span>
          </label> <br>
  
          <label style="font-size:22px" class="container" align="left"> Komponennten
            <input type="radio" name="CFG_stdBM">
            <span class="checkmark"></span>
          </label> <br>
  
          <label style="font-size:22px" class="container" align="left"> Zählen
            <input type="radio" name="CFG_stdBM">
            <span class="checkmark"></span>
          </label> <br>
  
          <label style="font-size:22px" class="container" align="left"> Kontrollwaage
            <input type="radio" name="CFG_stdBM">
            <span class="checkmark"></span>
          </label> <br>  
        </td>
      </tr>      

      <tr> <!-- Zeile 4-->
        <td style="font-size:22px" align="right">Max Range</td>
        <td align="left">
          <input style="font-size:22px; width:200px" placeholder="Max Range" type="text" id="CFG_iMaxRange" pattern="[0-9].">
          <span style="font-size:22px" align="right">g</span>
        </td>
      </tr>

      <tr> <!-- Zeile 5-->
        <td style="font-size:22px" align="right">Schrittweite</td>
        <td align="left">
          <input style="font-size:22px; width:200px" placeholder="Schrittweite" type="text" id="CFG_iSchrittweite" pattern="[0-9].">
          <span style="font-size:22px" align="right">g</span>
        </td>
      </tr>

      <tr> <!-- Zeile 6-->
        <td style="font-size:22px" align="right">Tolerance</td>
        <td align="left">
          <input style="font-size:22px; width:200px" placeholder="Tolerance" type="text" id="CFG_iTolerance" pattern="[0-9].">
          <span style="font-size:22px" align="right">%%</span>
        </td>
      </tr>

      <tr> <!-- Zeile 6 a-->
        <td style="font-size:22px" align="right">Einheit</td>
        <td align="left">
          <input style="font-size:22px; width:200px" placeholder="mg, g, kg, t, lbs" type="text" id="CFG_iUnit">
        </td>
      </tr>

      <tr> <!-- Zeile 7-->
        <td style="font-size:22px" valign=top align="right">Startup Wifi Mode</td>
        <td align="left">
          <!-- <input placeholder="Name" type="text" id="CFG_iName" pattern="[0-9][a-Z]"> -->
          <!-- <span style="font-size:16px" align="right" id="CFG_IPNumber"></span> -->
          <label style="font-size:22px" class="container" align="left"> Disabled
            <input type="radio" name="CFG_stdWIFI">
            <span class="checkmark"></span>
          </label> <br>
  
          <label style="font-size:22px" class="container" align="left"> Client Mode
            <input type="radio" name="CFG_stdWIFI">
            <span class="checkmark"></span>
          </label> <br>
  
          <label style="font-size:22px" class="container" align="left"> Accesspoint Mode
            <input type="radio" name="CFG_stdWIFI">
            <span class="checkmark"></span>
          </label> <br>  
        </td>
      </tr>

      <tr> <!-- Zeile 8-->
        <td style="font-size:22px" align="right">WiFi SSID</td>
        <td align="left">
          <input style="font-size:22px" placeholder="SSID" type="text" id="CFG_iSSID">
          <!-- <span >g</span> -->
        </td>
      </tr>

      <tr> <!-- Zeile 9-->
        <td style="font-size:22px" align="right">Passwort</td>
        <td align="left">
          <input style="font-size:22px" placeholder="*****" type="text" id="CFG_iPasswort">
          <!-- <span >g</span> -->
        </td>
      </tr>

      <tr> <!-- Zeile 10-->
        <td style="font-size:22px" align="right">Scale AP IP *</td>
        <td align="left">
          <input style="font-size:22px" placeholder="Access Point IP" type="text" id="CFG_iAPIP" pattern="[0-9].">
          <!-- <span >g</span> -->
        </td>
      </tr>

      <tr> <!-- Zeile 11-->
        <td style="font-size:22px" align="right">AP Gateway</td>
        <td align="left">
          <input style="font-size:22px" placeholder="Accesspoint Gateway IP" type="text" id="CFG_iGateway" pattern="[0-9].">
          <!-- <span >g</span> -->
        </td>
      </tr>

      <tr> <!-- Zeile 12-->
        <td style="font-size:22px" align="right">AP Subnetmask</td>
        <td align="left"> 
          <input style="font-size:22px" placeholder="Subnetmask" type="text" id="CFG_iSubnetmask" pattern="[0-9].">
          <!-- <span >g</span> -->
        </td>
      </tr>
   </table>
  </div>
  <br>
  <button style="font-size:32px" id="CFG_btn_Save" class="Button">Save</button>
  </div>
</div>


<script>
  'use strict';
////////////////////////////////////////////////////////////////////////////////////////////
// Globale Variablen
////////////////////////////////////////////////////////////////////////////////////////////
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;

  // Werte übertragen von der Waage
  var SollWert = 150; // Sollwert
  var IstWert = 146.0; // Istwert von der Waage
  var MaxWert = 1000.0;  // Maximalwert der Waage
  var Toleranz = 5;   // Toleranzbereich der Waage
  var Betriebsmodus = -1;// 0: Standardeinwaage (Summierung, Maximalgewicht)
                         // 1: Komponenten Einwaage (Zielgewicht)
                         // 2: Zählwaage
                         // 3: Kontrollwaage

  // Werte die für die verschiedenen Dialoge gebraucht werden und nicht bei jedem Refresh gelöscht werden sollen
  var Gesamtgewicht = +0; // Gesamtgewicht über alle Messungen bei der Standardeinwaage
  var STD_WType = 0;      // Wiegetyp 0: Additiv - Einzelgewichte werden auf die Waage hinzugefügt
                          //          1: Einzel - Einzelgewichte werden nacheinander gewogen und immer von der Waage entfern 
  var Messungen = [];    // Enthält die einzelnen Messungen
  var Einzelgewicht = +0; // Einzelgewicht aus dem Einzelgewichtsbestimmungsdialog
  var ContrMinGewicht = +0;
  var ContrMaxGewicht = +0;
  window.addEventListener('load', onLoad);
  window.addEventListener('resize', resizeCanvas, false);  // Wenn sich die Fenstergröße ändert, auch das Canvas ändern

  // Configurationswerte
  const configdata = {
    Type: 'CONFIG',                 // Configurationsdaten FESTER WERT nicht ändern!
    Name: 'Waage',                  // Name der Waage - id="CFG_iName"
    SSID: 'LoxDUS',                 // Client Mode SSID - id="CFG_iSSID"
    APIP: '192.168.4.1',            // Accesspoint IP - id="CFG_iAPIP"
    APgateway: '192.168.4.1',       // Accesspoint Gateway - id="CFG_iGateway"
    APsubnetmask: '255.255.255.0',  // Accesspoint Subnetmask - id="CFG_iSubnetmask"
    pwd: '',                        // ClientMode Passwort - id="CFG_iPasswort"
    WiFiMode: 2,                    // WiFi Startmode - name="CFG_stdWIFI", 0:Disabled, 1:Client Mode, 2:Accesspoint Mode
    Defaultmode: 0,                 // Checkbutton - name="CFG_stdBM", 0:Standard, 1:Komponennten, 2:Zählen, 3:Kontrollwaage
    IP: '',                         // Aktuelle IP Adresse - id="CFG_IPNumber" innerHTML
    ScaleMaxRange: 1000,            // Maximaler Wägebereich - id="CFG_iMaxRange"
    ScaleSteps: 0.1,                // Anzeigegenauigkeit - id="CFG_iSchrittweite"
    ScaleTolerance: 5,              // Wiegetoleranz - id="CFG_iSchrittweite"
    ScaleUnit: 'g'                  // Einheit der Waage - id="CFG_iUnit"
  };

////////////////////////////////////////////////////////////////////////////////////////////
// Dialog zur manuellen Einwaage von mehreren Komponenten
////////////////////////////////////////////////////////////////////////////////////////////
function StandardWeighing() {
  var canvas = document.getElementById('StandardWiegebalken');
  var ctx = canvas.getContext("2d");
  canvas.width = document.getElementById('StandardWeighingDialog').offsetWidth-40;
  var IstGewicht = IstWert;
  var AMaxWert  = Number(MaxWert) - Number(Gesamtgewicht); // Das noch verfügbare restgewicht
  
  // Berechne die Positionen der einzelnen Felder
  var MaxBreite = Number(canvas.width) - 40; // Breite des Wiegebalkens in Pixeln vom Tarierpunkt aus!
  
  // Test: MaxBreite = document.getElementById('StandardWeighingDialog').offsetWidth - 40;
  var GFaktor = MaxBreite / MaxWert; // Gesamtgewicht balken Faktor mit dem die Gewichtswerte multipliziert werden
                                        // müssen um ins Digramm zu passen
  var AFaktor = MaxBreite / AMaxWert;   // Aktuelles gewicht balken Faktor mit dem die Gewichtswerte multipliziert werden
                                        // müssen um ins Digramm zu passen
  var xGesamt = Number(Gesamtgewicht) * GFaktor;
  var xIst = IstGewicht * AFaktor;
  
  // clear the canvas
    ctx.clearRect(0,0,canvas.width,canvas.height);
  
   // console.log("Breite: " + canvas.width);
  //////////////////////////////////////////////////
  // Oberer Balken: Gesamtgewicht
  ctx.fillStyle = "rgb(240,240,240)";   // Hellgrau
  ctx.fillRect (20, 20, MaxBreite, 40);
  ctx.fillStyle = "rgb(0,200,0)";       // Grün
  ctx.fillRect (20, 25, xGesamt, 30);  
  ctx.lineWidth = 1;
  ctx.strokeStyle = "rgb(0,0,0)";       // Schwarz
  ctx.strokeRect (20, 20, MaxBreite, 40);
  // Gesamtgewicht Einzeichnen (Schwarz)
  ctx.beginPath();
    ctx.lineWidth = 3;
    ctx.moveTo(xGesamt+20, 20);            // vertikale Linie
    ctx.lineTo(xGesamt+20, 60);
  ctx.stroke();
  // Menge eintragen
  ctx.fillStyle = "rgb(0,0,0)";       // Grün
  ctx.font="bold 32px Arial";
  ctx.textAlign ="center";
  ctx.fillText(Number(Gesamtgewicht).toFixed(1) + configdata.ScaleUnit,MaxBreite/2 + 20,52);
  // Grenzen eintragen
  ctx.font="24px Arial";
  ctx.textAlign ="left";
  ctx.fillText("0"+configdata.ScaleUnit,20,90); 
  ctx.textAlign ="right";
  ctx.fillText(Number(MaxWert).toFixed(1) + configdata.ScaleUnit,canvas.width-20,90);

  //////////////////////////////////////////////////
  // Unterer Balken: Aktuelles Gewicht
  ctx.fillStyle = "rgb(240,240,240)";   // Hellgrau
  ctx.fillRect (20, 120, MaxBreite, 60);
  ctx.fillStyle = "rgb(0,200,0)";       // Grün
  ctx.fillRect (20, 125, xIst, 50);
  ctx.lineWidth = 1;
  ctx.strokeStyle = "rgb(0,0,0)";       // Schwarz
  ctx.strokeRect (20, 120, MaxBreite, 60);
  // Aktuelles Gewicht Einzeichnen (Schwarz)
  ctx.beginPath();
    ctx.lineWidth = 3;
    ctx.moveTo(xIst+20, 120);            // vertikale Linie
    ctx.lineTo(xIst+20, 180);
  ctx.stroke();
  // Pfeil für IstMenge einzeichnen
  ctx.fillStyle = "rgb(0,0,200)";
  ctx.beginPath();                    // Pfeil Oben
    ctx.moveTo(xIst+20, 120);
    ctx.lineTo(xIst+27, 90);
    ctx.lineTo(xIst+13, 90);
  ctx.fill();
  ctx.beginPath();                    // Pfeil Unten
    ctx.moveTo(xIst+20, 180);
    ctx.lineTo(xIst+27, 210);
    ctx.lineTo(xIst+13, 210);
  ctx.fill();
  // Menge eintragen

  // Grenzen eintragen
  ctx.fillStyle = "rgb(0,0,0)";
  ctx.font="24px Arial";
  ctx.textAlign ="left";
  ctx.fillText("0"+configdata.ScaleUnit,20,205); 
  ctx.textAlign ="right";
  ctx.fillText(Number(AMaxWert).toFixed(1) + configdata.ScaleUnit,canvas.width-20,205);

  // IST Box
  ctx.lineWidth = 3;
  ctx.fillStyle = "rgb(200,200,200)";
  ctx.fillRect (20, 220, MaxBreite, 100);
  ctx.strokeStyle = "rgb(0,0,0)";
  ctx.strokeRect (20, 220, MaxBreite, 100);
  ctx.fillStyle = "rgb(0,0,0)";
  ctx.font="24px Arial";
  ctx.fillText("Ist:",60,290);  
  ctx.font="bold 80px Arial";
  ctx.textAlign ="center";
  ctx.fillText(Number(IstWert).toFixed(1) + configdata.ScaleUnit, MaxBreite/2,290);
}


////////////////////////////////////////////////////////////////////////////////////////////
// Fügt einen Wert in die Liste der Einwaagen ein
////////////////////////////////////////////////////////////////////////////////////////////
function addValue(v) { 
  var list = document.getElementById('lstValue');
  var Eintrag =document.createElement('option');
  Eintrag.setAttribute("class", "service-small");
  //Eintrag.value = 3;
  Eintrag.text = Number(IstWert).toFixed(1) + configdata.ScaleUnit;
  Gesamtgewicht = Number(Gesamtgewicht) + Number(IstWert);
  websocket.send('tare'); // Waage tarieren
  list.appendChild(Eintrag);   
 }


////////////////////////////////////////////////////////////////////////////////////////////
// Dialog zur Einwaage von mehreren Komponenten mit einem genauen Zielgewicht
////////////////////////////////////////////////////////////////////////////////////////////
function ComponetWeighing() {
  var canvas = document.getElementById('DualWiegebalken');
  var ctx = canvas.getContext("2d");
  var offset;
  var xtemp, btemp, xSollDetail;  // Temporäre Variable
  const bWb = 30;   // Breite Wiegebalken
  const bDb = 30;   // Breite Detailbalken
  const aWbDb = 50;   // Abstand zwischen Wiegebalken und Detailbalken
  
  canvas.width = document.getElementById('ComponentWeighingDialog').offsetWidth-40;

  // Berechne die Positionen der einzelnen Felder
  var MaxBreite = canvas.width - 40 - 20; // Breite des Wiegebalkens in Pixeln vom Tarierpunkt aus!
  var Faktor = MaxBreite / MaxWert;   // Faktor mit dem die Gewichtswerte multipliziert werden
                      // müssen um ins Digramm zu passen
  var xNull = 20;             // Fixer Wert
  var xTara = xNull + 20;         // Fixer Wert
    var xSoll = SollWert * Faktor + xTara;  // Position des Sollwertes
  var xStartDetail = xSoll - (Toleranz * SollWert / 100) * Faktor;
  var xZuViel = xSoll + (Toleranz * SollWert / 100) * Faktor; // Die Warngrenze begletzten Viertel der Toleranz
  var xWarn = xZuViel - (Toleranz * SollWert / 400) * Faktor;
  var xMax = canvas.width - 20;
  var xIst = IstWert * Faktor + xTara;
  
  var TaraBreite = 40;
  var GrobBreite = xStartDetail - xTara;
  var ToleranzBreite = xWarn - xStartDetail;
  var WarnBreite = (Toleranz * SollWert / 400) * Faktor;
  var ZuVielBreite = xMax - xZuViel;

    // clear the canvas
    ctx.clearRect(0,0,canvas.width,canvas.height);
  
  // Oberer Balken: Grobeinstellung
  
  // Tarierbereich (Grau)
  ctx.fillStyle = "rgb(200,200,200)";
  ctx.fillRect (20, 50, TaraBreite, 30);
  
  // Grober Bereich (Türkis)
  ctx.fillStyle = "rgb(120,150,120)";
  ctx.fillRect (xTara, 50, GrobBreite, 30);
  
  // Toleranzbereich (Grün)
  ctx.fillStyle = "rgb(0,230,0)";
  ctx.fillRect (xStartDetail, 50, ToleranzBreite, 30);
  
  // Warnbereich (Gelb)
  ctx.fillStyle = "rgb(2000,200,0)";
  ctx.fillRect (xWarn, 50, WarnBreite, 30);
  
  // Ausser Toleranz (Rot)
  ctx.fillStyle = "rgb(200,0,0)";
  ctx.fillRect (xZuViel, 50, ZuVielBreite, 30);
  
  // Verbindung zur Detailfläche
  ctx.fillStyle = "rgb(230,230,230)";
  ctx.beginPath();
    ctx.moveTo(xStartDetail, 80);
    ctx.lineTo(xTara, 130); 
    ctx.lineTo(canvas.width - 20, 130);
    ctx.lineTo(xZuViel, 80);
    ctx.closePath();
  ctx.fill();
  
  // SollMenge Einzeichnen (Schwarz)
  ctx.strokeStyle = "rgb(0,0,0)";
  ctx.beginPath();
    ctx.lineWidth = 3;
    ctx.moveTo(xSoll, 35);     // vertikale Linie
    ctx.lineTo(xSoll, 85);
  ctx.stroke();
  
  // Jetzt die Beschriftung für die Sollmenge bestimmen
  ctx.textAlign ="left";
  ctx.font="bold 32px Arial";
  btemp = ctx.measureText(Number(SollWert).toFixed(1)).width + 50; // Breite des Textes
  if((xSoll-btemp/2) < xNull) xtemp = xNull;
  else if((xSoll+btemp/2) > (canvas.width - 20)) xtemp = canvas.width - 20 - btemp;
  else xtemp = xSoll - btemp/2;
  ctx.beginPath();
    ctx.moveTo(xtemp, 35); // Unterstrich
    ctx.lineTo(xtemp + btemp, 35);  
  ctx.stroke();
  
  // Sollmengen Text schreiben
  ctx.fillStyle = "rgb(0,0,0)";
  ctx.font="24px Arial";
  ctx.fillText("Soll:",xtemp,30); 
  ctx.font="bold 32px Arial";
  ctx.fillText(Number(SollWert).toFixed(1) + configdata.ScaleUnit,xtemp + 50,30);
  
  // Pfeil für IstMenge einzeichnen
  ctx.fillStyle = "rgb(0,0,250)";
  ctx.beginPath();
    ctx.moveTo(xIst, 80);
    ctx.lineTo(xIst+7, 50);
    ctx.lineTo(xIst-7, 50);
  ctx.fill();
    
  ctx.strokeStyle = "rgb(0,0,0)";
  var DetailGrenzen = Toleranz * SollWert / 100;
  var MinDetail = Number(SollWert) - Number(DetailGrenzen);
  var MaxDetail = Number(DetailGrenzen) + Number(SollWert);
  // Detailbalken /////////////////////////////////////////////////////////////////////////////////////
  if((IstWert >= MinDetail) && (IstWert <= MaxDetail)){
    // Wert ist im Toleranzbereich
    offset = 2 * DetailGrenzen;
    Faktor = MaxBreite / offset;    // Faktor mit dem die Gewichtswerte multipliziert werden
                      // müssen um ins Digramm zu passen
    offset = SollWert - DetailGrenzen;                 
    xSollDetail = (SollWert - offset) * Faktor + xTara; // Position des Sollwertes
    xStartDetail = 40;
    xWarn = (canvas.width - 20) - (Toleranz * SollWert / 400) * Faktor;
    xIst = (IstWert - offset) * Faktor;
    
    ToleranzBreite = xWarn - xStartDetail;
    WarnBreite = (Toleranz * SollWert / 400) * Faktor;
    
    // Toleranzbereich (Grün)
    ctx.fillStyle = "rgb(0,230,0)";
    ctx.fillRect (xStartDetail, 130, ToleranzBreite, 30);
   
    // Warnbereich (Gelb)
    ctx.fillStyle = "rgb(2000,200,0)";
    ctx.fillRect (xWarn, 130, WarnBreite, 30);
    
    // SollMenge Einzeichnen (Schwarz)
    ctx.strokeStyle = "rgb(0,0,0)";
    ctx.beginPath();
      ctx.lineWidth = 4;
      ctx.moveTo(xSollDetail, 120);
      ctx.lineTo(xSollDetail, 195);
    ctx.stroke();
    ctx.beginPath();
      ctx.lineWidth = 2;
      ctx.moveTo(xSoll, 85);
      ctx.lineTo(xSollDetail, 120);
    ctx.stroke();
    
    // IstMenge einzeichnen
    ctx.strokeStyle = "rgb(0,0,250)";
    ctx.beginPath();
      ctx.lineWidth = 2;
      ctx.moveTo(xIst, 125);    // Vertikale Linie für IstWert
      ctx.lineTo(xIst, 220);
    ctx.stroke();
    ctx.beginPath();
      ctx.moveTo(xIst, 190);    // Horizontale Linie für Differenzwert
      ctx.lineTo(xSollDetail, 190);
    ctx.stroke();

    ctx.fillStyle = "rgb(0,0,250)";
    ctx.beginPath();      // Pfeil nach Oben für IST Wert
      ctx.moveTo(xIst, 160);
      ctx.lineTo(xIst+7, 190);
      ctx.lineTo(xIst-7, 190);
    ctx.fill(); 
    
    ctx.font="bold 24px Arial";
    btemp = ctx.measureText(Number(SollWert-IstWert).toFixed(1)).width + 15; // Breite des Textes
    if(IstWert < SollWert) {
      ctx.beginPath();      // Pfeil nach Rechts für Differenz Wert
        ctx.moveTo(xSollDetail, 190);
        ctx.lineTo(xSollDetail-30, 183);
        ctx.lineTo(xSollDetail-30, 197);
      ctx.fill(); 
      // Rest Wert
      ctx.fillStyle = "rgb(0,0,0)";
      ctx.fillText((Number(SollWert-IstWert).toFixed(1)) + configdata.ScaleUnit,(xSollDetail-xIst-btemp)/2+xIst,185);
    } else if(IstWert > SollWert) {
      ctx.fillStyle = "rgb(200,0,0)";
      ctx.beginPath();      // Pfeil nach Links für Differenz Wert
        ctx.moveTo(xSollDetail, 190);
        ctx.lineTo(xSollDetail+30, 183);
        ctx.lineTo(xSollDetail+30, 197);
      ctx.fill();
      // Zuviel Wert
      ctx.fillText(Number(SollWert-IstWert).toFixed(1) + configdata.ScaleUnit,(xIst-xSollDetail-btemp)/2+xSollDetail,185);
    }
  } else {
    // Wert ist ausserhalb der Toleranz
    ctx.fillStyle = "rgb(200,200,200)";
    ctx.fillRect (20, 130, MaxBreite+20, 30); 
  }
    
  // IST Box
  ctx.lineWidth = 3;
  ctx.fillStyle = "rgb(200,200,200)";
  ctx.fillRect (20, 220, MaxBreite, 100);
  ctx.strokeStyle = "rgb(0,0,0)";
  ctx.strokeRect (20, 220, MaxBreite, 100);
  ctx.fillStyle = "rgb(0,0,0)";
  ctx.font="24px Arial";
  ctx.fillText("Ist:",40,290);  
  ctx.font="bold 80px Arial";
  ctx.textAlign ="center";
  ctx.fillText(Number(IstWert).toFixed(1) + configdata.ScaleUnit, (MaxBreite+40)/2,290);
  
  // Texte
  ctx.font="16px Arial";
  ctx.textAlign ="left";
    ctx.fillText("0"+configdata.ScaleUnit,20,100);
    ctx.fillText(Number(MinDetail).toFixed(1)+configdata.ScaleUnit,20,180);
  ctx.textAlign ="right";
    ctx.fillText(Number(MaxWert).toFixed(1)+configdata.ScaleUnit, canvas.width - 20,100);
    ctx.fillText(Number(MaxDetail).toFixed(1)+configdata.ScaleUnit,canvas.width - 20,180);
}


////////////////////////////////////////////////////////////////////////////////////////////
// Dialog zum zählen von Stückgut mit vorheriger Kalibrierung
////////////////////////////////////////////////////////////////////////////////////////////
function CountScale() {
  var E;
  // Es brauchen nur die beiden Textfelder aktualisiert werden
  if(Number(Einzelgewicht) > 0) {
    E = Number(IstWert) / Number(Einzelgewicht);
    document.getElementById("CountScale_Anz").innerText = E.toFixed(0);  // DialogDaten aktuelisierenx.value
  } else document.getElementById("CountScale_Anz").innerText = "----";  // DialogDaten aktuelisierenx.value

  //console.log("Einzelgewicht: " + Einzelgewicht + " Istwert: "+ IstWert + "  -> Berechnete Anzahl: " + E);

  document.getElementById("CountScale_IstWert").innerText = Number(IstWert).toFixed(1);  // DialogDaten aktuelisierenx.value
   
}

////////////////////////////////////////////////////////////////////////////////////////////
// Dialog zum Prüfen von Gewichten: Anzeige OK / NOK
// Hinweis: Grenzen sind in den Variablen: ContrMinGewicht und ContrMaxGewicht
////////////////////////////////////////////////////////////////////////////////////////////
function CheckScale() {
  var canvas = document.getElementById('CheckScaleDrawArea');
  var ctx = canvas.getContext("2d");
  canvas.width = document.getElementById('CheckScaleDialog').offsetWidth-40;
  
  // Berechne die Positionen der einzelnen Felder
  var MaxBreite = canvas.width - 40; // Breite des Wiegebalkens in Pixeln vom Tarierpunkt aus!
  var AFaktor;  // Aktuelles gewicht balken Faktor mit dem die Gewichtswerte multipliziert werden
                                        // müssen um ins Digramm zu passen
  var xIst;
  var TextColor;
  var Text;

  //////////////////////////////////////////////////
      // clear the canvas
      ctx.clearRect(0,0,canvas.width,canvas.height);
  //////////////////////////////////////////////////
  // Balken bereich
  ctx.lineWidth = 1;
  ctx.fillStyle = "rgb(240,0,0)";   // Roter Balken links
  ctx.fillRect (20, 50, 100, 70);
  ctx.fillStyle = "rgb(240,0,0)";   // Roter Balken Rechts
  ctx.fillRect (MaxBreite-80, 50, 100, 70);
  ctx.fillStyle = "rgb(230,230,230)";   // Weißer Balken Querdurch
  ctx.fillRect (20, 60, MaxBreite, 50);  
  ctx.strokeStyle = "rgb(0,0,0)";       // Schwarzer äusserer Rahmen
  ctx.strokeRect (20, 50, MaxBreite, 70);
  ctx.strokeRect (20, 60, MaxBreite, 50); // Schwarz innerer Rahmen

  //console.log("Min: " + ContrMinGewicht + " Max: "+ ContrMaxGewicht + " IstWert: "+ IstWert);
  
  if(ContrMaxGewicht == 0 || ContrMinGewicht < 0.3 || ContrMaxGewicht < ContrMinGewicht){
    Text = "-?-";
    TextColor = "rgb(100, 100, 100)"; // Dunkelgrau
  } else {

    // Texte
    ctx.fillStyle = "rgb(0,0,0)";
    ctx.font="16px Arial";
    ctx.textAlign ="center";
    ctx.fillText(Number(ContrMinGewicht).toFixed(1)+configdata.ScaleUnit,120,140);
    ctx.fillText(Number(ContrMaxGewicht).toFixed(1)+configdata.ScaleUnit,MaxBreite-80,140);

    if(IstWert >= ContrMinGewicht && IstWert <= ContrMaxGewicht) {
      // Wert ist in den Grenzen
      AFaktor = (MaxBreite-200) / (Number(ContrMaxGewicht) - Number(ContrMinGewicht));
      xIst = Number((Number(IstWert)-Number(ContrMinGewicht)) * Number(AFaktor) + 120);
      TextColor = "rgb(0, 200, 0)"; // Grün
      Text = "OK";

      // Balken zeichnen
      ctx.fillStyle = "rgb(0,200,0)";   // Grüner Balken
      ctx.fillRect (120, 60, Number(xIst)-120, 50);
      
    } else {
      // Wert ist ausserhalb der Grenzen
      // Unterscheiden, liegt gar nichts auf der Waage oder ist es ein Gewicht ausserhalb der Grenzen
      if(IstWert <= 0.3) {
        //Es liegt nichts auf der Waage
        TextColor = "rgb(200, 200, 200)"; // Grau
        Text = "---";
        xIst = -40;
      } else {
        //Falsches Gewicht
        TextColor = "rgb(255, 0, 0)"; // Rot
        Text = "NOK";      
        if(IstWert < ContrMinGewicht) xIst = 60;
        else xIst = MaxBreite-20;
      }
    }

    ctx.beginPath();                  // vertikale Linie
    ctx.lineWidth = 3;
    ctx.moveTo(xIst, 40);            
    ctx.lineTo(xIst, 130);
    ctx.stroke();
    // Pfeil für IstMenge einzeichnen
    ctx.fillStyle = "rgb(0,0,200)";
    ctx.beginPath();                    // Pfeil Oben
    ctx.moveTo(xIst, 50);
    ctx.lineTo(xIst+10, 10);
    ctx.lineTo(xIst-10, 10);
    ctx.fill();
    ctx.beginPath();                    // Pfeil Unten
    ctx.moveTo(xIst, 120);
    ctx.lineTo(xIst+10, 160);
    ctx.lineTo(xIst-10, 160);
    ctx.fill();
  }
  document.getElementById("CheckScale_OKNOK").style.color = TextColor;
  document.getElementById("CheckScale_OKNOK").innerText = Text; 

}

////////////////////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen
////////////////////////////////////////////////////////////////////////////////////////////

// List zuerst die aktuellen Configwerte aus dem Dialog und schreibt anschließend die aktuellen 
// Configurationseinstellungen aus dem Config-Dialog in die Waage (per JSON-String)
function WriteConfig() {
  var i;
  var radioButtons;
  // Werte aus Dialog auslesen
  configdata.Name = document.getElementById("CFG_iName").value;
  configdata.SSID = document.getElementById("CFG_iSSID").value;
  configdata.APIP = document.getElementById("CFG_iAPIP").value;
  configdata.APgateway = document.getElementById("CFG_iGateway").value;
  configdata.APsubnetmask = document.getElementById("CFG_iSubnetmask").value;
  configdata.ScaleMaxRange = document.getElementById("CFG_iMaxRange").value;
  configdata.ScaleSteps = document.getElementById("CFG_iSchrittweite").value;
  configdata.ScaleTolerance = document.getElementById("CFG_iTolerance").value;
  configdata.ScaleUnit = document.getElementById("CFG_iUnit").value;
  radioButtons = document.getElementsByName("CFG_stdBM");
    for(i = 0; i < radioButtons.length; i++)
    {   if(radioButtons[i].checked == true) 
        { configdata.Defaultmode = i;
          console.log("Default Betriebsmodus: " + i);
        }
    } 
  radioButtons = document.getElementsByName("CFG_stdWIFI");
    for(i = 0; i < radioButtons.length; i++)
    {   if(radioButtons[i].checked == true) 
        { configdata.WiFiMode = i;
          console.log("Default WiFi Modus: " + i);
        }
    }
  
  const pwd = document.getElementById("CFG_iPasswort").value;
  if(pwd.length > 4) { 
    configdata.PWD = pwd;
  } else {
    configdata.PWD = "";
  } 

  // Konfiguration an Waage schicken
  websocket.send(JSON.stringify(configdata));
}

function EGB_AnzahlChange() {
  var x = document.getElementById("EGB_Anzahl");
  var y = document.getElementById("EGB_Gewicht");
  
  if(Number(x.value) != 0) {
    var E = Number(y.value) / Number(x.value);
    document.getElementById("EGB_EinzGewicht").innerText = E.toFixed(2) + configdata.ScaleUnit + "/Stück";  // DialogDaten aktuelisierenx.value
    Einzelgewicht = Number(E);
  } else {
    document.getElementById("EGB_EinzGewicht").innerText = "---";  // DialogDaten aktuelisierenx.value
    Einzelgewicht = +0;
  }
}

function EGB_GewichtChange() {
  var x = document.getElementById("EGB_Anzahl");
  var y = document.getElementById("EGB_Gewicht");
  var E = Number(y.value) / Number(x.value);
    
  if(Number(x.value) != 0) {
    var E = Number(y.value) / Number(x.value);
    document.getElementById("EGB_EinzGewicht").innerText = E.toFixed(2) + configdata.ScaleUnit + "/Stück";  // DialogDaten aktuelisierenx.value
    Einzelgewicht = Number(E.toFixed(0));
  } else {
    document.getElementById("EGB_EinzGewicht").innerText = "---";  // DialogDaten aktuelisierenx.value
    Einzelgewicht = +0;
  } 
}

function KGB_MinGewichtChange() {
  var y = document.getElementById("KGB_MinGewicht");
  var E = Number(y.value);
  ContrMinGewicht = E;
}

function KGB_MaxGewichtChange() {
  var y = document.getElementById("KGB_MaxGewicht");
  var E = Number(y.value);  
  ContrMaxGewicht = E;
}

function resizeCanvas() {
  StandardWeighing(); // Standardeinwaage neu zeichnen
  ComponetWeighing(); // Komponenten Einwaage neu zeichnen
  CountScale(); // Zählwaage auffrischen
  CheckScale();
}

function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen    = onOpen;
  websocket.onclose   = onClose;
  websocket.onmessage = onMessage; // <-- add this line
}

function onOpen(event) {
  console.log('Connection opened');
}

function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}

/********************************
  Folgende Werte müssen als JSON String übergeben werden
    SollWert=100.5;   // Sollwert
    IstWert=97.0;     // Istwert von der Waage
    Toleranz=5;       // Toleranzbereich der Waage
    MaxWert=1000.0;   // Maximalwert der Waage
*********************************/  
function onMessage(event) {
  const json = event.data;
  const obj = JSON.parse(json);

  // In 'Type' steht wohin die Daten gehören

  if(obj.Type == "ACTUALS") {
    IstWert = obj.IstWert; 
    SollWert = obj.SollWert;
    Toleranz = obj.Toleranz;
    MaxWert = obj.MaxWert;

    refreshSite();
    document.getElementById("EGB_IstWert").innerText = IstWert;  // Einzelgewichtsbestimmung DialogDaten aktuelisieren
    document.getElementById("KGB_IstWert").innerText = IstWert;  // Kontrollgrenzenbestimmung DialogDaten aktuelisieren
    document.getElementById("CountScale_IstWert").innerText = Number(IstWert).toFixed(1); 
    document.getElementById("CheckScale_IstWert").innerText = Number(IstWert).toFixed(1);
  } else if(obj.Type =="CONFIG") {
    // Config Daten empfangen
    console.log("Konfigurationsdaten: " + obj);

    var radioButtons;
    // Werte aus Dialog auslesen
    document.getElementById("CFG_iName").value = configdata.Name = obj.Name;
    document.getElementById("CFG_iSSID").value = configdata.SSID = obj.SSID;
    document.getElementById("CFG_iAPIP").value = configdata.APIP = obj.APIP;
    document.getElementById("CFG_iGateway").value = configdata.APgateway = obj.APgateway;
    document.getElementById("CFG_iSubnetmask").value = configdata.APsubnetmask = obj.APsubnetmask;
    document.getElementById("CFG_iMaxRange").value = configdata.ScaleMaxRange = obj.ScaleMaxRange;
    document.getElementById("CFG_iSchrittweite").value = configdata.ScaleSteps = obj.ScaleSteps;
    document.getElementById("CFG_iTolerance").value = configdata.ScaleTolerance = obj.ScaleTolerance;
    document.getElementById("CFG_iUnit").value = configdata.ScaleUnit = obj.ScaleUnit;

    configdata.Defaultmode = obj.Defaultmode;
    radioButtons = document.getElementsByName("CFG_stdBM");
    radioButtons[configdata.Defaultmode].checked = true;
    if(Betriebsmodus != configdata.Defaultmode) {
      Betriebsmodus = configdata.Defaultmode;
      refreshSite();
    }
    configdata.WiFiMode = obj.WiFiMode;
    radioButtons = document.getElementsByName("CFG_stdWIFI");
    radioButtons[configdata.WiFiMode].checked = true; 

  } else console.log("Unbekannte Daten empfangen: " + obj);

}

/////////////////////////////////////////////////////////////
// Abhängig vom Betriebsmodus die Seite neu aufbauen
function refreshSite() {
  switch(Betriebsmodus) {
    case 0: // Standardmodus
      document.getElementById("StandardWeighingDialog").style.display = 'block';
      document.getElementById("ComponentWeighingDialog").style.display = 'none';
      document.getElementById("CountScaleDialog").style.display = 'none';
      document.getElementById("CheckScaleDialog").style.display = 'none';  
      StandardWeighing(); // Standardeinwaage neu zeichnen
      break;
    case 1: // Komponennteneinwaage
    document.getElementById("StandardWeighingDialog").style.display = 'none';
      document.getElementById("ComponentWeighingDialog").style.display = 'block';
      document.getElementById("CountScaleDialog").style.display = 'none';
      document.getElementById("CheckScaleDialog").style.display = 'none'; 
      ComponetWeighing(); // Komponenten Einwaage neu zeichnen
      break;
    case 2: // Zählmodus
      document.getElementById("StandardWeighingDialog").style.display = 'none';
      document.getElementById("ComponentWeighingDialog").style.display = 'none';
      document.getElementById("CountScaleDialog").style.display = 'block';
      document.getElementById("CheckScaleDialog").style.display = 'none';
      CountScale();  // Zählwaage zeichnen
      break;
      case 3: // Kontrollwaage
    document.getElementById("StandardWeighingDialog").style.display = 'none';
      document.getElementById("ComponentWeighingDialog").style.display = 'none';
      document.getElementById("CountScaleDialog").style.display = 'none';
      document.getElementById("CheckScaleDialog").style.display = 'block'; 
      CheckScale();  // Kontrollwaage zeichnen
      break;
    default:
      break;
  }
  
}
  
function onLoad(event) {
  document.getElementById("Menurow").style.display = "none"; // Menuzeile ausblenden
  document.getElementById("StandardWeighingDialog").style.display = 'none';
  document.getElementById("ComponentWeighingDialog").style.display = 'none';
  document.getElementById("CountScaleDialog").style.display = 'none';
  document.getElementById("CheckScaleDialog").style.display = 'none'; 
  initWebSocket();
  initButton();
  //refreshSite(); // Es wird auf die configuration gewartet. Vorher wird ncihts angezeigt
}

function initButton() {
  // Buttons in der Hauptzeile
  document.getElementById('btn_betriebsmodus').addEventListener('click', betriebsmodus_click);
  document.getElementById('btn_einstellungen').addEventListener('click', einstellungen_click);
  //document.getElementsByClassName("close")[0].addEventListener('click', close_modal_click); 
  document.getElementById('x_btn_BMA').addEventListener('click', close_modal_BMA_click);
  document.getElementById('x_btn_EGB').addEventListener('click', close_modal_EGB_click);
  document.getElementById('x_btn_KGB').addEventListener('click', close_modal_KGB_click);
  document.getElementById('x_btn_config').addEventListener('click', close_modal_config_click);
  //document.getElementById('x_btn_KGB').addEventListener('click', close_modal_KGB_click);

  // Buttons in Komponennten Dialog
  document.getElementById('btn_tarieren').addEventListener('click', tarieren_click);
  document.getElementById('btn_ok').addEventListener('click', ok_click);

  // Buttons aus Standard Dialog
  document.getElementById('std_btn_tarieren').addEventListener('click', std_tarieren_click);
  document.getElementById('std_btn_ok').addEventListener('click', std_ok_click);
  document.getElementById('std_btn_clear').addEventListener('click', std_clear_click);

  // Buttons aus Zählwaage Dialog
  document.getElementById('CS_btn_Definieren').addEventListener('click', CS_Definition_click);
  document.getElementById('CS_btn_tarieren').addEventListener('click', std_tarieren_click);

  // Buttons aus Kontrollwaage Dialog
  document.getElementById('CNTR_btn_Definieren').addEventListener('click', CNTR_Definition_click);
  document.getElementById('CNTR_btn_tarieren').addEventListener('click', std_tarieren_click);
  
  // Buttons aus Einzelgewichtsbestimmungs Dialog
  document.getElementById('EGB_btn_Uebern').addEventListener('click', EGB_uebernehmen_click);
  document.getElementById('EGB_btn_Tare').addEventListener('click', std_tarieren_click);
  
  // Buttons aus Kontrollgrenzenbestimmungs Dialog
  document.getElementById('KGB_btn_MinGewichtUebern').addEventListener('click', KGB_MinGewichtUebern_click);
  document.getElementById('KGB_btn_MaxGewichtUebern').addEventListener('click', KGB_MaxGewichtUebern_click);

  // Buttons aus Konfigurations Dialog
  document.getElementById('CFG_btn_Save').addEventListener('click', CFG_Save_click);
}

// Buttons in der Top Navigation
function betriebsmodus_click(){
  document.getElementById("BetriebsmodusAuswahl").style.display = "block";
  document.getElementById("Menurow").style.display = "none";
}
function einstellungen_click(){
  document.getElementById("Konfiguration").style.display = "block";
  document.getElementById("Menurow").style.display = "none";
}

document.getElementById('MenuHook').onmousemove = function(evt) {
  document.getElementById("Menurow").style.display = "block";
  // Menuzeile nach 4 Sekunden wieder ausblenden
  const t = setTimeout(function(){document.getElementById("Menurow").style.display = "none";}, 4000);
}


// Buttons aus Betriebsauswahl Dialog
function close_modal_BMA_click(){
  var radioButtons = document.getElementsByName("Betriebsmodus");
    for(var i = 0; i < radioButtons.length; i++)
    {   if(radioButtons[i].checked == true) 
        { Betriebsmodus = i;
          //console.log("Betriebsmodus: " + Betriebsmodus);
        }
    } 
  document.getElementById("BetriebsmodusAuswahl").style.display = "none";
  refreshSite();  // Ansicht erneuern
}

// Buttons aus Kontrollgrenzenbestimmungs Dialog
function CNTR_Definition_click(){
  document.getElementById("Kontrollgrenzenbestimmung").style.display = "block";
}
function KGB_MinGewichtUebern_click() {
  document.getElementById("KGB_MinGewicht").value = Number(IstWert);
  KGB_MinGewichtChange();
}
function KGB_MaxGewichtUebern_click() {
  document.getElementById("KGB_MaxGewicht").value = Number(IstWert);
  KGB_MaxGewichtChange();
}
function close_modal_KGB_click() {
  document.getElementById("Kontrollgrenzenbestimmung").style.display = "none";
  refreshSite();
}

// Button aus Einzelgewichtsbestimmungs Dialog
function CS_Definition_click(){
  document.getElementById("Einzelgewichtsbestimmung").style.display = "block";
}
function EGB_uebernehmen_click() {
  document.getElementById("EGB_Gewicht").value = Number(IstWert);
  EGB_GewichtChange();
}
function close_modal_EGB_click() {
  document.getElementById("Einzelgewichtsbestimmung").style.display = "none";
  refreshSite();  // Ansicht erneuern
}

// Button aus Konfig Dialog
function close_modal_config_click() {
  // Passwort wieder löschen
  configdata.PWD = ""; // Passwort wird nur übertragen wenn mindestens 4 Zeichen gefüllt sind
  document.getElementById("CFG_iPasswort").value = "";
  
  document.getElementById("Konfiguration").style.display = "none";
  refreshSite();  // Ansicht erneuern 
}
function CFG_Save_click() {
  WriteConfig();  // Configuration übernehmen
}

// Buttons aus Standard Dialog
function std_tarieren_click(){
  websocket.send('tare');
}
function std_ok_click(){
  addValue(IstWert);  // Fügt einen Messwert der Liste hinzu
}
function std_clear_click(){
  Gesamtgewicht = +0;
  var list = document.getElementById('lstValue');
  while (list.firstChild) {
    list.removeChild(list.firstChild);
  }
}
function std_type_click(){
  var radioButtons = document.getElementsByName("STD_Type");
  if(radioButtons[0].checked == true) STD_WType = 0;
  else STD_WType = 1;

  refreshSite();  // Ansicht erneuern
}

// Buttons aus Dual Wiegebalken Dialog
function tarieren_click(){
  websocket.send('tare');
}
function ok_click(){
  websocket.send('tare');
}

</script>
</body>
</html>

)========";
