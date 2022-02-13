void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();   
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_3911ms) {
    TIMEMACHINE_3911ms();
    TIMEMACHINE_next_3911ms = TIMEMACHINE_currMillis + 3911L;
  }
}

void TIMEMACHINE_3911ms() {
  MONITOR_render();
}
