
/* pins both analog and digital */
#define LED_PIN 13            // led pin on 13 (the uno board) to show calibrate timer.
#define SENSOR_ANALOG_IN A0   // connected to the light sensor that will create tone.
#define PIEZO_PIN 8           // pin connected to piezo that will output tone.

#define CALIBRATE_TIME 5000   // 5 secondss to calibrate light sesnsor for tone generation.
#define NOTE_LENGTH 20        // how long any one note will output for from the piezo.
#define TIMER 10              // used in conjuction with delay().

#define PIEZO_START_RANGE 50  // min range used in conjuction with map().
#define PIEZO_END_RANGE 4000  // max range used in conjunction with map(). 

int sensorValue;              // raw sesnor data
int sensorLow = 1023;         // will hold the lowest value once calibrate is finished.
int sensorHigh = 0;           // will hold the highest value once calibrate is finished.
 
 void setup() {
  /* keep led at pin 13 on, until calibrate is over */
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  /* calibrate the values until timer is done */
  while (millis() < CALIBRATE_TIME)
  {
    sensorValue = analogRead(SENSOR_ANALOG_IN);
    if (sensorValue >  sensorHigh)
      sensorHigh = sensorValue;
    if (sensorValue < sensorLow)
      sensorLow = sensorValue;
  }
  /* We're done, turn off light and get started */
  digitalWrite(LED_PIN, LOW); 
}

void loop() {
  int pitch;  // pitch of the tone that piezo will output.

  /* get a the raw data from analog sensor */
  sensorValue = analogRead(SENSOR_ANALOG_IN);

  /* convert raw analog data to a pitch that piezo can create */
  pitch = map(sensorValue, sensorLow, sensorHigh, 
    PIEZO_START_RANGE, PIEZO_END_RANGE);

  /* play the tone generated */
  tone(PIEZO_PIN, pitch, NOTE_LENGTH); 
  delay(TIMER);
}
