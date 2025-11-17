const int LEDL = 0; // variable for left light
const int LEDR = 1; // variable for right light

const int IR_SENSOR1 = 2; // pin D2 to IR sensor (L)
const int IR_SENSOR2 = 3; // pin D3 to second IR sensor (R)

const int trigPin = 4; // pin D4 to trig ultrasonic sensor
const int echoPin = 5; // pin D5 to trig ultrasonic sensor

// if 6 wheels are wanted, delete first pair of slashes in lines w/ ; 
// and assign pin numbers to variables at lines 21 and 24
const int inA1 = 6; // variable for h-bridge
const int inA2 = 7; // variable for h-bridge
const int inB1 = 8; // variable for h-bridge
const int inB2 = 9; // variable for h-bridge

const int inC1 = 10; // variable for second h-bridge
const int inC2 = 11; // variable for second h-bridge
const int inD1 = 12; // variable for second h-bridge
const int inD2 = 13; // variable for second h-bridge

//const int inE1 = ; // variable for third h-bridge
//const int inE2 = ; // variable for third h-bridge
//const int inF1 = ; // variable for third h-bridge
//const int inF2 = ; // variable for third h-bridge

void setup() {
  Serial.begin(9600); // start serial monitor at 9600 baud

  pinMode(LEDL, OUTPUT); // left light set as output
  pinMode(LEDR, OUTPUT); // right light set as output

  pinMode(IR_SENSOR1, INPUT); // IR sensors set as inputs
  pinMode(IR_SENSOR2, INPUT); // IR sensors set as inputs

  pinMode (trigPin, OUTPUT); // ultrasonic sensor trig set as output
  pinMode (echoPin, INPUT); // ultrasonic sensor echo set as input

  pinMode (inA1, OUTPUT); // all h-bridge variables are outputs
  pinMode (inA2, OUTPUT); // all h-bridge variables are outputs
  pinMode (inB1, OUTPUT); // all h-bridge variables are outputs
  pinMode (inB2, OUTPUT); // all h-bridge variables are outputs

  pinMode (inC1, OUTPUT); // all h-bridge variables are outputs
  pinMode (inC2, OUTPUT); // all h-bridge variables are outputs
  pinMode (inD1, OUTPUT); // all h-bridge variables are outputs
  pinMode (inD2, OUTPUT); // all h-bridge variables are outputs

  //pinMode (inE1, OUTPUT); // all h-bridge variables are outputs
  //pinMode (inE2, OUTPUT); // all h-bridge variables are outputs
  //pinMode (inF1, OUTPUT); // all h-bridge variables are outputs
  //pinMode (inF2, OUTPUT); // all h-bridge variables are outputs
}

void moveForward() {
  // all motors spin clockwise
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, HIGH);
  digitalWrite(inD2, LOW);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);
}


void turnLeft() {
  // left light blink
  digitalWrite(LEDL, HIGH);
  delay(1000); // 1 sec delay
  digitalWrite(LEDL, LOW);

  // select motors activate
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);
}

void turnRight() {
  // right light blink
  digitalWrite(LEDR, HIGH);
  delay(1000); // 1 sec delay
  digitalWrite(LEDR, LOW);

  //select motors activate
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, HIGH);
  digitalWrite(inD2, LOW);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);
}

void moveBackward() {
  // all motors spin counterclockwise
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);
}

void stopMotors() {
  // all motors stop
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, LOW);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);
}

void emergencyOverride() {
  // back up and turn on lights
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);

  digitalWrite(LEDL, HIGH);
  digitalWrite(LEDR, HIGH);
}

void lightsOff() {
  // stop and turn off lights
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, LOW);

  //digitalWrite(inE1, LOW);
  //digitalWrite(inE2, LOW);
  //digitalWrite(inF1, LOW);
  //digitalWrite(inF2, LOW);

  digitalWrite(LEDL, LOW);
  digitalWrite(LEDR, LOW);
}

void loop() {
// ref: https://github.com/heshanpasindusankalpa/Basic-Arduino-Line-Following-Robot/blob/main/LineFollowerCode.ino
// ref: a code from our prev assignments

bool IR_READ1 = digitalRead(IR_SENSOR1); // variable for IR sensor reading
bool IR_READ2 = digitalRead(IR_SENSOR2); // variable for IR sensor reading

float duration_us, distance_cm; // variables for ultrasonic sensor reading

// gen 10 microsec pulse to TRIG pin
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// measures duration of pulse from ECHO pin
duration_us = pulseIn(echoPin, HIGH);
// calc distance
distance_cm = 0.017 * duration_us;

// movement
if (distance_cm <= 10) {emergencyOverride();
return; //prevents IR logic from activating
} // if distance is 10 cm or less, back up and turn on lights
else {lightsOff();
} // if distance is more than 10 cm, stop and turn off lights

if (IR_READ1 == LOW && IR_READ2 == LOW) {moveForward();
} // if both IR sensors are LOW, move forward
else if (IR_READ1 == LOW && IR_READ2 == HIGH) {turnRight();
} // if L IR is LOW and R IR is HIGH, turn right
else if (IR_READ1 == HIGH && IR_READ2 == LOW) {turnLeft(); 
} // if L IR is HIGH and R IR is LOW, turn left
else {stopMotors();
} // stopped if all prior conditions are false
}