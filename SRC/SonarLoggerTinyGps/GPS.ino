void GPS_serial_process() {
  while (Serial.available())  {
    char c = Serial.read();
    if (gps.encode(c)) // Did a new valid sentence come in?
      SYS_GPS_isNewData = true;
  }
}

void GPS_init() {
  Serial.begin(57600);
}
