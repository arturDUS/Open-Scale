#include <Arduino.h>
#include "EEPROM.h"             // Used to store configuration and recipe in flash


#define MAX_NAME_LENGTH 20

//////////////////////////////////////////////////////////////////////////
// Rezepte für z.B. Epoxymischverhältnisse oder einfache chemische Verbindungen
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
