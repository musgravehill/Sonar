void SD_logData() {
  if (GPS_isNewData) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    if (flat != TinyGPS::GPS_INVALID_F_ANGLE && flon != TinyGPS::GPS_INVALID_F_ANGLE && SONAR_isValid) {
      myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
      if (myFile) {
        myFile.print(flat, 6);
        myFile.print(';');
        myFile.print(flon, 6);
        myFile.print(';');
        myFile.println(SONAR_depth_curr_cm);
        myFile.close();
        GPS_isNewData = false;
        SD_records_count++;
      } else {
        SD_isError = true;
      }
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