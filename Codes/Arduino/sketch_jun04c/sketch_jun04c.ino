
int nextStepX = 1;
int backStepX = 1;

int nextStepY = 1;
int backStepY = 1;

int led = 50;

int nikoDelay = 10;  // 2ms for PCB photoresist!!

int testDigInt;
String contentString;



void setup() {
  Serial.begin(57600);
  
  
  pinMode(9, OUTPUT);   //enables for X axis
  pinMode(10, OUTPUT);  //enables for X axis
  digitalWrite(9, HIGH);  //enables for X axis
  digitalWrite(10, HIGH); //enables for X axis
  
  pinMode(3, OUTPUT);  //enables for Y axis
  pinMode(2, OUTPUT);  //enables for Y axis
  digitalWrite(3, HIGH); //enables for Y axis
  digitalWrite(2, HIGH); //enables for Y axis
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  
  
  pinMode(52, INPUT);  //switch
  pinMode(led, OUTPUT);  //laser
}

void loop() {
  
  int x = map(analogRead(A0),0,1023,1,100); //get analog values from potentionometer joystick
  int y = map(analogRead(A1),0,1023,1,100); //get analog values from potentionometer joystick
  
  while (Serial.available() > 0) { // get 01010100110 sting from computer running processing
    String RawRead = Serial.readStringUntil('\n'); //write raw string until end of line
    String BackWay = RawRead.substring(300);  //get the first 300 characters of input string
    
    //Serial.print("I Read: ");
    //Serial.println(BackWay);
    
    String testDigit = RawRead.substring(0,1);  //i have absolutely no idea what this was for :D
    contentString = RawRead.substring(0,300); 
    
    testDigInt = testDigit.toInt();
    //Serial.print("testDig: ");
    //Serial.println(testDigInt);
    
    //Serial.print("String: ");
    //Serial.println(contentString);
    
    digitalWrite(3, HIGH);  //enable stepper motor drivers
    digitalWrite(2, HIGH);  //enable stepper motor drivers
    digitalWrite(9, HIGH);  //enable stepper motor drivers
    digitalWrite(10, HIGH); //enable stepper motor drivers
    
    for (int i=0; i <= 300; i++){ //run threw the lines until the end of range
      //Serial.print(contentString[i]);
      
      
      if(contentString[i] == '1') { //when string contains a black pixel at the current point...
        digitalWrite(led, HIGH);    //set laser high
        //Serial.println("1");

        // not sure if the order is in the right way! maybe wait before doSepY(0); ?? but it workd this way!
        doStepY(0);   // do next step
        delay(nikoDelay); // wait for the time the laser should burn
      }
      else {
        digitalWrite(led, LOW);   // set/keep laser off 
        //Serial.println("0");
        doStepY(0); // do next step
        delay(2);  //2ms for good running behaviour
      }
    }
    doStepX(1); // to step next for the laser mechanic
    
    
    for (int i=0; i <= 300; i++){ //get threw the lines in reversed orientation...
      //Serial.print(contentString[i]);
      
      //same procedure as last time
      if(BackWay[i] == '1') {
        digitalWrite(led, HIGH);
        //Serial.println("1");
        doStepY(1);
        delay(nikoDelay);
      }
      else {
        digitalWrite(led, LOW);
        //Serial.println("0");
        doStepY(1);
        delay(2);
      }
    }
    doStepX(1); // to step next for the laser mechanic
    
    Serial.write("k"); //write feedback for processing
    
  }// end of serial.available
  
  digitalWrite(9, LOW); //disable all motordrivers
  digitalWrite(10, LOW);  //disable all motordrivers
  digitalWrite(3, LOW); //disable all motordrivers
  digitalWrite(2, LOW); //disable all motordrivers
  
  if(digitalRead(52) == HIGH) { //if button is pressed...
    digitalWrite(led, HIGH);  // turn on laser
  }else digitalWrite(led, LOW); //if button is not pressed, turn off laser
  
  
  
  if(x > 60 || x < 40 || y > 60 || y < 40) {  // if joystick is moved enough...
    if(x > 60) {  // move axis when joystick is moved
      doStepX(1);
      //Serial.println("StepX 1");
    }
    if(x < 40) {
      doStepX(0);
      //Serial.println("StepX 0");
    }
    if(x > 40 && x < 60) { //set of X motor drivers, when joystick is not moved enough
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
    else {  //set on X motors, when joystick X axis is moved enough
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
    }
    
    if(y > 60) {  //same for Y axis...
      doStepY(1);
      //Serial.println("StepY 1");
    }
    if(y < 40) {
      doStepY(0);
      //Serial.println("StepY 0");
    }
    if(y > 40 && y < 60) {
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    }
    else {
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
    }
    
    delay(3); // for moveing the steppermotors not to fast, when joystick is moved
  }
  
}

void doStepX(int dirForX) {   //stepper motor function for X axis
  if(dirForX == 1) {
    switch(nextStepX) {
      case 1:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 2;
      backStepX = 8;
      break;
      case 2:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 3;
      backStepX = 1;
      break;
      case 3:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 4;
      backStepX = 2;
      break;
      case 4:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(8, LOW);
      nextStepX = 5;
      backStepX = 3;
      break;
      case 5:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(8, LOW);
      nextStepX = 6;
      backStepX = 4;
      break;
      case 6:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(8, HIGH);
      nextStepX = 7;
      backStepX = 5;
      break;
      case 7:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, HIGH);
      nextStepX = 8;
      backStepX = 6;
      break;
      case 8:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, HIGH);
      nextStepX = 1;
      backStepX = 7;
      break;
    }
  }else {
    switch(backStepX) {
      case 1:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 2;
      backStepX = 8;
      break;
      case 2:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 3;
      backStepX = 1;
      break;
      case 3:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(8, LOW);
      nextStepX = 4;
      backStepX = 2;
      break;
      case 4:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(8, LOW);
      nextStepX = 5;
      backStepX = 3;
      break;
      case 5:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(8, LOW);
      nextStepX = 6;
      backStepX = 4;
      break;
      case 6:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(8, HIGH);
      nextStepX = 7;
      backStepX = 5;
      break;
      case 7:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, HIGH);
      nextStepX = 8;
      backStepX = 6;
      break;
      case 8:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(8, HIGH);
      nextStepX = 1;
      backStepX = 7;
      break;
    }
  }
  
}

void doStepY(int dirForY) {   //stepper motor function for Y axis
  if(dirForY == 1) {
    switch(nextStepY) {
      case 1:
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 2;
      backStepY = 8;
      break;
      case 2:
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 3;
      backStepY = 1;
      break;
      case 3:
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 4;
      backStepY = 2;
      break;
      case 4:
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      nextStepY = 5;
      backStepY = 3;
      break;
      case 5:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      nextStepY = 6;
      backStepY = 4;
      break;
      case 6:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      nextStepY = 7;
      backStepY = 5;
      break;
      case 7:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      nextStepY = 8;
      backStepY = 6;
      break;
      case 8:
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      nextStepY = 1;
      backStepY = 7;
      break;
    }
  }else {
    switch(backStepY) {
      case 1:
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 2;
      backStepY = 8;
      break;
      case 2:
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 3;
      backStepY = 1;
      break;
      case 3:
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      nextStepY = 4;
      backStepY = 2;
      break;
      case 4:
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      nextStepY = 5;
      backStepY = 3;
      break;
      case 5:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      nextStepY = 6;
      backStepY = 4;
      break;
      case 6:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      nextStepY = 7;
      backStepY = 5;
      break;
      case 7:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      nextStepY = 8;
      backStepY = 6;
      break;
      case 8:
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      nextStepY = 1;
      backStepY = 7;
      break;
    }
  }
  
}
