

const byte SONAR_pin = 2; //interrupt #0
volatile int pulseLength; //holds the length of the input pulse. volatile because it is updated by the ISR
volatile unsigned long pulseStart = 0; //time the pulse started. Used in calculation of the pulse length
volatile boolean newPulse = false; //flag to indicate that a new pulse has been detected


unsigned long currentTime = 0; //name says it all

void setup()
{
  attachInterrupt(0, SONAR_ISR, CHANGE); //when interrupt 0 (pin 2 of Uno) detects a chanhe of state execute this function
  Serial.begin(57600);
}

void loop() {

}

// the interrupt routine starts here
//it is executed at any time that pin 2 (interrupt 0 on a Uno) changes state.
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
