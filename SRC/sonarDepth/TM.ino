void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();   
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_311ms) {
    TIMEMACHINE_311ms();
    TIMEMACHINE_next_311ms = TIMEMACHINE_currMillis + 311L;
  }
}


void TIMEMACHINE_311ms() {  
  float depth = SONAR_pulseDepthLength_mks / 1367.0;
  Serial.println(depth, 1);
}
