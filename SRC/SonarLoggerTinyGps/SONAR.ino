
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

  //=============SYNC start-end process================
  if (SONAR_state == 1) {
    SONAR_pulseStart_mks = mcrs;
    if (PIND & (1 << PD2)) { //sync time start at rising => d2 is high

    }
    else { //sync time finish at falling ====SYNC end
      if (delta_mks > 6660 && delta_mks < 6700) {  //sync pulse w = 6680 mks
        SONAR_state = 2; //listen for depth pulses
        SONAR_timeAllowListen_mks = mcrs + SONAR_allowNextSync_mks; //after this time allow to listen for next SYNC
      }
    }
  }

  //==============DEPTH pulses measure===========================
  if (SONAR_state == 2) {
    if (PIND & (1 << PD2)) { //rising => d2 is high
      if (delta_mks > 1300 && delta_mks < SONAR_depthMax_mks) {  //depth from ~0.8m to ~40m
        SONAR_pulseDepthLength_mks = delta_mks;
        SONAR_pulseDepthValidLast_mks = mcrs; //time for last valid depth => I can control last valid time
      } else {
        SONAR_pulseDepthLength_mks = 1; //depth pulse not valid
      }
      if (delta_mks >= SONAR_depthMax_mks) { //after SONAR_depthMax_mks swith state to 1 (SYNC start-end process)
        SONAR_state = 1;
      }
    }
  }

}

void SONAR_init() {
  DDRD &= ~(1 << PD2); //set d2 input SONAR_pin
  attachInterrupt(0, SONAR_ISR, CHANGE);
}
