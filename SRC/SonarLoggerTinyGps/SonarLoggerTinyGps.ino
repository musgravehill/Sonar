///// TODO SONAR depth filter smooth, delete too big,too low depths from current window


#include <stdlib.h>
#include <avr/wdt.h> //wathchdog
#include <stdint.h>

//================================================MONITOR==============
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F  0x27

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

//=============================================== GPS GPRMC===================================================================================
#include <TinyGPS.h>
TinyGPS gps;

//================================================SONAR=================================================================================
//SONAR_pin = 2; //interrupt #0
volatile uint32_t SONAR_timeAllowListen_mks = 1L; //time to next listen sync after previous syncOk
volatile uint32_t SONAR_pulseStart_mks = 1L; //time the pulse started. Used in calculation of the pulse length
volatile uint8_t SONAR_state = 1; //1=sync process 2=depth process
volatile uint32_t SONAR_pulseDepthValidLast_mks = 1; //mks for sonar depth
#define SONAR_allowNextSync_mks 244450  //min time to get new sync-pulse  (sonar send data 3-4Hz)
#define SONAR_failOvertime_mks 2657900 // 265790*10  
#define SONAR_depthMax_mks 57000
#define SONAR_time2depth 13.67 //100cm = 1m
volatile uint16_t SONAR_depths_cm[8]; //0...7 centimeter
volatile uint8_t SONAR_depths_idx = 0; //0...7  

//=================SYS==============
#define SYS_LOG_FileName "log.txt"
boolean SYS_GPS_isNewData = false;

//================================== TIMEMACHINE =================
uint32_t TIMEMACHINE_next_311ms = 0L;
uint32_t TIMEMACHINE_next_911ms = 0L;

void setup() {
  delay(3000);
  MONITOR_init();
  SONAR_init();
  GPS_init();
  SD_init();
}

void loop() {
  wdt_enable (WDTO_2S); //try to have time < 8s, else autoreset by watchdog
  TIMEMACHINE_loop();
  GPS_serial_process();
  wdt_reset();
  wdt_disable();
}
