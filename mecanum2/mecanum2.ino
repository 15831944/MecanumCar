//-----------------------------------------------------------
// Mecanum car demo 2
// Dan Royer 2018-02-01
// http://wiki.seeedstudio.com/images/9/91/Working_Principle%28Simplified%29.PNG
//-----------------------------------------------------------


#define MAX_PINS 12
#define BAUD     57600


//-----------------------------------------------------------


int pins[] = {
  2,  // a enb  fr
  3,  // b ena  fl
  4,  // c in1  fr forward
  5,  // d in2  fr backward
  6,  // e in3  fl forward
  7,  // f in4  fl backward
  
  8,  // g enb  bl
  9,  // h ena  br
  10, // i in1  bl forward
  11, // j in2  bl backward
  12, // k in3  br forward
  13, // l in4  br backward
};

int pinStates[MAX_PINS];


//-----------------------------------------------------------


void setup() {
  Serial.begin(BAUD);

  // logic pins
  for(int i=0;i<MAX_PINS;++i) {
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],LOW);
    pinStates[i] = 0;
  }

  digitalWrite(2,HIGH);  // ena
  digitalWrite(3,HIGH);  // enb
  digitalWrite(8,HIGH);  // ena
  digitalWrite(9,HIGH);  // enb
  
  Serial.println("\n\n**READY**");
}


void loop() {
  if(Serial.available()) {
    char c = Serial.read();
    //drivePinsDirectly(c);
    driveLevel2(c);
  }
}


void driveLevel2(char c) {
  switch(c) {
    case 'W':  goForward  ();  break;
    case 'A':  strafeLeft ();  break;
    case 'S':  goBackward ();  break;
    case 'D':  strafeRight();  break;
    case 'Q':  turnLeft   ();  break;
    case 'E':  turnRight  ();  break;
    case ' ':  stopAll    ();  break;
    case '\n':
    case '\r': break;
    default:
      Serial.println("Invalid key");
      return;
  }
  Serial.println(c);
}


void goForward() {
  FRforward();
  FLforward();
  BRforward();
  BLforward();
}
void goBackward() {
  FRbackward();
  FLbackward();
  BRbackward();
  BLbackward();
}
void strafeLeft() {
  FRforward();
  FLbackward();
  BRbackward();
  BLforward();
}
void strafeRight() {
  FRbackward();
  FLforward();
  BRforward();
  BLbackward();
}
void turnLeft() {
  FRforward();
  FLbackward();
  BRforward();
  BLbackward();
}
void turnRight() {
  FRbackward();
  FLforward();
  BRbackward();
  BLforward();
}
void stopAll() {
  FRstop();
  FLstop();
  BRstop();
  BLstop();
}


void FRforward () {  digitalWrite( 4,HIGH);  digitalWrite( 5,LOW );  }
void FRbackward() {  digitalWrite( 4,LOW );  digitalWrite( 5,HIGH);  }
void FRstop    () {  digitalWrite( 4,LOW );  digitalWrite( 5,LOW );  }

void FLforward () {  digitalWrite( 6,HIGH);  digitalWrite( 7,LOW );  }
void FLbackward() {  digitalWrite( 6,LOW );  digitalWrite( 7,HIGH);  }
void FLstop    () {  digitalWrite( 6,LOW );  digitalWrite( 7,LOW );  }

void BLforward () {  digitalWrite(10,HIGH);  digitalWrite(11,LOW );  }
void BLbackward() {  digitalWrite(10,LOW );  digitalWrite(11,HIGH);  }
void BLstop    () {  digitalWrite(10,LOW );  digitalWrite(11,LOW );  }

void BRforward () {  digitalWrite(13,LOW );  digitalWrite(12,HIGH);  }
void BRbackward() {  digitalWrite(13,HIGH);  digitalWrite(12,LOW );  }
void BRstop    () {  digitalWrite(13,LOW );  digitalWrite(12,LOW );  }


void drivePinsDirectly(char c) {
  int pinIndex = c-'a';
  if(pinIndex>=0 && pinIndex < MAX_PINS) {
    int state = pinStates[pinIndex];
    // toggle the pin state
    digitalWrite(pins[pinIndex],state?LOW:HIGH);
    // remember the new state
    pinStates[pinIndex] = pinStates[pinIndex] ^ 1;
    // tell us the new state
    printPinStates();
  } else if(c!='\r'&& c!='\n') {
    Serial.println("Invalid pin");
  }
}


int lines=0;
void printPinStates() {
  if((lines%10)==0) {
    printHR();
    for(int i=0;i<MAX_PINS;++i) {
      Serial.print((char)('a'+i));
      Serial.print(' ');
    }
    Serial.println();
    printHR();
  }
  lines++;
  
  for(int i=0;i<MAX_PINS;++i) {
    Serial.print(pinStates[i],DEC);
    Serial.print(' ');
  }
  Serial.println();
}


void printHR() {
  for(int i=0;i<MAX_PINS;++i) {
    Serial.print("--");
  }
  Serial.println();
}

