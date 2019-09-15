#include <Wire.h>

void setup() {
  Serial.begin(9600);
  
  //Wire.begin();
  //setTime(22, 30, 45, 7, 29, 10, 16); // gio phut giay thu ngay thang nam
  
  pins4Light(); // 7 and 8
  curtain();
  irRemote();
  acON();
}

void loop() {
  kp();
  listen2esp();
  readDS1307();
  autoLighting();
  delay(300);
}


