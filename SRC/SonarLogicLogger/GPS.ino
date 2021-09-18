void GPS_serial_process_continuously() {
  while (Serial.available())  {
    char c = Serial.read();
    if (gps.encode(c)){ // Did a new valid sentence come in?
       //TODO update global lat, long

    //  float flat, flon;  in global
   // unsigned long age;
   // gps.f_get_position(&flat, &flon, &age);
       
    }    
  }
}

void GPS_init() {
  Serial.begin(57600);
}
