int leftMotorEnable = 1;
int leftMotorIn1 = 7;
int leftMotorIn2 = 12;

int rightMotorEnable = 3;
int rightMotorIn1 = 2;
int rightMotorIn2 = 4;

void setup() {
  pinMode(leftMotorEnable, OUTPUT);
  // do the rest of the pins....
}

void loop() {
  digitalWrite(leftMotorEnable, HIGH); // enable left motor
  digitalWrite(rightMotorEnable, HIGH); // enable right motor

  goForward();
}

void goForward() {
  // make left motor go forward
  digitalWrite(leftMotorIn1, HIGH);
  digitalWrite(leftMotorIn2, LOW);

  // make right motor go forward
  digitalWrite(rightMotorIn1, HIGH);
  digitalWrite(rightMotorIn2, LOW);
}






