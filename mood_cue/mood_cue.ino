#include <Servo.h>

#define POT_PIN A0      // analog pin to read in the twisty button thingy.
#define CONTROL_PIN 9   // digital pin for rotation of motor.
#define BAUD 9600

int potValue = 0;       // analog value of twisty button thingy (0-1023).
int angle = 0;          // angle value after map() has done its thing.

Servo myServo;          // servo motor object.

void setup() 
{
  myServo.attach(CONTROL_PIN);

  Serial.begin(BAUD);
}

void loop() 
{
  potValue = analogRead(POT_PIN);
  angle = map(potValue, 0, 1023, 0, 179);

  myServo.write(angle);
  delay(15);
}
