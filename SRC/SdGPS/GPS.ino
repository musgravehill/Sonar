void GPS_serial_process() {
  if (GPS_serial.available()) {
    //delay(1);  //small delay to allow input buffer to fill
    char c = GPS_serial.read();  //gets one byte from serial buffer
    if (c == '$') {
      GPS_GLL_idx = 0;
    } else if (c == ',') {
      GPS_GLL_idx++;
    }
    if (GPS_GLL_idx > 0 && GPS_GLL_idx <= 5) {
      GPS_string_tmp += c;
    }
    if (GPS_GLL_idx > 5) {
      GPS_string = GPS_string_tmp;
      GPS_string_tmp = "";
      SYS_GPS_isNewData = true;
    }
    if (GPS_GLL_idx > 10) {
      GPS_GLL_idx = 10;
    }
  }

  if (SYS_GPS_isNewData) {
    Serial.println(GPS_string);
    SYS_GPS_isNewData = false;
  }
}
