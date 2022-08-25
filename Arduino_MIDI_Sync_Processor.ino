int i;
int isRunning;

byte commandByte;

unsigned long previousMillis = 0;

void setup() {
  i = 0;
  isRunning = 0;
  Serial.begin(31250);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 4 && isRunning) {
    if (i%6 == 0) {
      i = 0;
      PORTD = PORTD & B00100000;
    }
  }
  
  do {
    if (Serial.available()) {
      commandByte = Serial.read();
      if (commandByte == 0xFA) {
        PORTD = PORTD | B00100000;
        isRunning = 1;
      }
      if (commandByte == 0xF8 && isRunning) {
          PORTD = B10100000;
          previousMillis = millis();
          i += 1;
      }
      if (commandByte == 0xFC) {
        PORTD = B00000000;
        isRunning = 0;
        i = 0;
      }
    }
  } while (Serial.available() > 2);
}
