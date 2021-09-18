void MONITOR_init() {
  lcd.init();
  lcd.backlight();
}

void MONITOR_render() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(SD_records_count);
  lcd.print(F("rec"));
  if (SD_isError) {
    lcd.print(F(" SD?"));
  }

  lcd.setCursor(0, 1);
  lcd.print(F("R"));
  lcd.print(SONAR_pulses_rising[0]);
  lcd.print(F(" F"));
  lcd.print(SONAR_pulses_falling[0]);

}
