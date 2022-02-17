#define redLed 9
#define greenLed 10
#define buzzervcc 11
#define buzzertone 12
void setup() {
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(buzzervcc,OUTPUT);
  pinMode(buzzertone,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasReading = analogRead(A0),min_level = 300;
  Serial.print(gasReading);
  Serial.println();
  delay(500);
  if(gasReading > min_level){
    digitalWrite(greenLed,LOW);
    digitalWrite(redLed,HIGH);
    digitalWrite(buzzervcc,HIGH);
    tone(buzzertone,1000);
  }
  else{
    digitalWrite(greenLed,HIGH);
    digitalWrite(redLed,LOW);
    digitalWrite(buzzervcc,LOW);
  }
}
