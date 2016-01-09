

int nextStepX = 1;
int backStepX = 1;

int nextStepY = 1;
int backStepY = 1;

int led = 50;

int nikoDelay = 10;  // 2ms f platinen!!

int testDigInt;

String contentString;

void setup() {
  Serial.begin(57600);
  
  pinMode(9, OUTPUT);   //enables fuer X achse
  pinMode(10, OUTPUT);  //enables fuer X achse
  digitalWrite(9, HIGH);  //enables fuer X achse
  digitalWrite(10, HIGH); //enables fuer X achse
  
  pinMode(3, OUTPUT);  //enables fuer Y achse
  pinMode(2, OUTPUT);  //enables fuer Y achse
  digitalWrite(3, HIGH); //enables fuer Y achse
  digitalWrite(2, HIGH); //enables fuer Y achse
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  pinMode(52, INPUT);  //Schalter
  pinMode(led, OUTPUT);  //laser
}

void loop() {
  
  int x = map(analogRead(A0),0,1023,1,100);
  int y = map(analogRead(A1),0,1023,1,100);
  
  while (Serial.available() > 0) {
    String RawRead = Serial.readStringUntil('\n');
    String BackWay = RawRead.substring(300);
    
    //Serial.print("I Read: ");
    //Serial.println(BackWay);
    
    String testDigit = RawRead.substring(0,1);
    contentString = RawRead.substring(0,300);
    
    testDigInt = testDigit.toInt();
    //Serial.print("testDig: ");
    //Serial.println(testDigInt);
    
    //Serial.print("String: ");
    //Serial.println(contentString);
    
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    
    for (int i=0; i <= 300; i++){
      //Serial.print(contentString[i]);
      
      
      if(contentString[i] == '1') {
        digitalWrite(led, HIGH);
        //Serial.println("1");
        doStepY(0);
        delay(nikoDelay);
      }
      else {
        digitalWrite(led, LOW);
        //Serial.println("0");
        doStepY(0);
        delay(2);  //2ms für ruhigen lauf
      }
    }
    doStepX(1);
    
    
    for (int i=0; i <= 300; i++){
      //Serial.print(contentString[i]);
      
      
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
    doStepX(1);
    
    Serial.write("k");
    
  }
  
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  
  if(digitalRead(52) == HIGH) {
    digitalWrite(led, HIGH);
  }else digitalWrite(led, LOW);
  
  
  if(x > 60 || x < 40 || y > 60 || y < 40) {
    if(x > 60) {
      doStepX(1);
      //Serial.println("StepX 1");
    }
    if(x < 40) {
      doStepX(0);
      //Serial.println("StepX 0");
    }
    if(x > 40 && x < 60) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
    else {
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
    }
    
    
    if(y > 60) {
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
    
    delay(3);
  }
  
}
void doStepX(int dirForX) {
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

void doStepY(int dirForY) {
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
