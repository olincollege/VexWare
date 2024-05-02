int hasRun = 0;
int powershell_signal;

void setup() {
  pinMode(2, INPUT_PULLUP);
  long baudRate = 9600;
  Serial.begin(baudRate);
  pinMode(RX_LED, OUTPUT);
  //Keyboard.begin();
}

void loop() {
  
  // Check if data is available to read from serial
  if (Serial.available() > 0) {
    // Read the integer from serial
    powershell_signal = Serial.parseInt();
  }
    if (powershell_signal == '1'){
      digitalWrite(LED_RX,LOW); // turn on LED
    }

    }