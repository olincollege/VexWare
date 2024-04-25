/* 
Test opening command prompt on Windows as administrator

Keystroke sequence:
- WIN
- "command"
- RIGHT ARROW
- DOWN ARROW
- ENTER KEY
- LEFT ARROW
- ENTER KEY
*/
#include <Keyboard.h>

int hasRun = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  delay(800);
  //if the button is pressed
  if (digitalRead(2) == LOW) {
    if (hasRun == 0) {
    // Begin keystroke sequence
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.print("command");
    delay(500); // let animation play

    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(2500); // let animation play, UAC takes forever to come up

    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    //Keyboard.end(); // end keyboard emulation
    hasRun = 1;
    }
  }
}