//*----------------------------------------------------------------------------
// oled.cpp
//*----------------------------------------------------------------------------
#include "oled.h"
//*----------------------------------------------------------------------------
OledClass OLED;
//*----------------------------------------------------------------------------
// OLED-INIT-DATA
//*----------------------------------------------------------------------------
const u8 oled_init_data[] = {

  SSD1306_DISPLAYOFF,            // 0xAE
  SSD1306_MEMORYMODE,            // 0x20
  0x10,                          // --> PAGE ADRESSING MODE
  //SSD1306_COMSCANINC,            // 0xC0
  SSD1306_COMSCANDEC,            // 0xC8
  0x00,                          // --> set low column address
  0x10,                          // --> set high column address
  SSD1306_SETSTARTLINE,          // 0x40
  SSD1306_SETCONTRAST,           // 0x81
  0xFF,                          // --> contrast value
  SSD1306_SEGREMAP | 1,          // 0xA0/0xA1
  SSD1306_NORMALDISPLAY,         // 0xA6
  SSD1306_SETMULTIPLEX,          // 0xA8
  OLED_HEIGHT - 1,               // --> set multiplex ratio
  SSD1306_DISPLAYALLON_RESUME,   // 0xA4
  SSD1306_SETDISPLAYOFFSET,      // 0xD3
  0x00,                          // --> set display offset
  SSD1306_SETDISPLAYCLOCKDIV,    // 0xD5
  0xF0,                          // --> set divide ratio
  SSD1306_SETPRECHARGE,          // 0xD9
  0x22,                          // --> set precharge period
  SSD1306_SETCOMPINS,            // 0xDA
  0x12,                          // --> set com pins hardware config
  SSD1306_SETVCOMDETECT,         // 0xDB
  0x20,                          // --> set vcomh
  SSD1306_CHARGEPUMP,            // 0x8D
  0x14,                          // --> set DC-DC enable
  SSD1306_DISPLAYON              // 0xAF 
};
//*----------------------------------------------------------------------------
// LOCAL WRITECOM
//*----------------------------------------------------------------------------
void OledClass::writeCom(u8 cmd)
{
  Wire.beginTransmission(OLED_I2C_ADDRESS);
  Wire.write(0x80); 
  Wire.write(cmd); 
  Wire.endTransmission(); 
}
//*----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//*----------------------------------------------------------------------------
// bool begin()
//*----------------------------------------------------------------------------
bool OledClass::begin() 
{
  //==== INIT I2C AND CHECK FOR DISPLAY ====
	Wire.begin(21, 22);
	Wire.setClock(400000);
  Wire.beginTransmission(OLED_I2C_ADDRESS);
  u8 err = Wire.endTransmission(); 
  if(err) { return false; }

  //==== INIT DISPLAY ====
  for(int i = 0; i < sizeof(oled_init_data); i++) {
    writeCom(oled_init_data[i]);
  } 

  clear(0x00);
  show();

  return true;  
}
//*----------------------------------------------------------------------------
// setContrast
//*----------------------------------------------------------------------------
void OledClass::setContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect) 
{
  writeCom(SSD1306_SETPRECHARGE);   //0xD9
  writeCom(precharge);              //0xF1 default, to lower the contrast, put 1-1F
  writeCom(SSD1306_SETCONTRAST);    // 0x81
  writeCom(contrast);               // 0-255
  writeCom(SSD1306_SETVCOMDETECT);  //0xDB, (additionally needed to lower the contrast)
  writeCom(comdetect);	            //0x40 default, to lower the contrast, put 0
  writeCom(SSD1306_DISPLAYALLON_RESUME);  // 0xA4
  writeCom(SSD1306_NORMALDISPLAY);  // 0xA6
  writeCom(SSD1306_DISPLAYON);      // 0xAF
}
//*----------------------------------------------------------------------------
// setBrightness
//*----------------------------------------------------------------------------
void OledClass::setBrightness(uint8_t brightness) 
{
  uint8_t contrast = brightness;
  if (brightness < 128) {
    // Magic values to get a smooth/ step-free transition
    contrast = brightness * 1.171;
  } else {
    contrast = brightness * 1.171 - 43;
  }
  uint8_t precharge = 241;
  if(brightness == 0) {
    precharge = 0;
  }
  uint8_t comdetect = brightness / 8;
  setContrast(contrast, precharge, comdetect);
}
//*----------------------------------------------------------------------------
// void clear()
//*----------------------------------------------------------------------------
void OledClass::clear(u8 pattern) 
{
  memset((u8 *)buf, pattern, bufsize);
}
//*----------------------------------------------------------------------------
// void show()
//*----------------------------------------------------------------------------
void OledClass::show() 
{
  writeCom(0xB0);
  writeCom(0x00);
  writeCom(0x10);
  
  for(int i = 0; i < bufsize; i++) {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
    Wire.write(0x40);
    for(int x = 0; x < 16; x++) {
      Wire.write(buf[i]);
      i++;
    }
    i--;
    Wire.endTransmission();
  }    
}
//*----------------------------------------------------------------------------
// void setInvert
//*----------------------------------------------------------------------------
void OledClass::setInvert(bool b)
{
  invert = b;
}
//*----------------------------------------------------------------------------
// void setPixel 
// void clrPixel
//*----------------------------------------------------------------------------
static const u8 setTab[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
static const u8 clrTab[8] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };

void OledClass::setPixel(int lx, int ly)
{
  if((lx < 0) || (lx >= width) || (ly >= height)) { return; }   
  if(invert) { buf[((ly / 8) * width) + lx] &=  clrTab[ly & 0x07]; }
              else { buf[((ly / 8) * width) + lx] |=  setTab[ly & 0x07]; }
}               

void OledClass::clrPixel(int lx, int ly)
{
  if((lx < 0) || (lx >= width) || (ly >= height)) { return; }   
  if(invert) { buf[((ly / 8) * width) + lx] |=  setTab[ly & 0x07]; }
              else { buf[((ly / 8) * width) + lx] &=  clrTab[ly & 0x07]; }
}
//*----------------------------------------------------------------------------
// void hLine
//*----------------------------------------------------------------------------
void OledClass::hLine(u8 lx1, u8 ly, u8 lx2)
{
  while(lx1 <= lx2) { setPixel(lx1++, ly); }
}
//*----------------------------------------------------------------------------
// void vLine
//*----------------------------------------------------------------------------
void OledClass::vLine(u8 lx, u8 ly1, u8 ly2)
{
  while(ly1 <= ly2) { setPixel(lx, ly1++); }
}
//*----------------------------------------------------------------------------
// void frame
//*----------------------------------------------------------------------------
void OledClass::frame(u8 lx1, u8 ly1, u8 lx2, u8 ly2)
{
  hLine(lx1, ly1, lx2);
  hLine(lx1, ly2, lx2);
  vLine(lx1, ly1, ly2);
  vLine(lx2, ly1, ly2);
}
//*----------------------------------------------------------------------------
// void rect
//*----------------------------------------------------------------------------
void OledClass::rect(u8 lx1, u8 ly1, u8 lx2, u8 ly2)
{
  for(int yp = ly1; yp <= ly2; yp++) {
    hLine(lx1, yp, lx2);
  }
}
//*----------------------------------------------------------------------------
// void bar
//*----------------------------------------------------------------------------
void OledClass::bar(u8 lx1, u8 ly, u8 lx2, u32 max, u32 pos)
{
  u32 len = (lx2 - lx1 - 2) * pos / max;

  frame(lx1, ly, lx2, ly + 6);
  invert = true;
  rect(lx1 + 2, ly + 2, lx2 - 2,   ly + 4);
  invert = false;
  rect(lx1 + 2, ly + 2, lx1 + len, ly + 4);
}
//*----------------------------------------------------------------------------
