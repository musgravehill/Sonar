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
    lcd.setCursor(14, 0);
    lcd.print(F("SD?"));
  }

  for (byte i = 0; i <= SONAR_depths_idx_max; i++) {
    lcd.setCursor(i * 2, 1);
    lcd.print((SONAR_depths_cm[i] / 100.0), 0);
  }

  //lcd.setCursor(0, 1);
  //lcd.print((SONAR_depth_curr_cm/ 100.0), 1);

}
