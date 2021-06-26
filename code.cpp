#include<Servo.h>
Servo servo1;
const int trigPin = 3;
const int echoPin = 4;
// defining variables
long duration;
int distance;
int pos = 0;
int ir = 7;
int led = 8;
float start_time;
int check = 0;
float counter = 0;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(11, OUTPUT);
  pinMode(13,OUTPUT);
  servo1.attach(9);
  servo1.write(0);
  pinMode(ir,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(9600);
}


void loop() {
  start_time = millis();
  if (start_time >= 60) {
    start_time = 0;
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance <= 48) {
    digitalWrite(11, HIGH);
    delay(300);
    digitalWrite(11, LOW);
    delay(300);
}
  if((int(start_time) % 10 )== 0) {
  Serial.print("time: ");
  Serial.print(start_time/1000);
  Serial.println("");
  Serial.print("blinks: ");
  Serial.print(counter);
  Serial.println("");
  Serial.print("blinkrate per minute: ");
  Serial.print(counter/(start_time/60000));
  Serial.println("");
  }
  if(digitalRead(ir)==HIGH){
    if (check == 1) {
      counter ++;
      
    }
    check = 0;
    digitalWrite(led,HIGH);
  }
  else{
    check = 1;
    digitalWrite(led,LOW);
  }
  delay(100);
  int lightValue = analogRead(A0);
  lightValue = map(lightValue,0,1023,0,180);
  Serial.println(lightValue);
  if (lightValue > 35) { 
    if (pos == 100){
    for (pos = 100; pos>0; pos--){
    servo1.write(pos);
    delay(15);
      }
    }
  }
  else {
    if (pos == 0) {
      for (pos = 0; pos<100; pos++){
        servo1.write(pos);
        delay(15);
      }
    }
  }
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'a')
    {
      digitalWrite(13,HIGH);
      digitalWrite(11,HIGH);
    }
    else if(data == 'b')
    {
      digitalWrite(13,LOW);
      digitalWrite(11,LOW);
    }
  }
}