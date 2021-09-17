
void SONAR_depth_process_continuously() { //4Hz. My sonar sends data rate 4Hz
  if (!SONAR_isProcessTodo) {
    return;
  }
  if (!SONAR_isValid) {
    return;
  }
  SONAR_isProcessTodo = false;

  uint32_t depth_smooth = 0L;
  for (byte i = 0; i <= SONAR_depths_idx_max; i++) {
    depth_smooth += SONAR_depths_cm[i];
  }

  SONAR_depth_curr_cm = depth_smooth / (SONAR_depths_idx_max + 1);
}

void SONAR_checkOvertimeFail() {
  uint32_t delta_mks = micros() - SONAR_pulseDepthValidLast_mks;
  if (delta_mks > SONAR_failOvertime_mks) {
    SONAR_isValid = false;
  } else {
    SONAR_isValid = true;
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
        SONAR_depth_instant_mks = delta_mks; //store last depth after sync

        //time for last valid depth => I can control last valid time
        SONAR_pulseDepthValidLast_mks = mcrs;

        //flasher
        /*SONAR_flashes_cm[SONAR_depths_idx] = (delta_mks / SONAR_time2depth);
          SONAR_flashes_idx++;
          if (SONAR_flashes_idx > SONAR_flashes_idx_max) {
          SONAR_flashes_idx = 0;
          }*/

      }
      if (delta_mks >= SONAR_depthMax_mks) { //after SONAR_depthMax_mks swith state to 1 (SYNC start-end process)
        SONAR_state = 1; // goto SYNC waiting

        //store last valid depth to array
        if (SONAR_depth_instant_mks > 0) {
          SONAR_depths_cm[SONAR_depths_idx] = (SONAR_depth_instant_mks / SONAR_time2depth);
          SONAR_depths_idx++;
          if (SONAR_depths_idx > SONAR_depths_idx_max) {
            SONAR_depths_idx = 0;
          }
        }

        SONAR_isProcessTodo = true; //todo process data from sonar
      }
    }
  }

}

void SONAR_init() {
  DDRD &= ~(1 << PD2); //set d2 input SONAR_pin
  attachInterrupt(0, SONAR_ISR, CHANGE);
}
