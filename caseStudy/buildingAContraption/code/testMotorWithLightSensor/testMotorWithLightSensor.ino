/* Turn on a motor when a button is pressed, and stop when
    a light beam is blocked from a sensor

   1/25/17 - Michael Shiloh - Initial creation
   based on testMotorWithSwitch example from
   https://github.com/michaelshiloh/Mechatronics-Spring-2017/tree/master/examples/testMotorWithSwitch

   Pin usage:
   3 - a transistor controlling the motor
   2 - a pushbutton that will tell the motor to start moving
   A0 - a light sensor
*/

const int motorPin = 3;
const int switchPin = 2;
const int lightSensorPin = A0;

void setup() {
  pinMode (motorPin, OUTPUT);// Not necessary but good practice for clarity
  pinMode (switchPin, INPUT); // Not necessary but good practice for clarity
  pinMode (A0, INPUT); // Not necessary but good practice for clarity
  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(lightSensorPin);
  Serial.println(sensorValue); // Report the light sensor reading, so I can make adjustments

  if (HIGH == digitalRead(switchPin) ) { // read the pushbutton

    if ( sensorValue > 500 )  { // lots of light
      analogWrite(motorPin, 225);    // move the motor
    } else { // no light; mechanism must be blocking sensor
      analogWrite(motorPin, 0); // turn off motor
    }
  } else { // the switch must be off
    analogWrite(motorPin, 0); // so turn the motor off
  }
}

