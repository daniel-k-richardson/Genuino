/*  File: Spaceship
    Programmer: Daniel Richardson.
    Date: 7/1/2016
    This was the 3rd project in the Genuino starter kit
    that I have modified and improved. The idea of the program
    is to listen to the curcuit. If no volts are being receviced
    then the curcuit isn't complete, so power the green LED, otherwise
    (while the button is pressed) power two red LEDs and turn off
    the green LED.
*/


/* timer for delay() */
#define TIMER 500 // half a second.

/* Digital pins. */
enum
{
  RED_LED_ONE = 4,
  RED_LED_TWO = 5,
  GREEN_LED = 3,
  CURCUIT = 2
};

int switchState = 0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED_ONE, OUTPUT);
  pinMode(RED_LED_TWO, OUTPUT);
  pinMode(CURCUIT, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  switchState = digitalRead(CURCUIT);

  if (switchState == LOW)
  {
    /*  switch has not been pressed. Power up
        green LED, power down both red LEDs */
    digitalWrite(RED_LED_TWO, LOW);
    delay(TIMER);
    digitalWrite(RED_LED_ONE, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  else
  {
    /*  switch is currently pressed.
        power down green LED and power
        up both red LEDs */
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED_ONE, HIGH);
    delay(TIMER);
    digitalWrite(RED_LED_TWO, HIGH);
  }
}
