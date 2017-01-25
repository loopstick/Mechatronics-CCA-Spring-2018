/* A very simple example showing how to use analogWrite() to set the speed of a motor.
    (of course Arduino has no idea whether you really have a motor attached, or an LED, or something else)

   In this example nothing ever changes so it can all be done in setup()

   1/25/17 - Michael Shiloh - Initial creation

   Pin usage:
   3 - a transistor controlling a motor
*/

void setup() {
  pinMode (3, OUTPUT);  // strictly speaking not necessary but good practice for clarity
  analogWrite(3, 40);    // Set the PWM value to 40 (can range from minimum 0 to maximum 255)
}

// Must always have a loop() function, even if there is nothing in it
void loop() {
}
