#include <Servo.h>
#include <LiquidCrystal.h>

Servo motor;
int servo = 10;
LiquidCrystal LCD(A2,9,8,7,6,5);

int trigPin = A0;
int echoPin = A1;


float pingTime;
float frontDistance;
float leftDistance;
float rightDistance;
float speedOfSound = 0.034;

int controlPin1M1 = 8;
int controlPin2M1 = 7;
int enablePinM1 = 6;

int controlPin1M2 = 13;
int controlPin2M2 = 12;
int enablePinM2 = 11;

int motorDir1 = 0;
int motorDir2 = 0;

int motorSpeed = 255;


float distance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  return speedOfSound*pulseIn(echoPin, HIGH)/2;
}



void driveMotors(int dir1, int dir2){
  digitalWrite(controlPin1M1, !dir1);
  digitalWrite(controlPin2M1, dir1);
  digitalWrite(controlPin1M2, !dir2);
  digitalWrite(controlPin2M2, dir2);
}

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  LCD.begin(16,2);
  LCD.setCursor(0,0);
  LCD.print("Distance:");    
  
  pinMode(controlPin1M1, OUTPUT);
  pinMode(controlPin2M1, OUTPUT);
  pinMode(controlPin1M2, OUTPUT);
  pinMode(controlPin2M2, OUTPUT);
  pinMode(enablePinM1, OUTPUT);
  pinMode(enablePinM2, OUTPUT);
  digitalWrite(enablePinM1, 0);
  digitalWrite(enablePinM2, 0);
  
  motor.attach(servo);
  motor.write(0);
}

void loop()
{
  delay(50);
  LCD.setCursor(0,1);
  frontDistance = distance();

  Serial.print(frontDistance);
  Serial.println(" cm");
  Serial.print(leftDistance);
  Serial.println(" left cm");
  Serial.print(rightDistance);
  Serial.println(" right cm");

  LCD.setCursor(0,1);
  LCD.print("               ");
  LCD.setCursor(0,1);
  LCD.print(frontDistance);
  LCD.print(" cm");
  
  if (frontDistance < 20){
    analogWrite(enablePinM1, 0);
    analogWrite(enablePinM2, 0);
    
    motor.write(0);
    delay(1000);
    
    leftDistance = distance();
    
    LCD.setCursor(0,1);
    LCD.print("               ");
    LCD.setCursor(0,1);
    LCD.print(leftDistance);
    LCD.print(" cm");

    motor.write(90);
    delay(1000);
    
    motor.write(180);
    delay(1000);
    
    rightDistance = distance();
    
    LCD.setCursor(0,1);
    LCD.print("               ");
    LCD.setCursor(0,1);
    LCD.print(rightDistance);
    LCD.print(" cm");
    
    motor.write(90);
    delay(1000);
    
    analogWrite(enablePinM1, motorSpeed);
    analogWrite(enablePinM2, motorSpeed);
    motorDir1 = 1;
    motorDir2 = 1;
    driveMotors(motorDir1, motorDir2);
    delay(300);

    if (leftDistance > rightDistance){
      motorDir1 = 0;
      motorDir2 = 1;
    } else {
      motorDir1 = 1;
      motorDir2 = 0;
    }
    
    driveMotors(motorDir1, motorDir2);
    delay(500);
    
    motorDir1 = 0;
    motorDir2 = 0;
    
  } else {
    
  analogWrite(enablePinM1, motorSpeed);
  analogWrite(enablePinM2, motorSpeed);
  motor.write(90);
  }
  driveMotors(motorDir1, motorDir2);
  delay(50);
  
}
