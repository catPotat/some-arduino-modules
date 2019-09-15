#include <Servo.h>

Servo curtainServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;

void curtain() {
  curtainServo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void curtainRight() {
  pos += 1;
  curtainServo.write(pos);
  }
  
void curtainLeft() {
  pos -= 1;
  curtainServo.write(pos);
  }

void openCurtain() {
  pos += 1280; 
  curtainServo.write(pos);
}

void closeCurtain() {
  pos -= 1280; 
  curtainServo.write(pos);
}


