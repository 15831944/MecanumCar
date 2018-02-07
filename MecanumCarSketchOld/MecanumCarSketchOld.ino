// Mecanum Car Control Test
// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1 - Br
#define MOTOR1_ENA 1
#define MOTOR1_IN3 5
#define MOTOR1_IN4 6
//Motor 2
#define MOTOR2_ENA 2
#define MOTOR2_IN3 3
#define MOTOR2_IN4 4
//Motor 3
#define MOTOR3_ENA 8
#define MOTOR3_IN3 9
#define MOTOR3_IN4 10
//Motor 4
#define MOTOR4_ENA 7
#define MOTOR4_IN3 11
#define MOTOR4_IN4 12


// Setup runs once per reset
void setup() {
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
  
  //Define L298N Dual H-Bridge Motor Controller Pins
  
  pinMode(MOTOR1_ENA,OUTPUT);
  pinMode(MOTOR1_IN3,OUTPUT);
  pinMode(MOTOR1_IN4,OUTPUT);
  
  pinMode(MOTOR2_ENA,OUTPUT);
  pinMode(MOTOR2_IN3,OUTPUT);
  pinMode(MOTOR2_IN4,OUTPUT);
  
  pinMode(MOTOR3_ENA,OUTPUT);
  pinMode(MOTOR3_IN3,OUTPUT);
  pinMode(MOTOR3_IN4,OUTPUT);
  
  pinMode(MOTOR4_ENA,OUTPUT);
  pinMode(MOTOR4_IN3,OUTPUT);
  pinMode(MOTOR4_IN4,OUTPUT);

  // power for one h bridge comes from pin 13.
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
      case 'a':  digitalWrite(MOTOR1_ENA,HIGH);  break;  // Enable 
      case 'A':  digitalWrite(MOTOR1_ENA,LOW );  break;  // Disable 
      case 'b':  digitalWrite(MOTOR1_IN3,HIGH);  break;  // Enable 
      case 'B':  digitalWrite(MOTOR1_IN3,LOW );  break;  // Disable 
      case 'c':  digitalWrite(MOTOR1_IN4,HIGH);  break;  // Enable 
      case 'C':  digitalWrite(MOTOR1_IN4,LOW );  break;  // Disable 
      
      case 'd':  digitalWrite(MOTOR2_ENA,HIGH);  break;  // Enable 
      case 'D':  digitalWrite(MOTOR2_ENA,LOW );  break;  // Disable 
      case 'e':  digitalWrite(MOTOR2_IN3,HIGH);  break;  // Enable
      case 'E':  digitalWrite(MOTOR2_IN3,LOW );  break;  // Disable 
      case 'f':  digitalWrite(MOTOR2_IN4,HIGH);  break;  // Enable 
      case 'F':  digitalWrite(MOTOR2_IN4,LOW );  break;  // Disable 
      
      case 'g':  digitalWrite(MOTOR3_ENA,HIGH);  break;  // Enable 
      case 'G':  digitalWrite(MOTOR3_ENA,LOW );  break;  // Disable 
      case 'h':  digitalWrite(MOTOR3_IN3,HIGH);  break;  // Enable 
      case 'H':  digitalWrite(MOTOR3_IN3,LOW );  break;  // Disable 
      case 'i':  digitalWrite(MOTOR3_IN4,HIGH);  break;  // Enable 
      case 'I':  digitalWrite(MOTOR3_IN4,LOW );  break;  // Disable 
      
      case 'j':  digitalWrite(MOTOR4_ENA,HIGH);  break;  // Enable 
      case 'J':  digitalWrite(MOTOR4_ENA,LOW );  break;  // Disable 
      case 'k':  digitalWrite(MOTOR4_IN3,HIGH);  break;  // Enable 
      case 'K':  digitalWrite(MOTOR4_IN3,LOW );  break;  // Disable 
      case 'l':  digitalWrite(MOTOR4_IN4,HIGH);  break;  // Enable 
      case 'L':  digitalWrite(MOTOR4_IN4,LOW );  break;  // Disable 
      
      default: break; // do nothing
    }
  }
}
