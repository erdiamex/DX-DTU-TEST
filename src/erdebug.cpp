//*----------------------------------------------------------------------------
// ERDEBUG.CPP
//*----------------------------------------------------------------------------
#include <Arduino.h>
#include "erdebug.h"
#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf.h"
//*----------------------------------------------------------------------------
DebugClass  dbg;
//*----------------------------------------------------------------------------
const char HX[] = "0123456789ABCDEF";
//*----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//*----------------------------------------------------------------------------
// void send
//*----------------------------------------------------------------------------
void DebugClass::send(u8 val)
{
  Serial.write(val);
}  
//*----------------------------------------------------------------------------
// void hex
//*----------------------------------------------------------------------------
void DebugClass::hex(u32 val, u8 type)
{
  val <<= (32 - type);
  while(type) {
    send(HX[val >> 28]);
    val <<= 4;
    type -= 4;
  }
}
//*----------------------------------------------------------------------------
// void line
//*----------------------------------------------------------------------------
void DebugClass::line(char ch, int cnt)
{
	while(cnt--) {
		send(ch);
	}
  send(13);
  send(10);
}
//*----------------------------------------------------------------------------
// void dump
//*----------------------------------------------------------------------------
void DebugClass::dump(u8 *adr, u32 anz)
{
  u32 blk = anz / 16;
  u32 ln, i;
  u8  c;

  if((blk * 16) != anz) { blk++; }

  for(ln = 0; ln < blk; ln++) {
    hex((u32)adr, 32);
    send(':');
    for(i = 0; i < 16; i++) {
      send(' ');
      if(ln * 16 + i < anz) { hex(*(adr + i), 8); }
                       else { send('.'); send('.');    }
    }
    send(' '); send(' ');
    for(i = 0; i < 16; i++) {
      if(ln * 16 + i < anz) {
        c = *(adr + i);
        if((c < 0x20) || (c > 0x7F)) { c = '.'; }
        send(c);
      }
    }
    adr += 16;
    send(13);
    send(10);
  }
}
//*----------------------------------------------------------------------------
// PRINTF
//*----------------------------------------------------------------------------
static void serout(int c, void *ctx = NULL) 
{ 
  Serial.write(c); 
}

int DebugClass::printf(const char *format, ...)
{
  va_list val;
  va_start(val, format);
  int const rv = npf_vpprintf(&serout, NULL, format, val);
  va_end(val);
  return rv; 
}  
//*----------------------------------------------------------------------------
// SNPRINTF
//*----------------------------------------------------------------------------
int DebugClass::snprintf(char *out, unsigned int count, const char *format, ...)
{
  va_list val;
  va_start(val, format);
  int const rv = npf_vsnprintf(out, count, format, val);
  va_end(val);
  return rv; 
}  
//*----------------------------------------------------------------------------
