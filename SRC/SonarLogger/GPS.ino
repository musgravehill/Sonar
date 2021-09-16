void GPS_serial_process() {
  if (Serial.available()) {
    //delay(1);  //small delay to allow input buffer to fill
    char c = Serial.read();

    if (c == '$') {
      GPS_GLL_idx = 0; //start chunks, delimiter is ','
      GPS_messageType_idx = 0; //start to wrire string GPGLL, etc
    } else if (c == ',') {
      GPS_GLL_idx++; //next chunks, delimiter is ','
      if (GPS_GLL_idx > 1 && GPS_GLL_idx <= 5) {
        GPS_string_tmp += ';'; //set delimiter ';' between chunks of data
      }
    } else {
      GPS_messageType_idx++; //message length increment
      if (GPS_messageType_idx < 6) {
        GPS_messageType += c; //store begin of gps-message where nmea-type GPGLL, GPRMC, etc
      } else {
        GPS_messageType_idx = 6; //dont allow overflow
      }
      if (GPS_GLL_idx > 0 && GPS_GLL_idx <= 4) { //get chunks 1,2,3,4 from gps-message
        GPS_string_tmp += c;
      }
      if (GPS_GLL_idx == 5) { //my chunks are ready
        GPS_GLL_idx = 6; //set chunks idx to next => message is ready
        if (GPS_string_tmp.length() > 8 && GPS_messageType == "GPGLL") {
          GPS_string = GPS_string_tmp;
          SYS_GPS_isNewData = true;
        }
        GPS_string_tmp = F("");
        GPS_messageType = F("");
      }
    }
    if (GPS_GLL_idx > 6) { //dont allow overflow
      GPS_GLL_idx = 6;
    }

    if (GPS_string.length() > 30 || GPS_string_tmp.length() > 30 ) {
      GPS_string = F("");
      GPS_string_tmp = F("");
      SYS_GPS_isNewData = false;
    }
  }
}

void GPS_init() {
  Serial.begin(57600);
}