int i;
byte commandByte;
int isrunning;
unsigned long previousMillis = 0;

void setup() {
  i = 0;
  isrunning = 0;
  Serial.begin(31250);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 4 && isrunning) {
    if (i%6 == 0) {
      i = 0;
      PORTD = PORTD & B00100000;
    }
  }
  do{
    if (Serial.available()){
      commandByte = Serial.read();
      if (commandByte == 0xFA) {
        PORTD = PORTD | B00100000;
        isrunning = 1;
      }
      if (commandByte == 0xF8 && isrunning) {
          PORTD = B10100000;
          previousMillis = millis();
          i += 1;
      }
      if (commandByte == 0xFC) {
        PORTD = B00000000;
        isrunning = 0;
        i = 0;
      }
    }
  }
  while (Serial.available() > 2);
}
