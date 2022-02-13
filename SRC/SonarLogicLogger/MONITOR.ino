void MONITOR_init() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(F("SonarLogicLogger"));
  delay(1500);
}

void MONITOR_render() {
  lcd.clear();
  switch (MONITOR_screen_num) {
    case 0:
      MONITOR_render_0();
      break;
    case 1:
      MONITOR_render_1();
      break;
    case 2:
      MONITOR_render_2();
      break;
  }
  MONITOR_screen_num++;
  if (MONITOR_screen_num > 2) {
    MONITOR_screen_num = 0;
  }
}

void MONITOR_render_0() {
  lcd.setCursor(0, 0);
  if (SD_isError) {
    lcd.print(F("SD_ERR"));
  } else {
    lcd.print(SD_fileName);
    lcd.print(F(":"));
    lcd.print(SD_records_count);
  }

  lcd.setCursor(0, 1);
  lcd.print(F("R"));
  lcd.print(MONITOR_SONAR_pulses_rising_0);
  lcd.print(F(" F"));
  lcd.print(MONITOR_SONAR_pulses_falling_0);
}

void MONITOR_render_1() {
  lcd.setCursor(0, 0);
  lcd.print(F("LAT "));
  lcd.print(lat_f, 6);

  lcd.setCursor(0, 1);
  lcd.print(F("LNG "));
  lcd.print(lng_f, 6);
}

void MONITOR_render_2() {
  lcd.setCursor(0, 0);
  lcd.print(F("SAT "));
  lcd.print(gps.satellites());

  lcd.setCursor(0, 1);
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  lcd.print(day);
  lcd.print('-');
  lcd.print(month);
  lcd.print('-');
  lcd.print(year);
  lcd.print(' ');
  lcd.print(hour);
  lcd.print(':');
  lcd.print(minute);
}
