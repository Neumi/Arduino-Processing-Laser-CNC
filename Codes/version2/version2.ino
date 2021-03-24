
int nextStepX = 1;
int backStepX = 1;

int nextStepY = 1;
int backStepY = 1;

int laserTime = 5;  // 2ms for PCB photoresist!!

int stepPinX = 6;
int dirPinX = 7;
int stepPinY = 8;
int dirPinY = 9;
int laserPin = 13;

String contentString;

void setup() {
  Serial.begin(57600);

  pinMode(stepPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(laserPin, OUTPUT);

}

void loop() {

  while (Serial.available() > 0) {
    String RawRead = Serial.readStringUntil('\n');
    String BackWay = RawRead.substring(300);
    contentString = RawRead.substring(0, 300);

    for (int i = 0; i <= 300; i++) {
      if (contentString[i] == '1') { //when string contains a black pixel at the current point...
        digitalWrite(laserPin, HIGH);    //set laser high
        doStepY(0);   // do next step
        delay(laserTime); // wait for the time the laser should burn
      }
      else {
        digitalWrite(laserPin, LOW);   // set/keep laser off
        doStepY(0);
      }
    }
    doStepX(1);

    for (int i = 0; i <= 300; i++) { //get threw the lines in reversed orientation...
      if (BackWay[i] == '1') {
        digitalWrite(laserPin, HIGH);
        doStepY(1);
        delay(laserTime);
      }
      else {
        digitalWrite(laserPin, LOW);
        doStepY(1);
      }
    }
    doStepX(1); // to step next for the laser mechanic
    Serial.write("k"); //write feedback for processing
  }
}


void doStepX(boolean dir) {
  digitalWrite(dirPinX, dir);
  digitalWrite(stepPinX, HIGH);
  delay(2);
  digitalWrite(stepPinX, LOW);
  delay(2);

}
void doStepY(boolean dir) {
  digitalWrite(dirPinY, dir);
  digitalWrite(stepPinY, HIGH);
  delay(2);
  digitalWrite(stepPinY, LOW);
  delay(2);
}
