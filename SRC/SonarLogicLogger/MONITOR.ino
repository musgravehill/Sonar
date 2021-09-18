void MONITOR_init() {
  lcd.init();
  lcd.backlight();
}

void MONITOR_render() {
  lcd.clear();
  lcd.setCursor(0, 0);

   

  if (SD_isError) {
    lcd.setCursor(13, 0);
    lcd.print(F("SD?"));
  }


  /*for (byte i = 0; i <= 3; i++) {
    lcd.setCursor(i * 4, 1);
    lcd.print((SONAR_flashes_cm[i] / 100.0), 1);
    }*/

   

}
