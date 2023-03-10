//*----------------------------------------------------------------------------
// File: main.cpp
//*----------------------------------------------------------------------------
#include "board.h"
#include "erdebug.h"
#include "oled.h"
#include "font.h"
//*----------------------------------------------------------------------------
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "DX-DTU-TEST";
const char* password = "12345678";
//*----------------------------------------------------------------------------
#include <SPI.h>
#include "RF24.h"

RF24 radio(NRF_CE, NRF_CS);
//*----------------------------------------------------------------------------
bool testOk = false;
//*----------------------------------------------------------------------------
// SYSTEM SETUP
//*----------------------------------------------------------------------------
void setup() 
{
  BOARD.begin();
  Serial.begin(115200);
#if SHOW_CORES
  dbg.printf("### %6s::CORE=%d PRIO=%d%r", pcTaskGetName(NULL), xPortGetCoreID(), uxTaskPriorityGet(NULL));
#endif  
  delay(200);
  dbg.printf("%r%s%r", BOARD.HeadStr(30).c_str());
  dbg.printf("  SNR: %s%r", BOARD.Mac2Snr());
  dbg.printf("SYSID: %08X%r", PROG_SYSID);
  dbg.printf(" CODE: %04X%r", PROG_SYSCODE);
  dbg.printf(" HEAP: %d%r", ESP.getFreeHeap());
  dbg.printf("F_CPU: %d MHz%r", ESP.getCpuFreqMHz());

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  bool nrf = radio.begin();
  dbg.printf("nRF24: %s%r", nrf==0 ? "FAIL" : "OK");
  Serial.print(" APIP: ");
  Serial.println(IP);
  dbg.line('-', 30);

  testOk = nrf;

  char fmtText[32];
  OLED.begin();
  OLED.setBrightness(255);
  FONT.setFont(XL_FONT);
  FONT.stringAligned(64, 0, TXT_ALIGN_CENTER, "DX-DTU");
  OLED.hLine(0, 18, 127);
  FONT.setFont(NEW_FONT);
  if(testOk) {
    FONT.stringAligned(64, 22, TXT_ALIGN_CENTER, "Selftest: OK");
    FONT.stringAligned(64, 36, TXT_ALIGN_CENTER, "No firmware");
    FONT.stringAligned(64, 50, TXT_ALIGN_CENTER, "Read manual");
  } else {
    FONT.stringAligned(64, 34, TXT_ALIGN_CENTER, "Selftest: FAIL");
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_R, HIGH);
  }  
  OLED.show(); 
}
//*----------------------------------------------------------------------------
// UPLOAD LOOP
//*----------------------------------------------------------------------------
void loop()
{
  if(testOk) {
    vTaskDelay(1000);  
  } else {  
    digitalWrite(LED_R, LOW);
    vTaskDelay(100);  
    digitalWrite(LED_R, HIGH);
    vTaskDelay(100);  
  }
}
//*----------------------------------------------------------------------------

