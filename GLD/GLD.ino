#include <SoftwareSerial.h>
SoftwareSerial gld(5, 6);

void gldSend();
void gldReceive();

int redLed = 9;
int greenLed = 10;
int buzzervcc = 11;
int buzzertone = 12;
int i = 0;
int a;

void setup() {
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(buzzervcc,OUTPUT);
  pinMode(buzzertone,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
  gld.begin(9600);
  delay(1000);
}

void loop() {
  int gasReading = analogRead(A0),min_level = 300;
  Serial.print(gasReading);
  Serial.println();
  if(gasReading > min_level){
    digitalWrite(greenLed,LOW);
    digitalWrite(redLed,HIGH);
    digitalWrite(buzzervcc,HIGH);
    tone(buzzertone,1000);
      if(i == 0){
        Serial.print("Detected");
        gldSend();
        i++;
      }
    
    if (gld.available()>0){
      Serial.write(gld.read());
    }
    gldReceive();
    if(a == 1){
      gldSend();
      a = 0;
    }
  }
  else{
    digitalWrite(greenLed,HIGH);
    digitalWrite(redLed,LOW);
    digitalWrite(buzzervcc,LOW);
    i = 0;
  }
}

void gldSend(){
  gld.println("AT+CMGF=1");
  delay(1000);
  gld.println("AT+CMGS=\"+918669799343\"\r");
  delay(1000);
  gld.println("GAS LEAKAGE HAS BEEN DETECTED");
  delay(100);
  Serial.println ("Done");
  delay(100);
  gld.println((char)26);
  delay(1000);
}
void gldReceive(){
  gld.println("AT+CMGF=1\r");
  gld.println("AT+CNMI=2,2,0,0,0\r");//Read SMS at location 1.
  if (gld.available() > 0) {
    a = gld.read();
    Serial.write(a);
  }
  delay(100);
}
