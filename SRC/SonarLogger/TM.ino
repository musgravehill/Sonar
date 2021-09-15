void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_311ms) {
    TIMEMACHINE_311ms();
    TIMEMACHINE_next_311ms = TIMEMACHINE_currMillis + 311L;
  }
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_911ms) {
    TIMEMACHINE_911ms();
    TIMEMACHINE_next_911ms = TIMEMACHINE_currMillis + 911L;
  }
}


void TIMEMACHINE_311ms() {
  SONAR_checkOvertimeFail(); //!!!!!!!!!!

  if (SYS_GPS_isNewData) {
    uint16_t depth = SONAR_getDepth_cm();
    myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
    if (myFile) {
      myFile.println(GPS_string + ';' + depth);
      myFile.close();
      SYS_GPS_isNewData = false;
    }
  }
}

void TIMEMACHINE_911ms() {
  MONITOR_render();
}
