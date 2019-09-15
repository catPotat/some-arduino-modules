int espin = 13;
   
void listen2esp() {
  if (digitalRead(espin)==HIGH) {
    while (Serial.available() > 0 ) {
      char cmd = Serial.read();
      recieveCMD(cmd);
    }
  }
}

void recieveCMD(char esp) {
  if (esp == 'L') { lightON(); }
  if (esp == 'l') { lightOFF(); }
  if (esp == 'p') { fPower(); }
  if (esp == 's') { fSpeed(); }
  if (esp == 'o') { fOscil(); }
  if (esp == 't') { fTimer(); }
  if (esp == 'C') { openCurtain(); }
  if (esp == 'c') { closeCurtain(); }
}
