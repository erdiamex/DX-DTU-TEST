//*----------------------------------------------------------------------------
// ERDEBUG.H
//*----------------------------------------------------------------------------
#pragma once
//*----------------------------------------------------------------------------
#include <stdarg.h>
#include "defines.h"
//*----------------------------------------------------------------------------
// DEBUG CLASS
//*----------------------------------------------------------------------------
class DebugClass {
  private:
  public:
    //...........................................
    void send(u8 val);
    void hex(u32 val, u8 type);
    void dump(u8 *adr, u32 anz);
    void line(char ch, int cnt);
    //...........................................
    int printf(const char *format, ...);
    int snprintf(char *out, unsigned int count, const char *format, ...);
    //...........................................
};

extern DebugClass dbg;
//*----------------------------------------------------------------------------


