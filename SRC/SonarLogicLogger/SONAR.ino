
//listen N pulses Rising and Falling after Sync
void SONAR_ISR() {
  if (SONAR_isProcessTodo) {
    return;  //waiting for SD log
  }
  uint32_t mcrs = micros();
  if (SONAR_state == 1 && SONAR_timeAllowListen_mks > mcrs) {
    return;  //waiting for Sync, but time too less from prev syncOk
  }

  uint32_t delta_mks = mcrs - SONAR_syncEnd_mks;

  //=============SYNC start-end process================
  if (SONAR_state == 1) {
    SONAR_syncEnd_mks = mcrs;
    if (PIND & (1 << PD2)) { //sync time start at rising => d2 is high

    }
    else { //sync time finish at falling ====SYNC end
      if (delta_mks > 6660 && delta_mks < 6700) {  //sync pulse w = 6680 mks
        SONAR_state = 2; //listen for depth pulses
        SONAR_timeAllowListen_mks = mcrs + SONAR_allowNextSync_mks; //after this time allow to listen for next SYNC
      }
    }
    return;
  }

  //==============DEPTH pulses measure===========================
  if (SONAR_state == 2) {
    if (delta_mks <= SONAR_depthMax_mks) {
      if (PIND & (1 << PD2)) { //rising => d2 is high
        SONAR_pulses_rising[SONAR_pulses_rising_idx] = delta_mks;
        SONAR_pulses_rising_idx++;
        if (SONAR_pulses_rising_idx > SONAR_pulses_rising_idx_max) {
          SONAR_pulses_rising_idx = 0;
        }
      } else { //falling
        SONAR_pulses_falling[SONAR_pulses_falling_idx] = delta_mks;
        SONAR_pulses_falling_idx++;
        if (SONAR_pulses_falling_idx > SONAR_pulses_falling_idx_max) {
          SONAR_pulses_falling_idx = 0;
        }
      }
      else {
        SONAR_isProcessTodo = true; //todo process data from sonar
        SONAR_state = 1; // goto SYNC waiting
      }
      return;
    }
  }

  void SONAR_init() {
    DDRD &= ~(1 << PD2); //set d2 input SONAR_pin
    attachInterrupt(0, SONAR_ISR, CHANGE);
  }
