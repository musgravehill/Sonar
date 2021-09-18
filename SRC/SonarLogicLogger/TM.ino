void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_251ms) {
    TIMEMACHINE_251ms();
    TIMEMACHINE_next_251ms = TIMEMACHINE_currMillis + 251L;
  }
  if (TIMEMACHINE_currMillis > TIMEMACHINE_next_911ms) {
    TIMEMACHINE_911ms();
    TIMEMACHINE_next_911ms = TIMEMACHINE_currMillis + 911L;
  }
}


void TIMEMACHINE_251ms() {  
    
}

void TIMEMACHINE_911ms() {
  MONITOR_render();
}
