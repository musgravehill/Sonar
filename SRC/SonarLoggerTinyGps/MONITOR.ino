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
  lcd.print(flat, 6);
  lcd.print(' ');
  lcd.print(flon, 6);

  lcd.setCursor(0, 1);
  lcd.print((SONAR_getDepth_cm() / 100.0), 2);
  if (SD_isError) {
    lcd.setCursor(8, 1);
    lcd.print(F("SD_ERR"));
  }
}
