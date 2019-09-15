#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 11, 10 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void kp()
{
  char key = kpd.getKey();
  //if(key) { Serial.println(key); }
  if ( key == '1' ) { toggleLight(); }
  if ( key == '4' ) { fPower(); }
  if ( key == '5' ) { fSpeed(); }
  if ( key == '6' ) { fOscil(); }
  if ( key == '7' ) { fTimer(); }
  if ( key == '2' ) { if (kpd.getState()==HOLD ) {curtainRight();} }
  if ( key == '3' ) { if (kpd.getState()==HOLD ) {curtainLeft();} }
}
