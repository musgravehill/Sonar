
///////TODO PORTBDC read pin2 state 0\1, dont use slow digitalRead
const uint8_t SONAR_pin = 2; //interrupt #0
volatile uint32_t SONAR_timeAllowListen_mks = 1L; //time to next listen sync after previous syncOk
volatile uint32_t SONAR_pulseStart_mks = 1L; //time the pulse started. Used in calculation of the pulse length
volatile uint8_t SONAR_state = 1; //1=sync process 2=depth process
volatile uint32_t SONAR_pulseDepthLength_mks = 1; //mks for sonar depth
#define SONAR_allowNextSync_mks 244450  //min time to get new sync-pulse  (sonar send data 3-4Hz)
#define SONAR_depthMax_mks 58111

//================================== TIMEMACHINE =================================================================
uint32_t TIMEMACHINE_next_311ms = 0L;


void setup() {
  DDRD &= ~(1 << PD2); //set d2 input
  attachInterrupt(0, SONAR_ISR, CHANGE);
  Serial.begin(57600);
}

void loop() {
  TIMEMACHINE_loop();
}

void SONAR_ISR() {
  uint32_t mcrs = micros();
  if (SONAR_state == 1 && SONAR_timeAllowListen_mks > mcrs) {
    return;  //waiting for Sync, but time too less from prev syncOk
  }

  if (SONAR_state == 1) { //sync
    if (PIND & (1 << PD2)) { //sync time start at rising => d2 is high
      SONAR_pulseStart_mks = mcrs;
    }
    else { //sync time finish at falling
      uint32_t delta_mks = mcrs - SONAR_pulseStart_mks;
      if (delta_mks > 6660 && delta_mks < 6700) {
        SONAR_state = 2;
        SONAR_timeAllowListen_mks = mcrs + SONAR_allowNextSync_mks;
        SONAR_pulseStart_mks = mcrs;
      }
    }
  }

  if (SONAR_state == 2) { //depth
    if (PIND & (1 << PD2)) { //rising => d2 is high
      uint32_t delta_mks = mcrs - SONAR_pulseStart_mks;
      SONAR_state = 1;
      if (delta_mks > 800 && delta_mks < SONAR_depthMax_mks) {
        SONAR_pulseDepthLength_mks = delta_mks;
      } else {
        SONAR_pulseDepthLength_mks = 1;
      }
    }
  }

}
