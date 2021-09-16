//SD
//MOSI 11
//MISO 12
//CLK 13
//SS 10


#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

#include <SoftwareSerial.h>
SoftwareSerial GPS_serial(8, 9); //RX, TX
String GPS_string = "";
String GPS_string_tmp = "";
uint8_t GPS_GLL_idx = 0;
boolean SYS_GPS_isNewData = false; //after save SD set SYS_GPS_isNewData=false;

// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1
#define SD_SS 10
#define SPI_SPEED SD_SCK_MHZ(4)
#define LOG_FileName "log.txt"

SdFat32 sd;
File32 myFile;

void setup() {
  Serial.begin(57600);
  GPS_serial.begin(57600);

  if (sd.begin(SD_SS, SPI_SPEED)) {
    myFile = sd.open(LOG_FileName, FILE_WRITE);
    if (myFile) {
      myFile.println(F("4 5 6"));
      myFile.close();
    }
  }
}

void loop() {
  GPS_serial_process();

  if (SYS_GPS_isNewData) {
    Serial.println(GPS_string);
    SYS_GPS_isNewData = false;
  }
  
}