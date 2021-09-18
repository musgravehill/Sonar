void GPS_serial_process_continuously() {
  while (Serial.available())  {
    char c = Serial.read();
    if (gps.encode(c)) // Did a new valid sentence come in?
       //TODO update global lat, long
  }
}

void GPS_init() {
  Serial.begin(57600);
}
