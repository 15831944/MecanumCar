//-----------------------------------------------------------
// Mecanum car demo 1
// Dan Royer 2018-02-01
//-----------------------------------------------------------


#define MAX_PINS 12
#define BAUD     57600


//-----------------------------------------------------------

int pins[] = {
  2,  // a enb
  3,  // b ena
  4,  // c in1
  5,  // d in2
  6,  // e in3
  7,  // f in4
  
  8,  // g enb
  9,  // h ena
  10, // i in1
  11, // j in2
  12, // k in3
  13, // l in4
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

  Serial.println("\n\n**READY**");
}

void loop() {
  if(Serial.available()) {
    char c = Serial.read();
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

