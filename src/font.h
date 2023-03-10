//*----------------------------------------------------------------------------
// FONT.H
//*----------------------------------------------------------------------------
#pragma once
//*----------------------------------------------------------------------------
#include "oled.h"
//*----------------------------------------------------------------------------
// FONT-FUNKTIONSTABELLE
//*----------------------------------------------------------------------------
#define DIGI_FONT         0
#define BIG_FONT          1
#define BOLD_FONT         2
#define NEW_FONT          3
#define XL_FONT           4
//*----------------------------------------------------------------------------
#define TXT_ALIGN_LEFT    0
#define TXT_ALIGN_CENTER  1
#define TXT_ALIGN_RIGHT   2
//*----------------------------------------------------------------------------
// FONT-HEADER
//*----------------------------------------------------------------------------
typedef struct {
  u8  Font_Size_Lo;       // Font size in Bytes LOW
  u8  Font_Size_Hi;       // Font size in Bytes HIGH
  u8  Font_Width;         // Font Width in Pixels
  u8  Font_Height;        // Font Height in Pixels
  u8  Font_BitsPerPixels; // Font Bits per Pixels (nur 1 erlaubt)
  u8  Font_FirstChar;     // Font first char
  u8  Font_LastChar;      // Font last char
} TFONTHEAD;
//*----------------------------------------------------------------------------
// MyFONT class
//*----------------------------------------------------------------------------
class FontClass {
  private:
    u8 *widthtab;         // Zeiger auf die Font-Breitentabelle
    u8 *chardata;         // Zeiger auf die Font-Daten
    u8 firstchar;         // First Char aus Header
    u8 lastchar;          // Last Char aus Header
    u8 height;            // Font Height aus Header
    int x;                // X-Position
    int y;                // Y-Position
    u8 space;             // Space between chars
  public:
    void beginFont(u8 *pFont, u8 spc);
    void setFont(int font);
    void setPos(int xp, int yp);
    void charDraw(char c);
    void stringDraw(const char *ptr);
    void stringAligned(int xp, int yp, u8 mode, const char *ptr);
    void printf(int xp, int yp, u8 mode, const char *string, ...);
    //......................................................
    u8   getCharWidth(const char c);
    u16  getStringWidth(const char *ptr, u8 length);
    //......................................................
};

extern FontClass FONT;
//*----------------------------------------------------------------------------
