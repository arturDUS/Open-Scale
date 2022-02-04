/*
 * Grafiken können mit
 *    https://www.online-utility.org/image/convert/to/XBM
 * in das XBM Formt umgewandelt werden
 * Aufruf mit
 *    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
 */

#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
const uint8_t WiFi_Logo_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
  0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
  0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
  0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
  0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
  0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

#define Splash_width 117
#define Splash_height 55
const uint8_t Splash[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
  0x00, 0x80, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x00, 0xC0, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x00, 0xFC, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xC0, 0xFF, 0x01, 0xF0, 0xE3, 
  0xC7, 0xE7, 0x80, 0x1F, 0x9F, 0x07, 0x00, 0x00, 0x00, 0x30, 0xF8, 0xFF, 
  0x01, 0xF0, 0xC1, 0xC7, 0xFF, 0xE1, 0x3F, 0xDF, 0x0F, 0x00, 0x00, 0x00, 
  0xB0, 0xFF, 0xF3, 0x03, 0xF8, 0xC1, 0xC7, 0xFF, 0xF3, 0x3F, 0xFF, 0x0F, 
  0x00, 0x00, 0x00, 0xF0, 0x7F, 0xF0, 0x03, 0xF8, 0xC0, 0xC7, 0xFF, 0xF3, 
  0x7C, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0x07, 0xB8, 0x03, 0xF8, 0xC0, 
  0xE7, 0xE7, 0xFB, 0xBC, 0x9F, 0x0F, 0x00, 0x00, 0xE0, 0xFF, 0x00, 0x38, 
  0x07, 0xF8, 0xC0, 0xE7, 0xE3, 0xFB, 0xBF, 0x8F, 0x07, 0x00, 0x00, 0xFE, 
  0x3F, 0x00, 0x1C, 0x07, 0xF8, 0xE0, 0xE7, 0xE3, 0xFB, 0x9F, 0x8F, 0x07, 
  0x00, 0xC4, 0xFF, 0x79, 0x00, 0x1C, 0x0E, 0xF8, 0xF1, 0xE3, 0xE3, 0xF9, 
  0x87, 0xCF, 0x07, 0x00, 0xFE, 0x1F, 0x78, 0x00, 0x1E, 0x0E, 0xF0, 0xFF, 
  0xE1, 0xF1, 0x79, 0x90, 0xC7, 0x07, 0x00, 0xFE, 0x03, 0x78, 0x00, 0x0E, 
  0x1E, 0xF0, 0xFF, 0xF1, 0xFF, 0xF8, 0xDF, 0xC7, 0x07, 0x00, 0x3F, 0x00, 
  0x78, 0x00, 0x0F, 0x1C, 0xE0, 0x7F, 0xF0, 0x7F, 0xF0, 0xCF, 0xC7, 0x03, 
  0x00, 0x0F, 0x00, 0x78, 0x00, 0x07, 0x1C, 0x80, 0x1F, 0xF0, 0x1F, 0xE0, 
  0xC7, 0xE7, 0x03, 0x80, 0x1F, 0x00, 0x78, 0x00, 0x07, 0x38, 0x00, 0x00, 
  0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x78, 0x80, 0x03, 
  0x38, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3B, 0x00, 
  0x7C, 0x80, 0x03, 0x70, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x39, 0x00, 0x7C, 0xC0, 0x01, 0x70, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x79, 0x00, 0xFC, 0xC0, 0x01, 0xF0, 0x00, 0x00, 
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x70, 0x00, 0xFC, 0xE0, 0x00, 
  0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x70, 0x00, 
  0xFC, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xF0, 0xE0, 0x00, 0xFC, 0xC0, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x70, 0xE0, 0x00, 0xFE, 0xC0, 0xFF, 0x7F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xC0, 0x01, 0xFE, 0xC0, 0xFF, 
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xC0, 0x01, 
  0xFE, 0xC0, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x38, 0xC0, 0x03, 0xFE, 0xC0, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1C, 0x80, 0x03, 0xFE, 0x81, 0xFF, 0x3F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x80, 0x03, 0xFE, 0x81, 0xFF, 
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x07, 
  0xFE, 0x01, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x0E, 0x00, 0x07, 0xFF, 0x01, 0xFE, 0x0F, 0x80, 0x3F, 0x00, 0x00, 0x00, 
  0xF8, 0x00, 0x00, 0x0F, 0x00, 0x0E, 0xFF, 0x01, 0xFC, 0x07, 0xC0, 0x7F, 
  0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xFE, 0xFF, 0x07, 0xFF, 0x01, 0xF8, 
  0x03, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xFE, 0xFF, 0x07, 
  0xFF, 0x01, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 
  0xFE, 0xFF, 0x03, 0xFF, 0x01, 0x00, 0x00, 0xF0, 0x61, 0xF0, 0x83, 0xFF, 
  0x7C, 0xE0, 0x07, 0xFC, 0xFF, 0x03, 0xFF, 0x03, 0x00, 0x00, 0xF0, 0x03, 
  0xFC, 0xE3, 0xFF, 0x7C, 0xF8, 0x0F, 0xFC, 0xFF, 0x83, 0xFF, 0x03, 0x00, 
  0x00, 0xF0, 0x07, 0xFE, 0xF3, 0xFF, 0x3C, 0xFC, 0x0F, 0xFC, 0xFF, 0x83, 
  0xFF, 0x03, 0x00, 0x00, 0xF0, 0x1F, 0xFE, 0xF3, 0xF9, 0x3E, 0x3C, 0x1F, 
  0xF8, 0xFF, 0x81, 0xFF, 0x03, 0x00, 0x00, 0xE0, 0x3F, 0x3F, 0xF8, 0xF8, 
  0x3E, 0x3E, 0x0F, 0xF8, 0xFF, 0x81, 0xFF, 0x03, 0x00, 0x00, 0x80, 0x3F, 
  0x1F, 0xF8, 0x78, 0x3E, 0xFE, 0x0F, 0xF0, 0xFF, 0x80, 0xFF, 0x03, 0x00, 
  0x00, 0x00, 0x3E, 0x0F, 0x78, 0x7C, 0x3E, 0xFE, 0x07, 0xE0, 0x7F, 0x80, 
  0xFF, 0x03, 0x00, 0x00, 0x18, 0x3E, 0x1F, 0x79, 0x7E, 0x1E, 0xFE, 0x01, 
  0xC0, 0x3F, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xF8, 0x3F, 0xFF, 0xF8, 0x7F, 
  0x7F, 0x1E, 0x04, 0x00, 0x06, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0xF8, 0x3F, 
  0xFF, 0xF8, 0x7F, 0x7E, 0xFE, 0x07, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 
  0x00, 0xFC, 0x1F, 0xFE, 0xF8, 0x7D, 0x7E, 0xFC, 0x03, 0x00, 0x00, 0xC0, 
  0xFF, 0x07, 0x00, 0x00, 0xF0, 0x07, 0x7C, 0xF0, 0x7C, 0x7C, 0xF8, 0x01, 
  0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00 };
