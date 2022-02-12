void MONITOR_init() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(F("SonarLogicLogger"));
  delay(1500);
}

void MONITOR_render() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(SD_records_count);
  lcd.print(F("rec "));
  if (SD_isError) {
    lcd.print(F(" SD? "));
  }
  lcd.print(lat_f, 0);
  lcd.print(' ');
  lcd.print(lng_f, 0);

  lcd.setCursor(0, 1);
  lcd.print(F("R"));
  lcd.print(MONITOR_SONAR_pulses_rising_0);
  lcd.print(F(" F"));
  lcd.print(MONITOR_SONAR_pulses_falling_0);

}
