

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
  
  if(arg1> DEADZONE) return 1;
  if(arg1<-DEADZONE) return -1;
  return 0;
}


/**
 * @input x x-axis value of joystick
 * @input y y-axis value of joystick
 * @return 0=deadzone, 1=east, 2=north, 3=west, 4=south
 */
int getMajorAxis(int x,int y) {
  x -= MIDDLE;
  y -= MIDDLE;
  
  //Serial.print(x);  Serial.print('\t');
  //Serial.print(y);  Serial.print('\t');
  
  int ax = abs(x);
  int ay = abs(y);
  if(ax<DEADZONE && ay<DEADZONE) return 0;
  else if(ax>DEADZONE && ay>DEADZONE) {
    if(ax>ay) {
      if(x>0) return 1;
      else return 3;
    } else {
      if(y>0) return 2;
      else return 4;
    }
  } else if(ax>DEADZONE) {
    if(x>0) return 1;
    else return 3;
  } else {  // ay>DEADZONE
    if(y>0) return 2;
    else return 4;
  }
}

int driveStateOld=0;

void loop() {
  //singleAxisTest();
  int right = getMajorAxis(analogRead(0),analogRead(1));
  int left  = getMajorAxis(analogRead(2),analogRead(3));

  // find the desired drive state
  int driveState = driveStateOld;
  if(left==2) {
    if(right==2) driveState=1;
    if(right==4) driveState=6;
  }
  if(left==4) {
    if(right==2) driveState=5;
    if(right==4) driveState=3;
  }
  if(left==1 && right==1) driveState=4;
  if(left==3 && right==3) driveState=2;
  if(left==0 && right==0) driveState=0;

  // only trasmit changes to drive state
  if(driveStateOld != driveState) {
    driveStateOld = driveState;
    switch(driveState) {
      case  1:  Serial.print('W');  break;
      case  2:  Serial.print('A');  break;
      case  3:  Serial.print('S');  break;
      case  4:  Serial.print('D');  break;
      case  5:  Serial.print('Q');  break;
      case  6:  Serial.print('E');  break;
      default:  Serial.print(' ');  break;
    }
    Serial.print("\n");
  }

  delay(50);
}


void singleAxisTest() {
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
