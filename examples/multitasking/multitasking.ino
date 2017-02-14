
/*
*/

#include <Servo.h>

// Pin usage

// LDR and white LED
const int whiteLEDPin = 6;
const int LDRPin = A1;

// traffic light
const int greenLEDPin = 7;
const int yellowLEDPin = 4;
const int redLEDPin = 2;

// other
const int buttonPin = 8;
const int servoPin = 11;
const int potPin = A0;

Servo myservo;

class Flasher
{
    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the number of the LED pin
    long OnTime;     // milliseconds of on-time
    long OffTime;    // milliseconds of off-time

    // These maintain the current state
    int ledState;                 // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated

    // Constructor - creates a Flasher
    // and initializes the member variables and state
  public:
    Flasher(int pin, long on, long off)
    {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      OnTime = on;
      OffTime = off;

      ledState = LOW;
      previousMillis = 0;
    }

    void Update()
    {
      // check to see if it's time to change the state of the LED
      unsigned long currentMillis = millis();

      if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
      {
        ledState = LOW;  // Turn it off
        previousMillis = currentMillis;  // Remember the time
        digitalWrite(ledPin, ledState);  // Update the actual LED
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
      {
        ledState = HIGH;  // turn it on
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(ledPin, ledState);   // Update the actual LED
      }
    }
};


Flasher redFlasher(redLEDPin, 100, 400);
Flasher yellowFlasher(yellowLEDPin, 400, 700);
Flasher greenFlasher(greenLEDPin, 350, 350);

void setup() {
  pinMode(whiteLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  Serial.begin(9600);

  myservo.attach(servoPin);
}

void loop() {

  // potentiometer controlls white LED brightness
  // which affects Light Dependent Resistor (LDR)
  // which sets angle of servo motor
  int answer = analogRead(potPin); // answer between 0 - 1023
  answer = map (answer, 0, 1023, 0, 255);
  analogWrite(whiteLEDPin, answer); // can only go from 0 - 255

  answer = analogRead(LDRPin);
  Serial.print(answer);
  Serial.print('\t');
  answer = map (answer, 800, 1023, 5, 175);
  Serial.println(answer);
  myservo.write(answer);


  //  // Traffic light
  //  trafficLight(greenLEDPin);
  //  delay(1000);
  //  trafficLight(yellowLEDPin);
  //  delay(1000);
  //  trafficLight(redLEDPin);
  //  delay(1000);
  //  trafficLight(yellowLEDPin);
  //  delay(1000);

  redFlasher.Update();
  yellowFlasher.Update();
  greenFlasher.Update();

}


void trafficLightOff() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
}

void trafficLight(int whichLED) {
  trafficLightOff();
  digitalWrite(whichLED, HIGH);
}

