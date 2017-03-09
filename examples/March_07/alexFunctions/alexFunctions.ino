/*
  Alex's color sensing robot code, modified to use functions.

  The functions I added in class are at the very end of the file.

  Based on Alex's original code at
  https://github.com/alexmkane/mechatronics/blob/master/vehicle_homework

*/

#include "Adafruit_TCS34725.h"
#include <Wire.h>
#include <Math.h>

byte i2cWriteBuffer[10];
byte i2cReadBuffer[10];

#define SensorAddressWrite 0x29 //
#define SensorAddressRead 0x29 // 
#define EnableAddress 0xa0 // register address + command bits
#define ATimeAddress 0xa1 // register address + command bits
#define WTimeAddress 0xa3 // register address + command bits
#define ConfigAddress 0xad // register address + command bits
#define ControlAddress 0xaf // register address + command bits
#define IDAddress 0xb2 // register address + command bits
#define ColorAddress 0xb4 // register address + command bits

/*
  Send register address and the byte value you want to write the magnetometer and
  loads the destination register with the value you send
*/

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void Writei2cRegisters(byte numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  Wire.write(command);                          // Send command, normally the register address
  for (i = 0; i < numberbytes; i++)                 // Send data
    Wire.write(i2cWriteBuffer[i]);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

/*
  Send register address to this function and it returns byte value
  for the magnetometer register's contents
*/
byte Readi2cRegisters(int numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
  Wire.write(command);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle

  Wire.requestFrom(SensorAddressRead, numberbytes);  // read data
  for (i = 0; i < numberbytes; i++)
    i2cReadBuffer[i] = Wire.read();
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

void init_TCS34725(void)
{
  i2cWriteBuffer[0] = 0x10;
  Writei2cRegisters(1, ATimeAddress);   // RGBC timing is 256 - contents x 2.4mS =
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ConfigAddress);  // Can be used to change the wait time
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ControlAddress); // RGBC gain control
  i2cWriteBuffer[0] = 0x03;
  Writei2cRegisters(1, EnableAddress);   // enable ADs and oscillator for sensor
}

void get_TCS34725ID(void)
{
  Readi2cRegisters(1, IDAddress);
  if (i2cReadBuffer[0] = 0x44)
    Serial.println("TCS34725 is present");
  else
    Serial.println("TCS34725 not responding");
}

/*
  Reads the register values for clear, red, green, and blue.
*/
void get_Colors(void)
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters(8, ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1] << 8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7] << 8) + (unsigned int)i2cReadBuffer[6];

  // send register values to the serial monitor
  /*
    Serial.print("clear color=");
    Serial.print(clear_color, DEC);
    Serial.print(" red color=");
    Serial.print(red_color, DEC);
    Serial.print(" green color=");
    Serial.print(green_color, DEC);
    Serial.print(" blue color=");
    Serial.println(blue_color, DEC);
  */

  // Basic RGB color differentiation can be accomplished by comparing the values and the largest reading will be
  // the prominent color

  if ((red_color > blue_color) && (red_color > green_color))
    Serial.println("detecting red");
  else if ((green_color > blue_color) && (green_color > red_color))
    Serial.println("detecting green");
  else if ((blue_color > red_color) && (blue_color > green_color))
    Serial.println("detecting blue");
  else
    Serial.println("color not detectable");

}



/*
  // variables will change:
  int enableStateRight = HIGH;
  int enableStateLeft = HIGH; // variable for reading the pushbutton status
  int greenSensor = 0;
  int redSensor = 0;
  int blueSensor = 0; */

const int enable1 = 6; // PWM pin for speed control
const int in1 = 4;
const int in2 = 2;
// Control pins for the right half of the H-bridge
const int enable2 = 9; // PWM pin for speed control
const int in3 = 8;
const int in4 = 7;
const int led = 10;
const int colorMotor = 11;

void setup() {

  // constants won't change. They're used here to
  // set pin numbers:


  // initialize the motor pin as an output:
  pinMode( enable1, OUTPUT);
  pinMode( in1, OUTPUT);
  pinMode( in2, OUTPUT);

  pinMode( enable2, OUTPUT);
  pinMode( in3, OUTPUT);
  pinMode( in4, OUTPUT);
  pinMode( led, OUTPUT);
  pinMode( colorMotor, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

}

void loop()

{

  analogWrite (colorMotor, 55);
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters(8, ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1] << 8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7] << 8) + (unsigned int)i2cReadBuffer[6];
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  if ((red_color > blue_color) && (red_color > green_color)) {
    Serial.println("detecting red 1st");
    goForward(); // this is how we use, or call, the "goForward()" function
  }
  else if ((green_color > blue_color) && (green_color > red_color)) {
    Serial.println("detecting green");
    turnRight();
  }
  else if ((blue_color > red_color) && (blue_color > green_color)) {
    Serial.println("detecting blue");
    turnLeft();
  }
  else {
    Serial.println("color not detectable");
  }

  // read the state of the pushbutton value:
  //  enableStateRight = digitalRead(enablePinRight);

}

/* this is the body of the function goForward. It is usually called
  the "function declaration" or "function definition"

  Notice that it starts with the word void,
  meaning that there is no return value

  Notice that after the name of the function "goForward"
  the parenthesis are empty, meaning that it takes no parameters

*/
void goForward() {
  // right motor forward
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  analogWrite (enable1, 200);
  // left motor forward
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
  analogWrite (enable2, 200);
  digitalWrite(led, LOW);
}


void turnRight() {
  // right motor stop; this will drag or skid
  digitalWrite(led, HIGH);
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  analogWrite (enable1, 200);
  // left motor forward
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
  analogWrite (enable2, 200);
}

void turnLeft() {
  // right motor forward
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  analogWrite (enable1, 200);
  // left motor reverse; this will turn fast
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
  analogWrite (enable2, 200);
}
