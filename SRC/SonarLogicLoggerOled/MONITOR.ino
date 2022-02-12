void MONITOR_init() {
  u8g.setFont(u8g_font_unifont_0_8); //u8g_font_9x15r
  u8g.setFontPosTop();

  u8g.firstPage();
  do {
    u8g.drawStr(0, 0, F("SonarLogicLogger"));
    //u8g.setPrintPos(13, 0);
    //u8g.print(MENU_item_name[MENU_item_num_curr]);
  } while ( u8g.nextPage() );

  delay(1500);
}

void MONITOR_render() {
  /*lcd.clear();
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
  */
}
