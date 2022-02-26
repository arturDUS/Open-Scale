#include <Arduino.h>
#include "EEPROM.h"             // Used to store configuration and recipe in flash


#define MAX_NAME_LENGTH 20

//////////////////////////////////////////////////////////////////////////
// Rezepte für z.B. Epoxymischverhältnisse oder einfache chemische Verbindungen

struct sMaterial {
  uint8_t number;
  char description[20];
  float density;
  char uom[5];
};

struct sMbrBomPos {
  uint8_t recipenumber;
  uint8_t bompos;
  uint8_t materialnumber;
  char property[20];      // additinal property of the material e.g. warm, hot, clean, ....
  float quantity;
  float tolerance;
};

struct sActivity {
  uint8_t recipenumber;
  uint8_t activitynumber;
  uint8_t activitytype;
  uint8_t parameter1;
  uint8_t parameter2;
  float parameter3;
  uint8_t outputmat;
  char activity[80];
  uint8_t activitystatus;
};

struct sMBR {
  uint8_t recipenumber;
};




// BOM Position
struct sRecipeBomElement {
  uint8_t recipe;
  uint8_t bompos;
  char name[MAX_NAME_LENGTH];
  float quantity;
  float density;
  float tolerance;
  char unit[5];
};




//////////////////////////////////////////////////////////////////////////
// Funktionsprototypen
uint8_t insertBOMPos(uint8_t recipe, uint8_t bompos, char *name, float quantity, float density, float tolerance, char *uint8_t);
//uint8_t deleteBOMPos(uint8_t recipe, uint8_t bompos);
//uint8_t deleteRecipe(uint8_t recipe);
//void WriteRecipe(RecipeBomElement *recipe);
//void ReadRecipe(RecipeBomElement *recipe);
