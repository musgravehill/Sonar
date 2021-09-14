void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_311ms) {
    TIMEMACHINE_311ms();
    TIMEMACHINE_next_311ms = TIMEMACHINE_currMillis + 311L;
  }
}


void TIMEMACHINE_311ms() {
  uint16_t depth = SONAR_pulseDepthLength_mks / SONAR_time2depth;
  Serial.println(depth);
}
