void MONITOR_init() {
  lcd.init();                      
  lcd.backlight();
}

void MONITOR_render() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("HELLO"));
}
