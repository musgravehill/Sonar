void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_311ms) {
    TIMEMACHINE_311ms();
    TIMEMACHINE_next_311ms = TIMEMACHINE_currMillis + 311L;
  }
}


void TIMEMACHINE_311ms() {
  SONAR_chechOvertimeFail(); //!!!!!!!!!!
  uint16_t depth = SONAR_getDepth_cm();
  Serial.println(depth);
}
