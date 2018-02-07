void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
}


int count=0;
void loop() {
  ++count;
  if(count%50) {
    count=1;
    Serial.println("---------------------------------------------");
    Serial.println("0\t1\t2\t3\t4\t12\t13");
    Serial.println("---------------------------------------------");
  }
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(0));  Serial.print('\t');
  Serial.print(analogRead(1));  Serial.print('\t');
  Serial.print(analogRead(2));  Serial.print('\t');
  Serial.print(analogRead(3));  Serial.print('\t');
  Serial.print(digitalRead(12));  Serial.print('\t');
  Serial.print(digitalRead(13));  Serial.print('\n');
  delay(50);
}
