/*
 * Zoetrope
 */

// Pins
#define controlPin1 4 // connected to pin 7 on the H-bridge
#define controlPin2 5 // connected to pin 2 on the H-bridge
#define enablePin 6 // connected to pin 1 on the H-bridge
#define directionSwitchPin 2 // connected to the switch for direction
#define onOffSwitchStateSwitchPin 3 // connected to the switch for turning the
#define potPin A0
#define controlPin3 7 // connected to pin 7 on the H-bridge
#define controlPin4 8 // connected to pin 2 on the H-bridge
#define enablePin2 9

// Variables
byte onOffSwitchState = 0; // current state of the on/off switch
byte previousOnOffSwitchState = 0; // previous position of the on/off switch
byte directionSwitchState = 0; // current state of the direction switch
byte previousDirectionSwitchState = 0; // previous state of the direction switch
byte motorEnabled = 0; // Turns the motor on/off
byte motorSpeed = 0; // speed of the motor
byte motorDirection = 1; // current direction of the motor

void setup() {
  // initialize the inputs and outputs
  Serial.begin(9600);
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(controlPin3, OUTPUT);
  pinMode(controlPin4, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  // pull the enable pin LOW to start
  digitalWrite(enablePin, LOW);
  digitalWrite(enablePin2, LOW);
}

void loop() {
  // read the value of the on/off switch
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  
  // read the value of the direction switch
  directionSwitchState = digitalRead(directionSwitchPin);
  
  // read the value of the pot and divide by 4 to get a value that can be
  // used for PWM (potPin value will be from 0 to 1023)
  motorSpeed = analogRead(potPin) / 4; //divide by 4 to get 0-255

  // if the on/off button changed state since the last loop()
  if (onOffSwitchState != previousOnOffSwitchState) {
    // change the value of motorEnabled if pressed
    if (onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  // if the direction button changed state since the last loop()
  if (directionSwitchState != previousDirectionSwitchState) {
    // change the value of motorDirection if pressed
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  // change the direction the motor spins by talking to the control pins
  // on the H-Bridge
  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, HIGH);
    digitalWrite(controlPin4, LOW);
    Serial.println("FORWARD");
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, HIGH);
    Serial.println("REVERSE");
  }

  // if the motor is supposed to be on, read the motor speed
  if (motorEnabled == 1) {
    // PWM the enable pin to vary the speed
    analogWrite(enablePin, motorSpeed);
    analogWrite(enablePin2, motorSpeed);
    Serial.println(motorSpeed);
  } else { // if the motor is not supposed to be on
    //turn the motor off
    analogWrite(enablePin, 0);
    analogWrite(enablePin2, 0);
  }

  // save the current on/off switch state as the previous
  previousDirectionSwitchState = directionSwitchState;
  // save the current switch state as the previous
  previousOnOffSwitchState = onOffSwitchState;
}
