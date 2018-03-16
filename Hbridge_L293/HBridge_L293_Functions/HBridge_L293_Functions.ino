
//left motor H bridge control pins
int motor1a = 2;
int motor1b = 4;
//right motor H bridge control pins
int motor2a = 7;
int motor2b = 8;

int dir = 0; // variable for motor control direction

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1a,OUTPUT);  //controls H Bridge input 1a
  pinMode(motor1b,OUTPUT);  //controls H Bridge input 1b
  pinMode(motor2a,OUTPUT);  //controls H Bridge input 2a
  pinMode(motor2b,OUTPUT);  //controls H Bridge input 2b
  pinMode(13,OUTPUT);  // built in LED - for deBug
}

/*
When Pin2=1 & pin4 = logic 0, then it rotates in clockwise direction.
Pin2=logic 0 & Pin4=logic 1, then it rotates in anti clock direction
Pin2=logic 0 & Pin4=logic 0, then it is idle (high impedance state)
Pin2=logic 1 & Pin4=logic 1, then it is idle
*/

void loop() {
  // put your main code here, to run repeatedly:
forward();
delay(1000);
stopp();
delay(1000);
reverse();
delay(1000);
stopp();
delay(1000);
leftRev();
delay(1000);
stopp();
delay(1000);
leftTurn();
delay(1000);
stopp();
delay(1000);
rightRev();
delay(1000);
stopp();
delay(1000);
rightTurn();
delay(1000);
stopp();
delay(1000);
spinLeft();
delay(1000);
stopp();
delay(1000);
spinRight();
delay(1000);
stopp();
}

void forward() {
//forward
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
}

void reverse() {
//reverse
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
}

void idleHigh() {
// idle high
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);
}

void idleLow() {
// idle low
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);
}  

void stopp() {
  idleLow();
}

void leftRev() {
//turn left - left motor reverse
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
}

void rightRev() {
//turn right - right motor reverse 
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
}

void leftTurn() {
//turn left - right motor forward
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
}

void rightTurn() {
//turn right - left motor on 
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
}

void spinRight() {
  rightRev();
  rightTurn();
}

void spinLeft() {
  leftRev();
  leftTurn();
}



