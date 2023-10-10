#include <Servo.h>
//declare and initialize variables
Servo servoLeft;
Servo servoRight;
Servo pingServo;
const int pingServoPin = 11 ;
const int pingPinT = 10;
const int pingPinE = 9;
int frontDistance;
int leftDistance;
int rightDistance;
long duration;
int cm;

//setup
void setup() {
 Serial.begin (9600);
 pingServo.attach(pingServoPin);
 servoLeft.attach(13);
 servoRight.attach(12);
 pinMode(pingPinT, OUTPUT);
 pinMode(pingPinE, INPUT);
}

//void loop
void loop() {
frontDistance = distanceDetect();

//while front distance is greater than or equal to 12
while(frontDistance >= 12){

frontDistance = distanceDetect();

//for loop
for(int i=1; i<=15; i++){

  servoLeft.writeMicroseconds (1700);
  servoRight.writeMicroseconds (1300);
  delay(20);

  }

 frontDistance = distanceDetect();
 
}
//for loop
for(int i=1; i<=10; i++){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(20);
}


pingServo.writeMicroseconds (1500);
delay (1500);
frontDistance = distanceDetect();
delay(100);

pingServo.writeMicroseconds (0);
delay (1500);
leftDistance = distanceDetect();
delay(100);

pingServo.writeMicroseconds (1500);
 delay (1500);
 
pingServo.writeMicroseconds (3000);
delay (1500);
rightDistance = distanceDetect();
delay(100);

pingServo.writeMicroseconds (1500);
 delay (1500);

//if right distance is greater than left distance turn right
if(rightDistance>leftDistance){

for(int i=1; i<=15; i++){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(20);
}

for(int i=1; i<=26; i++){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(20);
  }

}
//else if turn left
else if(leftDistance>rightDistance){

for(int i=1; i<15; i++){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(20);
}

for(int i=1; i<=29; i++){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(20);
  }


}


}

//detect distance method
int distanceDetect (){
digitalWrite(pingPinT, LOW);
delayMicroseconds(2);
digitalWrite(pingPinT, HIGH);
delayMicroseconds (10);
digitalWrite(pingPinT, LOW);
duration = pulseIn(pingPinE, HIGH, 25000);
cm = duration * 0.034 / 2;

return cm;
}
