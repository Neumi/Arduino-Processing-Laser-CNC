// doppeltest
import processing.serial.*;
Serial myPort;

PImage img;       // The source image
int cols, rows;   // Number of columns and rows in our system

int line = 0;
int val;
boolean runthrew = false;

int pixelSquare = 300;

void setup() {
  size(300, 300);
  img = loadImage("Arduino Logo 300x300.png");
  String portName = Serial.list()[9];
  myPort = new Serial(this, portName, 57600);
}

void draw() {  
  background(0, 102, 153);
  image(img, 0, 0);
  loadPixels();
  stroke(0,0,255);
  line(line-1,0,line-1,300);
  textSize(20);
  fill(200,200,200);
  rect(0,0,110,25);
  fill(0,240,0);
  text("Line: ",10,20);
  text(line, 60,20);
  
  if(mousePressed) {
    myPort.write("0");  //anfangsbefehl
  }
  
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
    
    if(line < 300) {
      
      if(val == 'k') {
        
        println();
        println("Received Pulse! ");
        print("Line: ");
        println(line);
        
        newSection();
      }
    }
    else {
      text("Ready!",20,20);
    }
  }
  
  
  
}

void newSection() {
  
  for ( int j = 0; j < 299; j++) {
    int x = line + pixelSquare; // x position
    int y = j + pixelSquare; // y position
    
    int loc = line + j * pixelSquare; // Pixel array location
    
    int c = img.pixels[loc];
    
    if(c < -16000000) {
      print(1);
      myPort.write("1");
    }
    else {
      print(0);
      myPort.write("0");
    }
  }
  line = line + 1;
  myPort.write("0");
  for ( int j = 299; j > 0; j--) {
    int x = line + pixelSquare; // x position
    int y = j + pixelSquare; // y position
    
    int loc = line + j * pixelSquare; // Pixel array location
    
    int c = img.pixels[loc];
    
    if(c < -16000000) {
      print(1);
      myPort.write("1");
    }
    else {
      print(0);
      myPort.write("0");
    }
  }
  line = line + 1;
  
  
  myPort.write('\n');
  
}
