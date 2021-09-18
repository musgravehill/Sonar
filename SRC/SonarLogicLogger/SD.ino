void SD_logData_continuously() {
  if (!SONAR_isProcessTodo) {
    return;
  }
  SONAR_isProcessTodo = false;
  myFile = sd.open(SYS_LOG_FileName, FILE_WRITE);
  if (myFile) {    
    myFile.close();     
    SD_records_count++;
  } else {
    SD_isError = true;
  }
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
