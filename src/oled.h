//*----------------------------------------------------------------------------
// oled.h
//*----------------------------------------------------------------------------
#include <Wire.h>
#include "defines.h"
//*----------------------------------------------------------------------------
#pragma once
//*----------------------------------------------------------------------------
#define OLED_I2C_ADDRESS  0x3C
//*----------------------------------------------------------------------------
#define OLED_WIDTH        128 // OLED display width, in pixels
#define OLED_HEIGHT       64  // OLED display height, in pixels 
#define OLED_BUFSIZE      (OLED_WIDTH * (OLED_HEIGHT / 8))
//*----------------------------------------------------------------------------
#define SSD1306_SETCONTRAST               0x81
#define SSD1306_DISPLAYALLON_RESUME       0xA4
#define SSD1306_DISPLAYALLON              0xA5
#define SSD1306_NORMALDISPLAY             0xA6
#define SSD1306_INVERTDISPLAY             0xA7
#define SSD1306_DISPLAYOFF                0xAE
#define SSD1306_DISPLAYON                 0xAF
#define SSD1306_SETDISPLAYOFFSET          0xD3
#define SSD1306_SETCOMPINS                0xDA
#define SSD1306_SETVCOMDETECT             0xDB
#define SSD1306_SETDISPLAYCLOCKDIV        0xD5
#define SSD1306_SETPRECHARGE              0xD9
#define SSD1306_SETMULTIPLEX              0xA8
#define SSD1306_SETLOWCOLUMN              0x00
#define SSD1306_SETHIGHCOLUMN             0x10
#define SSD1306_SETSTARTLINE              0x40
#define SSD1306_MEMORYMODE                0x20
#define SSD1306_COLUMNADDR                0x21
#define SSD1306_PAGEADDR                  0x22
#define SSD1306_COMSCANINC                0xC0
#define SSD1306_COMSCANDEC                0xC8
#define SSD1306_SEGREMAP                  0xA0
#define SSD1306_CHARGEPUMP                0x8D
#define SSD1306_EXTERNALVCC               0x1
#define SSD1306_SWITCHCAPVCC              0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL           0x2F
#define SSD1306_DEACTIVATE_SCROLL         0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA  0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL   0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL    0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A  
//*----------------------------------------------------------------------------
// MyOLED class
//*----------------------------------------------------------------------------
class OledClass {
  private:
    void writeCom(u8 cmd);
    //...........................................................    
    int bufsize = OLED_BUFSIZE;
    bool invert = false; 
    u8 buf[OLED_BUFSIZE];
  public:
    bool begin();  
    void clear(u8 pattern = 0);
    void setBrightness(uint8_t brightness);
    void setContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect);
    void show();
    void setInvert(bool b);
    void setPixel(int lx, int ly);
    void clrPixel(int lx, int ly);
    void hLine(u8 lx1, u8 ly, u8 lx2);
    void vLine(u8 lx, u8 ly1, u8 ly2);
    void frame(u8 lx1, u8 ly1, u8 lx2, u8 ly2);
    void rect(u8 lx1, u8 ly1, u8 lx2, u8 ly2);
    void bar(u8 lx1, u8 ly, u8 lx2, u32 max, u32 pos);
    //...........................................................    
    int width   = OLED_WIDTH;    
    int height  = OLED_HEIGHT;
};

extern OledClass OLED;
//*----------------------------------------------------------------------------
