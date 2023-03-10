//*----------------------------------------------------------------------------
// FONT.C
//*----------------------------------------------------------------------------
#include "font.h"
#include "oled.h"
#include "NewFont2.h"
#include "tahoma_14.h"
//*----------------------------------------------------------------------------
FontClass FONT;
//*----------------------------------------------------------------------------
// Fordert die Breite in Pixeln des gew�nschten Zeichens an (0 = Error)
//*----------------------------------------------------------------------------
u8 FontClass::getCharWidth(const char c)
{
  if(c < firstchar) { return 0; }
  if(c > lastchar)  { return 0; }
  return widthtab[c - firstchar];
}
//*----------------------------------------------------------------------------
// Breite des Strings ermitteln
//*----------------------------------------------------------------------------
u16 FontClass::getStringWidth(const char *ptr, u8 length)
{
  u16 width = 0;

  while(*ptr) {
    width += getCharWidth(*ptr) + space;
    ptr++;
    if(--length == 0) { break; }
  }
  return width - space;
}
//*----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//*----------------------------------------------------------------------------
// void begin()
//*----------------------------------------------------------------------------
void FontClass::beginFont(u8 *pFont, u8 spc) 
{  
  firstchar  = ((TFONTHEAD *)pFont)->Font_FirstChar; 
  lastchar   = ((TFONTHEAD *)pFont)->Font_LastChar; 
  height     = ((TFONTHEAD *)pFont)->Font_Height; 
  widthtab   = (u8 *)(u32)pFont + sizeof(TFONTHEAD);
  chardata   = widthtab + (lastchar - firstchar + 1);
  x          = 0;      // x-pos
  y          = 0;      // y-pos
  space      = spc;    // space between chars
}
//*----------------------------------------------------------------------------
// setFont
//*----------------------------------------------------------------------------
void FontClass::setFont(int font)
{
  switch(font) {
    //............................................
    case NEW_FONT: 
      beginFont((u8 *)NewFont2, 1);
      break;
    //............................................
    case XL_FONT: 
      beginFont((u8 *)tahoma_14, 1);
      break;
    //............................................
    default:    // Pointer in font
      beginFont((u8 *)font, 1);
      break;
    //............................................
  }
}
//*----------------------------------------------------------------------------
// void setPos
//*----------------------------------------------------------------------------
void FontClass::setPos(int xp, int yp)
{
  x = xp; 
  y = yp; 
}
//*----------------------------------------------------------------------------
// void charDraw
//*----------------------------------------------------------------------------
void FontClass::charDraw(char c)
{
  u8  xp, yp, i = 0;
  u8  bitcount, fdata;
  u16 idx  = 0;
  u16 w    = getCharWidth(c);

  if(w == 0) { return; }    // ungültiges Zeichen, abbruch
  c -= firstchar;           // Zeichen in Tabelle setzen
  while(i < c) { idx += widthtab[i++]; }
  idx *= height;
  bitcount = idx & 0x07;
  idx >>= 3;
  fdata = chardata[idx++] >> bitcount;

  for(xp = 0; xp < w; xp++) {
    for(yp = 0; yp < height; yp++) {
      if(bitcount > 7) {
        fdata = chardata[idx++];
        bitcount = 0;
      }
      if(fdata & 0x01) { OLED.setPixel(x + xp, y + yp); } 
                  else { OLED.clrPixel(x + xp, y + yp); }
      fdata >>= 1;
      bitcount++;
    }
  }
  x += w;
  xp = space;
  while(xp) {
    for(yp = 0; yp < height; yp++) {
      OLED.clrPixel(x, y + yp);
    }
    x++;
    xp--;
  }
}
//*----------------------------------------------------------------------------
// void stringDraw
//*----------------------------------------------------------------------------
void FontClass::stringDraw(const char *ptr)
{
  while(*ptr) { charDraw(*ptr++); }
}
//*----------------------------------------------------------------------------
// void stringAligned
//*----------------------------------------------------------------------------
void FontClass::stringAligned(int xp, int yp, u8 mode, const char *ptr)
{
  y = yp;
  switch(mode) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case TXT_ALIGN_LEFT:
      x = xp;
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case TXT_ALIGN_CENTER:
      x = xp - (getStringWidth(ptr, 0) / 2);
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case TXT_ALIGN_RIGHT:
      x = xp - getStringWidth(ptr, 0);
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }
  stringDraw(ptr);
}
//*----------------------------------------------------------------------------
// void printf
//*----------------------------------------------------------------------------
void FontClass::printf(int xp, int yp, u8 mode, const char *string, ...)
{
  char tmp[128];
  char *ptr = tmp;

  va_list vaArgP;
  va_start(vaArgP, string);
  sprintf(tmp, string, vaArgP);  
  stringAligned(xp, yp, mode, tmp);
}
//*----------------------------------------------------------------------------
