//*----------------------------------------------------------------------------
// BOARD.CPP
//*----------------------------------------------------------------------------
#include "board.h"
#include "erdebug.h"
//*----------------------------------------------------------------------------
BoardClass BOARD;
//*----------------------------------------------------------------------------
// BEGIN
//*----------------------------------------------------------------------------
void BoardClass::begin()
{
  //==== BIOSINFO INIT ====
  BiosInfo.SysId    = PROG_SYSID;
  BiosInfo.Version  = PROG_VERSION;
  BiosInfo.SysCode  = PROG_SYSCODE;
  strcpy(BiosInfo.ProgInfo, PROG_NAME);
  esp_efuse_mac_get_default(BiosInfo.Mac);

  //==== INIT PORT DIRECTION ====
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);

  //==== SET PORTS ====
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_R, HIGH);
}
//*----------------------------------------------------------------------------
// Header-String
//*----------------------------------------------------------------------------
String BoardClass::HeadStr(u8 len)
{
  String tmp = " " + String(PROG_NAME)
       + " v" + String(PROG_VERSION / 10, DEC) + 
       "." + String(PROG_VERSION % 10, DEC) + " ";
  int cnt = len - tmp.length();
  for(int i = 0; i < (cnt / 2); i++) { tmp = "=" + tmp; }
  for(int i = 0; i < (cnt / 2); i++) { tmp = tmp + "="; }
  if(cnt & 1) { tmp = tmp + "="; }
  return tmp;
}
//*----------------------------------------------------------------------------
// MAC TO SERIAL
//*----------------------------------------------------------------------------
char *BoardClass::Mac2Snr()
{
  sprintf(Snr, "%02X%02X-%02X%02X-%02X%02X", BiosInfo.Mac[0], BiosInfo.Mac[1],
    BiosInfo.Mac[2], BiosInfo.Mac[3], BiosInfo.Mac[4], BiosInfo.Mac[5]);
  return Snr;  
}
//*----------------------------------------------------------------------------
    