//MOSI - pin 11
//MISO - pin 12
//CLK - pin 13


#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1
const uint8_t chipSelect = 10;
#define SPI_SPEED SD_SCK_MHZ(4)

SdFat32 sd;
File32 myFile;

void setup() {
  if (sd.begin(chipSelect, SPI_SPEED)) {
    myFile = sd.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("testing 1, 2, 3.");
      myFile.close();
    }
  }
}

  void loop() {


  }
