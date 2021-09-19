void GPS_serial_process_continuously() {
  while (Serial.available())  {
    char c = Serial.read();
    if (gps.encode(c)) { // Did a new valid sentence come in?
      unsigned long age;
      gps.f_get_position(&lat_f, &lng_f, &age);
    }
  }
}

void GPS_init() {
  Serial.begin(57600);
}
