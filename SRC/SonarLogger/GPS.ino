void GPS_serial_process() {
  if (Serial.available()) {
    //delay(1);  //small delay to allow input buffer to fill
    char c = Serial.read();

    if (c == '$') {
      GPS_GLL_idx = 0;
    } else if (c == ',') {
      GPS_GLL_idx++;
      if (GPS_GLL_idx > 1 && GPS_GLL_idx <= 5) {
        GPS_string_tmp += ';';
      }
    } else {
      if (GPS_GLL_idx > 0 && GPS_GLL_idx <= 4) {
        GPS_string_tmp += c;
      }
      if (GPS_GLL_idx == 5) {
        GPS_GLL_idx = 6;
        GPS_string = GPS_string_tmp;
        GPS_string_tmp = F("");
        SYS_GPS_isNewData = true;
      }
    }
    if (GPS_GLL_idx > 6) {
      GPS_GLL_idx = 6;
    }
  }
}

void GPS_init() {
  Serial.begin(57600); 
}
