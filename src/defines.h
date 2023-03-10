//*----------------------------------------------------------------------------
// defines.h
//*----------------------------------------------------------------------------
#pragma once
//*----------------------------------------------------------------------------
#include <Arduino.h>
#include <stdint.h>
//*----------------------------------------------------------------------------
// SWITCHES
//*----------------------------------------------------------------------------
#define SHOW_CORES      1
#define SHOW_DIR        0
#define DO_TEST_CRYPT   0
#define COM_DEBUG       0
//*----------------------------------------------------------------------------
// DEFINITIONEN
//*----------------------------------------------------------------------------
#define ATTR_ALIGNED(Bytes) __attribute__ ((aligned(Bytes)))
#define PACKED              __attribute__ ((packed))
#define WEAK                __attribute__ ((weak))
#ifndef MIN
  #define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif  
#define C(s) (char *)s
//*----------------------------------------------------------------------------
// TYPEDEFS
//*----------------------------------------------------------------------------
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef int32_t  vs32;
typedef int16_t  vs16;
typedef int8_t   vs8;

typedef int32_t vsc32;  /*!< Read Only */
typedef int16_t vsc16;  /*!< Read Only */
typedef int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef uint8_t  byte;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef uint32_t  vu32;
typedef uint16_t vu16;
typedef uint8_t  vu8;

typedef uint32_t vuc32;  /*!< Read Only */
typedef uint16_t vuc16;  /*!< Read Only */
typedef uint8_t vuc8;   /*!< Read Only */
//*----------------------------------------------------------------------------
// PORT DEFINES
//*----------------------------------------------------------------------------
#define DEBUG_TX      1
#define DEBUG_RX      3
#define NRF_CE        4
#define NRF_CS        5
#define NRF_INT       16
#define NRF_SCK       18
#define NRF_MISO      19
#define I2C_SDA       21
#define I2C_SCL       22
#define NRF_MOSI      23
#define LED_R         32
#define LED_B         33
//*----------------------------------------------------------------------------


