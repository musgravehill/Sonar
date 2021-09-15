void SD_logData() {
  if (SYS_GPS_isNewData) {
    uint16_t depth = SONAR_getDepth_cm();
    myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
    if (myFile) {
      myFile.println(depth);
      myFile.close();
      SYS_GPS_isNewData = false;
    }else {
      SD_isError = true;
    }
  }
}

void SD_init() {
  if (sd.begin(SD_SS, SPI_SPEED)) {
    myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
    if (myFile) {
      myFile.println(F("NEW"));
      myFile.close();
      SD_isError = false;
    } else {
      SD_isError = true;
    }
  }
}
