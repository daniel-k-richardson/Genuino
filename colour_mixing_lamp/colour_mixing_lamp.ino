/*  colour_mixing_lamp.ino
 *  programmer: Daniel Richardson
 *  Date: 8/1/2016
 *  This is the forth Genuino project from the starter guide.
 *  I have of course made a few improvements on the code.
 *  
 *  The general idea of this program is of this code is to take
 *  input from three sensors that change depending on how much
 *  light is cast/blocked from them. Thos values are then converted
 *  from a range of 0-1023 coming in, to 0-255 going out. Which control
 *  three LED lights. Causing them to dim and change colour based on the
 *  light in a room.
 */


#define TIMER 5     // 5 milliseconds, used in conjunction with delay()
#define BYTE 9600   // the data size for Serial.begin()
/*  AnalogWrite only uses values between 0-255, the sensor reads from 0 to 1023.
 *  To adjust the input from the sensors to something analogWrite can use, we divide
 *  the sensors' read in data by 4, so that it can then be used by analogWrite() */
#define DOWN_SCALE_VALUE(sensor_in_value) (sensor_in_value) / 4  

/* Function prototypes */
void displaySensorValues(void);
void setSenesorValues(void);
void downScawlSensorValue(void);
void displayUsableValues(void);

/* Uno pins */
enum 
{
  // Uno digital pins.
  RED_LED_PIN = 9,
  BLUE_LED_PIN = 10,
  GREEN_LED_PIN = 11,
  
  // Uno analog pins.
  RED_SENSOR_PIN = A0,
  BLUE_SENSOR_PIN = A1,
  GREEN_SENSOR_PIN = A2
};

/*  red, green, blue values for LED output
 * after __SensorValue has been divided by four */
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

/* Reads in a value from analog sensor pins (a number between 0-1023). */
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() 
{
  Serial.begin(BYTE);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  setSenesorValues();
  displaySensorValues();
  
  downScawlSensorValue();
  displayUsableValues();

  writeToLEDS();
}

/*  Get the analog sensor values from their
 *  respective pins and assign them to red,
 *  green and blue SensorValue. */
void setSenesorValues(void)
{
  redSensorValue = analogRead(RED_SENSOR_PIN);
  delay(TIMER);
  greenSensorValue = analogRead(GREEN_SENSOR_PIN);
  delay(TIMER);
  blueSensorValue = analogRead(BLUE_SENSOR_PIN);
}

/* Display the raw sensor data in the Serial Monitor. */
void displaySensorValues(void)
{
  Serial.print("Raw Sensor Values \t red: ");
  Serial.print(redSensorValue);

  Serial.print("\t green: ");
  Serial.print(greenSensorValue);

  Serial.print("\t blue: ");
  Serial.print(blueSensorValue);
}

/*  Analog values of the sensors are too high
 *  and must be reduced for digial output. */
void downScawlSensorValue(void)
{
  redValue = DOWN_SCALE_VALUE(redSensorValue);
  greenValue = DOWN_SCALE_VALUE(greenSensorValue);
  blueValue = DOWN_SCALE_VALUE(blueSensorValue);
}

/* Display usable colour values in Serial Monitor */
void displayUsableValues(void)
{
  Serial.print("Mapped Sensor Values: /t red: ");
  Serial.print(redValue);

  Serial.print("\t green: ");
  Serial.print(greenValue);

  Serial.print("\t blue: ");
  Serial.print(blueValue);
}

/*  Write output to LEDS, values have been converted
 *  to a range which can be displayed within a digital
 *  range 0-255. */
void writeToLEDS(void)
{
  analogWrite(RED_LED_PIN, redValue);
  analogWrite(GREEN_LED_PIN, greenValue);
  analogWrite(BLUE_LED_PIN, blueValue);
}

