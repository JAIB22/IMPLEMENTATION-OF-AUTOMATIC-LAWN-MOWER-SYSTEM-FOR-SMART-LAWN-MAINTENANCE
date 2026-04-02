#include <Servo.h>
#include <AFMotor.h>
#define Echo A0
#define Trig A1
int value;
int distance;
int Left=0;
int Right=0;
int Speed =130;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M4(4);
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(10);
  servo.write(90);
  M1.setSpeed(Speed);
  M4.setSpeed(Speed);
  //Serial.begin(9600);
}
void loop() {
 
  if (Serial.available() > 0) {
    value = Serial.read();
    if(value >10){Speed = value;} 
   }
  M1.setSpeed(Speed);
  M4.setSpeed(Speed);
  if (value == 4) {
    forward();
  } else if (value == 3) {
    backward();
  } else if (value == 2) {
    left();
  } else if (value == 1) {
    right();
  } else if (value == 5) {
    Stop();
  }
    else if (value == 7)
  {
    Obstacle();
  }
}
void Obstacle() 
{
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 distance = ultrasonic();
 if(distance<=15)
 {
      Stop();
      delay(100);
      backward();
      delay(300);
      Stop();
      delay(200);
      distanceR = rightsee();
      delay(200);
      distanceL = leftsee();
      delay(200);
    
      if(distanceR>=distanceL)
      {
        right();
        delay(500);
        Stop();
      }else
      {
        left();
        delay(500);
        Stop();
      }
 }else
 {
  forward();
 }
 
}
 
// Ultrasonic sensor distance reading function
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void forward() {
  M1.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {
  M1.setSpeed(100);
  
  M1.run(RELEASE);
  M4.run(FORWARD);

}
void left() {
  
  M4.setSpeed(100);
  M1.run(FORWARD);
  M4.run(RELEASE);

}
void Stop() {
  M1.run(RELEASE);
  M4.run(RELEASE);
}
int rightsee() {
  servo.write(20);
  delay(800);
  Right = ultrasonic();
  servo.write(90);
  return Right;
}
int leftsee() {
  servo.write(180);
  delay(800);
  Left = ultrasonic();
  servo.write(90);
  return Left;
}