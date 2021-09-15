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
  SD_logData();
  
}

void TIMEMACHINE_911ms() {
  MONITOR_render();
}
