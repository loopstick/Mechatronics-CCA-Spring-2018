/* Control analogWrite() according to input using digitalRead().
   Could be used to move a motor when a button is pressed

   1/25/17 - Michael Shiloh - Initial creation
   based on setMotorSpeed example from
   https://github.com/michaelshiloh/Mechatronics-Spring-2017/tree/master/examples/setMotorSpeed

   Pin usage:
   3 - some output device, e.g. a transistor controlling a motor
   2 - some digital input device, e.g. a switch
*/

void setup() {
  pinMode (3, OUTPUT);// Not necessary but good practice for clarity
  pinMode (2, INPUT); // Not necessary but good practice for clarity
}

// Must always have a loop() function, even if there is nothing in it
void loop() {

  if (HIGH == digitalRead(2) ) {
    analogWrite(3, 220);    // this is the slowest my motor would still turn
  } else {
    analogWrite(3, 0);    // motor off
  }
}

