/* 
 Like logic analizer logger  salae
 Write lat,lng and all pulses! Impulses can be analyzed on a computer at home!
 */


#include <stdlib.h>
#include <avr/wdt.h> //wathchdog
#include <stdint.h>

//================================================MONITOR==============
#include <Wire.h>
#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);  // I2C / TWI
uint16_t MONITOR_SONAR_pulses_rising_0 = 0;
uint16_t MONITOR_SONAR_pulses_falling_0 = 0;

//=============================================== GPS GPRMC===================================================================================
#include <TinyGPS.h>
TinyGPS gps;
float lat_f = 0.0, lng_f = 0.0;

//==================================================SD=======================
// MOSI-11 MISO-12 CLK-13 SS-10
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#define SD_FAT_TYPE 1 //1 for FAT16/FAT32 
#define SD_SS 10
#define SPI_SPEED SD_SCK_MHZ(4)
SdFat32 sd;
File32 myFile;
boolean SD_isError = true;
uint16_t SD_records_count = 0;
String SD_fileName;

//================================================SONAR=================================================================================
//SONAR_pin = 2; //interrupt #0
volatile uint32_t SONAR_timeAllowListen_mks = 1L; //time to next listen sync after previous syncOk
volatile uint32_t SONAR_syncEnd_mks = 1L; //time the pulse started. Used in calculation of the pulse length
volatile uint8_t SONAR_state = 1; //1=sync process 2=depth process

volatile uint16_t SONAR_pulses_rising[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile uint8_t SONAR_pulses_rising_idx = 0;
#define SONAR_pulses_rising_idx_max 15

volatile uint16_t SONAR_pulses_falling[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile uint8_t SONAR_pulses_falling_idx = 0;
#define SONAR_pulses_falling_idx_max 15
volatile boolean SONAR_isProcessTodo = false;

#define SONAR_allowNextSync_mks 244450L  //min time to get new sync-pulse  (sonar send data 3-4Hz)
#define SONAR_depthMax_mks 57000

//=================SYS==============



//================================== TIMEMACHINE =================
uint32_t TIMEMACHINE_next_251ms = 0L;
uint32_t TIMEMACHINE_next_911ms = 0L;

void setup() {
  randomSeed(analogRead(0));
  delay(3000);
  MONITOR_init();
  SONAR_init();
  GPS_init();
  SD_init();
}

void loop() {
  wdt_enable (WDTO_2S); //try to have time < 8s, else autoreset by watchdog
  TIMEMACHINE_loop();
  GPS_serial_process_continuously();
  SD_logData_continuously();
  wdt_reset();
  wdt_disable();
}