
///////TODO PORTBDC read pin2 state 0\1, dont use slow digitlRead
const uint8_t SONAR_pin = 2; //interrupt #0
volatile uint32_t SONAR_pulseStart_ms = 1L; //time the pulse started. Used in calculation of the pulse length
volatile boolean SONAR_isSyncWaiting = true;
volatile boolean SONAR_isMeasureDepth = false;
volatile uint16_t SONAR_pulseDepthLength_ms = 1;
#define SONAR_allowNextSync_ms 251130  //min time to get new sync-pulse  (sonar send data 3-4Hz)

void setup() {
  attachInterrupt(0, SONAR_ISR, CHANGE);
  Serial.begin(57600);
}

void loop() {

}

void SONAR_ISR() {
  if (digitalRead(rcPin) == HIGH) //if the pin is HIGH
  {
    pulseStart = micros(); //save the current time in microseconds
  }
  else
  {
    if (pulseStart && (newPulse == false)) //otherwise if we are timing and this is not a new pulse
    {
      pulseLength = (int)(micros() - pulseStart); //calculate the pulse length
      pulseStart = 0; //reset the pulse start time to zero
      newPulse = true; //set flag to indicate that we are timing a new pulse
    }
  }
}
