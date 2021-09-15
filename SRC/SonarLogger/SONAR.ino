
uint16_t SONAR_getDepth_cm() {
  return SONAR_pulseDepthLength_mks / SONAR_time2depth;
}

void SONAR_checkOvertimeFail() {
  uint32_t delta_mks = micros() - SONAR_pulseDepthValidLast_mks;
  if (delta_mks > SONAR_failOvertime_mks) {
    SONAR_pulseDepthLength_mks = 1; //unknown depth, no signal
  }
}

void SONAR_ISR() {
  uint32_t mcrs = micros();
  if (SONAR_state == 1 && SONAR_timeAllowListen_mks > mcrs) {
    return;  //waiting for Sync, but time too less from prev syncOk
  }

  uint32_t delta_mks = mcrs - SONAR_pulseStart_mks;

  if (SONAR_state == 1) { //sync
    if (PIND & (1 << PD2)) { //sync time start at rising => d2 is high
      SONAR_pulseStart_mks = mcrs;
    }
    else { //sync time finish at falling
      if (delta_mks > 6660 && delta_mks < 6700) {
        SONAR_state = 2;
        SONAR_timeAllowListen_mks = mcrs + SONAR_allowNextSync_mks;
        SONAR_pulseStart_mks = mcrs;
      }
    }
  }

  if (SONAR_state == 2) { //depth
    if (PIND & (1 << PD2)) { //rising => d2 is high
      SONAR_state = 1;
      if (delta_mks > 1300 && delta_mks < SONAR_depthMax_mks) {
        SONAR_pulseDepthLength_mks = delta_mks;
        SONAR_pulseDepthValidLast_mks = mcrs; //time valid depth 
      } else {
        SONAR_pulseDepthLength_mks = 1;
      }
    }
  }

}
