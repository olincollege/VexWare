int hasRun = 0;

void setup() {
  long baudRate = 9600;
  Serial.begin(baudRate);
  pinMode(21, OUTPUT);
  //Keyboard.begin();
}

void loop() {
  // Check if data is available to read from serial
    if (Serial.available() > 0) {
        String receivedString = Serial.readStringUntil('\n');
        //Serial.println("Received: " + receivedString);
        digitalWrite(21,LOW); // turn on LED 
        delay(1000);
    }
  digitalWrite(21,HIGH); // turn off LED 
  delay(1000);
}

/*
Potential way to recognize operating system:

- install pip on ubuntu on the local user, without sudo permissions
- use pip to install pyserial
- download python script to send signals over serial to USB ports
- Run python script
- Stop keyboard emulation on Arduino and begin serial reads
- If serial signal is read, can identify the operating system as Linux.

- somehow signal to the target system that Linux was recognized
- OR:
- Restart keyboard emulation
- Run the appropriate keyboard injection sequence to install files
*/
