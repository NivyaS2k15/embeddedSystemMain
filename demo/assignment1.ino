/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
ASSIGNMETN NIVYA ONE


*/

#include <Servo.h>

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int buttonPin = 2;
int buttonFirstState = 0;
int buttonLastState = 1;
 
void setup() {
  myservo.attach(9); 
  pinMode(buttonPin, INPUT);
   // attaches the servo on pin 9 to the Servo object
}

void loop() {
  buttonFirstState = digitalRead(buttonPin);  // read the button

  if (buttonFirstState == HIGH && buttonLastState == LOW) {
    // If button is pressed and servo is not at 180, move to 180
    for (pos = 0; pos <= 180; pos++) {
      myservo.write(pos);
      delay(10);
    }
   buttonLastState = HIGH;
  }

  if (buttonFirstState == LOW && buttonLastState == HIGH) {
    // If button is released and servo is at 180, move back to 0
    for (pos = 180; pos >= 0; pos--) {
      myservo.write(pos);
      delay(10);
    }
    buttonLastState = LOW ;
  }
}

