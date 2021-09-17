void MONITOR_init() {
  lcd.init();
  lcd.backlight();
}

void MONITOR_render() {
  lcd.clear();
  lcd.setCursor(0, 0);

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  if (flat != TinyGPS::GPS_INVALID_F_ANGLE && flon != TinyGPS::GPS_INVALID_F_ANGLE) {
    lcd.print(flat, 4);
    lcd.print(' ');
    lcd.print(flon, 4);
  } else {
    lcd.print(F("GPS?"));
  }

  if (SD_isError) {
    lcd.setCursor(13, 0);
    lcd.print(F("SD?"));
  }


  /*for (byte i = 0; i <= 3; i++) {
    lcd.setCursor(i * 4, 1);
    lcd.print((SONAR_flashes_cm[i] / 100.0), 1);
    }*/

  lcd.setCursor(0, 1);
  lcd.print((SONAR_depth_curr_cm / 100.0), 1);
  lcd.print(F("m "));
  if (!SONAR_isValid) {
    lcd.print(F(" SONAR? "));
  }
  lcd.print(SD_records_count);
  lcd.print(F("pos"));

}
