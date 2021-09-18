///// logic analizer logger  salae =)


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
uint16_t SD_records_count = 0;

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

//=================SYS==============
#define SYS_LOG_FileName "sig.txt"

//================================== TIMEMACHINE =================
uint32_t TIMEMACHINE_next_251ms = 0L;
uint32_t TIMEMACHINE_next_911ms = 0L;

void setup() {
  delay(3000);
  MONITOR_init();
  SONAR_init();
  SD_init();
}

void loop() {
  wdt_enable (WDTO_2S); //try to have time < 8s, else autoreset by watchdog
  TIMEMACHINE_loop();
  SD_logData_continuously();
  wdt_reset();
  wdt_disable();
}
