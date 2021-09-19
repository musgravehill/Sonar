void SD_logData_continuously() {
  if (!SONAR_isProcessTodo) {
    return;
  }

  MONITOR_SONAR_pulses_rising_0 = SONAR_pulses_rising[0];
  MONITOR_SONAR_pulses_falling_0 = SONAR_pulses_falling[0];

  myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
  if (myFile) {
    myFile.print(F("R;"));
    for (byte i = 0; i <= SONAR_pulses_rising_idx_max; i++) {
      myFile.print(SONAR_pulses_rising[i], DEC);
      myFile.print(F(";"));
      SONAR_pulses_rising[i] = 0;
    }
    myFile.print(F("F;"));
    for (byte i = 0; i <= SONAR_pulses_falling_idx_max; i++) {
      myFile.print(SONAR_pulses_falling[i], DEC);
      myFile.print(F(";"));
      SONAR_pulses_falling[i] = 0;
    }
    myFile.print(lat_f, 6);
    myFile.print(F(";"));
    myFile.print(lng_f, 6);
    myFile.println();
    myFile.close();
    SD_records_count++;
  } else {
    SD_isError = true;
  }

  SONAR_pulses_rising_idx = 0;
  SONAR_pulses_falling_idx = 0;

  SONAR_isProcessTodo = false;
}

void SD_init() {
  if (sd.begin(SD_SS, SPI_SPEED)) {
    myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
    if (myFile) {
      myFile.println(F("NEW"));
      myFile.close();
      SD_isError = false;
    } else {
      SD_isError = true;
    }
  }
}
