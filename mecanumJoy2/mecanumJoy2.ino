

#define MIDDLE    512
#define DEADZONE  32


int oldRX, oldRY, oldLX, oldLY;



void setup() {  
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}


int convert(int arg0) {
  int arg1 = arg0 - MIDDLE;
  Serial.print(arg1);
  Serial.print('\t');
  
  if(arg1>DEADZONE) return 1;
  if(arg1<DEADZONE) return -1;
  return 0;
}


void loop() {
  int rx = convert(analogRead(0));
  int ry = convert(analogRead(1));
  int lx = convert(analogRead(2));
  int ly = convert(analogRead(3));

  if(oldRX != rx || 
     oldRY != ry ||
     oldLX != lx ||
     oldLY != ly )
  {
    oldRX = rx;
    oldRY = ry;
    oldLX = lx;
    oldLY = ly;
     // state changed!
     if(oldRX==0 && oldRY==0 
     && oldLX==0 && oldLY==0) 
                        Serial.print(" ");  // all stop
     else if(oldRY== 1) Serial.print("W");  // forward
     else if(oldRY==-1) Serial.print("S");  // backward
     else if(oldRX==-1) Serial.print("A");  // strafe left
     else if(oldRX== 1) Serial.print("D");  // strafe right
     
     else if(oldLX==-1) Serial.print("Q");  // turn left
     else if(oldLX== 1) Serial.print("E");  // turn right
  }
  Serial.print("\n");
  delay(50);
}
