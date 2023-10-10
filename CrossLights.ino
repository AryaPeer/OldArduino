//Arya Peer - Crossing Light code

//Initialize and declare variables
int redWestEast = 3;
int yellowWestEast = 4;
int greenWestEast = 5;
int redNorthSouth = 6;
int yellowNorthSouth = 7;
int greenNorthSouth = 8;

const int a = 11;
const int b = 12;
const int c = A5;
const int d = A3;
const int e = A4;
const int f = 10;
const int g = 9;

int redLed = 2;
int greenLed = 13;
int blueLed = A1;

int num;
int button = A2;
int IN8 = 0;

void setup() {
  //set bitrate for arduino
  Serial.begin(9600);

  //set the pinmode for pins on the arduino
  pinMode(redWestEast, OUTPUT);
  pinMode(yellowWestEast, OUTPUT);
  pinMode(greenWestEast, OUTPUT);
  pinMode(redNorthSouth, OUTPUT);
  pinMode(yellowNorthSouth, OUTPUT);
  pinMode(greenNorthSouth, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode (greenLed, OUTPUT);
  pinMode (redLed, OUTPUT);
  pinMode (blueLed, OUTPUT);

  pinMode (button, INPUT);
}

//Function to take rgb values as an argument and set them as the output of the rgb led
void setRGBColor (int red, int green, int blue) {
  digitalWrite (redLed, red);
  digitalWrite (greenLed, green);
  digitalWrite (blueLed, blue);
}

//Function to display numbers on the seven segment display by tyrning on and off specific segments
//This function turns on and off segments of the delay to display the number
void SevenSegmentDisplay(int num) {
  if (num == 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
  }
  if (num == 1) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }
  if (num == 2) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if (num == 3) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if (num == 4) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (num == 5) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (num == 6) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (num == 7) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }
  if (num == 8) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (num == 9) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
}

void loop() {
  //Read button and set color of walking light as red
  IN8 = digitalRead (button);
  setRGBColor(255, 0, 0);

  //Declare and initialize variables
  int ledOnCount = 0;
  bool permanentLoop = true;

  //permanent loop
  while (permanentLoop == true) {

    //for 9 seconds loop north south green light on and west east red light on
    for (int i = 0; i < 9; i++) {
      SevenSegmentDisplay(9 - i);
      Serial.print("N/S Green light on for: ");
      Serial.println(i + 1);

      //North South
      digitalWrite(greenNorthSouth, HIGH);
      digitalWrite(yellowNorthSouth, LOW);
      digitalWrite(redNorthSouth, LOW);

      //East West
      digitalWrite(redWestEast, HIGH);
      digitalWrite(yellowWestEast, LOW);
      digitalWrite(greenWestEast, LOW);

      //if IN8 is low delay for 1 second
      if (IN8 == LOW) {

        delay(1000);

      } else { //if IN8 is high turn on the crossing light

        // if i is less than 5 then turn on the blue light and print it's the east west crossing light
        if (i < 5) {

          Serial.println("E/W Crossing Light");
          setRGBColor(0, 0, 255);
          delay(1000);

        } else {
          //else blink red lights 250 ms on 250 ms off
          setRGBColor(255, 0, 0);
          ledOnCount += 1;
          delay (250);
          setRGBColor(0, 0, 0);
          delay (250);

          Serial.print("number of times the rgb led has blinked: ");
          Serial.println(ledOnCount);

          setRGBColor(255, 0, 0);
          ledOnCount += 1;
          delay (250);
          setRGBColor(0, 0, 0);
          delay (250);

          Serial.print("number of times the rgb led has blinked: ");
          Serial.println(ledOnCount);
        }
      }
    }

    //set in8 as 0 and set rgb as red
    IN8 = 0;
    setRGBColor(255, 0, 0);

    //for 5 seconds loop north south yellow light on and west east red light on
    for (int j = 0; j < 5; j++) {

      // if IN8 is low read the button
      if (IN8 == LOW) {
        IN8 = digitalRead (button);
      }

      //if the button has been pressed output that the button has been pressed
      if (IN8 == HIGH) {
        Serial.println("Input Pressed");
      }

      //output to seven segment display
      SevenSegmentDisplay (5 - j);
      Serial.print("N/S Yellow Light on for: ");
      Serial.println(j + 1);

      //North South
      digitalWrite(greenNorthSouth, LOW);
      digitalWrite(yellowNorthSouth, HIGH);
      digitalWrite(redNorthSouth, LOW);

      //East West
      digitalWrite(redWestEast, HIGH);
      digitalWrite(yellowWestEast, LOW);
      digitalWrite(greenWestEast, LOW);

      //delay 1 second
      delay(1000);
    }

    //for 2 seconds loop north south red light on and west east red light on
    for (int k = 0; k < 2; k++) {

      // if IN8 is low read the button
      if (IN8 == LOW) {
        IN8 = digitalRead (button);
      }

      // if IN8 is high
      if (IN8 == HIGH) {
        Serial.println("Input Pressed");
      }

      SevenSegmentDisplay (2 - k);
      Serial.print("N/S red light on for: ");
      Serial.println(k + 1);

      //North South
      digitalWrite(greenNorthSouth, LOW);
      digitalWrite(yellowNorthSouth, LOW);
      digitalWrite(redNorthSouth, HIGH);

      //East West
      digitalWrite(redWestEast, HIGH);
      digitalWrite(yellowWestEast, LOW);
      digitalWrite(greenWestEast, LOW);

      delay(1000);
    }

    //if in8 is low check for button press
    if (IN8 == LOW) {
      IN8 = digitalRead (button);
    }

    ledOnCount = 0;

    //for 9 seconds loop north south red light on and west east green light on
    for (int x = 0; x < 9; x++) {

      SevenSegmentDisplay(9 - x);
      Serial.print("E/W Green light on for: ");
      Serial.println(x + 1);

      //North South
      digitalWrite(greenNorthSouth, LOW);
      digitalWrite(yellowNorthSouth, LOW);
      digitalWrite(redNorthSouth, HIGH);

      //East West
      digitalWrite(redWestEast, LOW);
      digitalWrite(yellowWestEast, LOW);
      digitalWrite(greenWestEast, HIGH);

      //if in8 is low delay 1 second
      if (IN8 == LOW) {

        delay (1000);

      } else {//if in8 is high turn on the crossing light
        if (x < 5) {//5 second loop of crossing light on

          Serial.println("N/S Crossing Light");
          setRGBColor(0, 0, 255);
          delay(1000);

        } else {// 4 seconds of red light blinking

          setRGBColor(255, 0, 0);
          ledOnCount += 1;
          delay (250);

          setRGBColor(0, 0, 0);
          delay (250);

          Serial.print("number of times the rgb led has blinked: ");
          Serial.println(ledOnCount);

          setRGBColor(255, 0, 0);
          ledOnCount += 1;
          delay (250);

          setRGBColor(0, 0, 0);
          delay (250);

          Serial.print("number of times the rgb led has blinked: ");
          Serial.println(ledOnCount);
        }
      }
    }

    IN8 = 0;
    setRGBColor(255, 0, 0);

    //for 5 seconds loop north south red light on and west east yellow on
    for (int y = 0; y < 5; y++) {

      //if in8 is low check button
      if (IN8 == LOW) {
        IN8 = digitalRead (button);
      }

      //if in8 is high output message
      if (IN8 == HIGH) {
        Serial.println("Input Pressed");
      }

      SevenSegmentDisplay (5 - y);
      Serial.print("E/W Yellow Light on for: ");
      Serial.println(y + 1);

      //North South
      digitalWrite(greenNorthSouth, LOW);
      digitalWrite(yellowNorthSouth, LOW);
      digitalWrite(redNorthSouth, HIGH);

      //East West
      digitalWrite(redWestEast, LOW);
      digitalWrite(yellowWestEast, HIGH);
      digitalWrite(greenWestEast, LOW);

      delay(1000);

    }

    //for 2 seconds loop north south red light on and west east red light on
    for (int z = 0; z < 2; z++) {
      //if in8 is low check button
      if (IN8 == LOW) {
        IN8 = digitalRead(button);
      }

      //if in8 is high output
      if (IN8 == HIGH) {
        Serial.println("Input Pressed");
      }

      SevenSegmentDisplay (2 - z);
      Serial.print("E/W Red light on for: ");
      Serial.println(z + 1);

      //North South
      digitalWrite(greenNorthSouth, LOW);
      digitalWrite(yellowNorthSouth, LOW);
      digitalWrite(redNorthSouth, HIGH);

      //East West
      digitalWrite(redWestEast, HIGH);
      digitalWrite(yellowWestEast, LOW);
      digitalWrite(greenWestEast, LOW);

      delay(1000);
    }
  }
}
