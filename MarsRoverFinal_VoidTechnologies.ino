const int LEDL = 0; // variable for light (L)
const int LEDR = 1; // variable for light (R)

const int IR_SENSOR1 = 2; // pin D2 to IR sensor (L)
const int IR_SENSOR2 = 3; // pin D3 to second IR sensor (R)

const int trigPin = 4; // pin D4 to trig ultrasonic sensor
const int echoPin = 5; // pin D5 to trig ultrasonic sensor

const int inA1 = 6; // variable for h-bridge
const int inA2 = 7; // variable for h-bridge
const int inB1 = 8; // variable for h-bridge
const int inB2 = 9; // variable for h-bridge

const int inC1 = 10; // variable for second h-bridge
const int inC2 = 11; // variable for second h-bridge
const int inD1 = 12; // variable for second h-bridge
const int inD2 = 13; // variable for second h-bridge

void setup() {
  Serial.begin(9600); // variable for second h-bridge
  Serial.println("Robot Starting...");

  pinMode(LEDL, OUTPUT); // light set as output
  pinMode(LEDR, OUTPUT); // light set as output

  pinMode(IR_SENSOR1, INPUT); // IR sensors set as inputs
  pinMode(IR_SENSOR2, INPUT); // IR sensors set as inputs

  pinMode(trigPin, OUTPUT); // ultrasonic sensor trig set as output
  pinMode(echoPin, INPUT); // ultrasonic sensor trig set as output

  pinMode(inA1, OUTPUT); // all h-bridge variables are outputs
  pinMode(inA2, OUTPUT); // all h-bridge variables are outputs
  pinMode(inB1, OUTPUT); // all h-bridge variables are outputs
  pinMode(inB2, OUTPUT); // all h-bridge variables are outputs

  pinMode(inC1, OUTPUT); // all h-bridge variables are outputs
  pinMode(inC2, OUTPUT); // all h-bridge variables are outputs
  pinMode(inD1, OUTPUT); // all h-bridge variables are outputs
  pinMode(inD2, OUTPUT); // all h-bridge variables are outputs
}

// functions
void moveForward() {
  Serial.println("Action: Move FORWARD");

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, LOW);  
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, HIGH);  
  digitalWrite(inD2, LOW);
}

void turnLeft() {
  Serial.println("Action: Turn LEFT");

  digitalWrite(LEDL, HIGH);
  delay(1000);
  digitalWrite(LEDL, LOW);

 digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);
}

void turnRight() {
  Serial.println("Action: Turn RIGHT");

  digitalWrite(LEDR, HIGH);
  delay(1000);
  digitalWrite(LEDR, LOW);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, HIGH);
  digitalWrite(inD2, LOW);
}

void moveBackward() {
  Serial.println("Action: Move BACKWARD");

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);
}

void stopMotors() {
  Serial.println("Action: STOP");

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, LOW);
}

void emergencyOverride() {
  Serial.println("EMERGENCY OVERRIDE: Object too close!");

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, HIGH);

  digitalWrite(LEDL, HIGH);
  digitalWrite(LEDR, HIGH);
}

void lightsOff() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD1, LOW);
  digitalWrite(inD2, LOW);

  digitalWrite(LEDL, LOW);
  digitalWrite(LEDR, LOW);
}
// end of functions

void loop() {
// ref: https://github.com/heshanpasindusankalpa/Basic-Arduino-Line-Following-Robot/blob/main/LineFollowerCode.ino
// ref: code from prev assignments (Circuit Lab, mostly)

  // read IR sensors
  bool IR_READ1 = digitalRead(IR_SENSOR1); // variable for IR sensor reading
  bool IR_READ2 = digitalRead(IR_SENSOR2); // variable for IR sensor reading

  Serial.print("IR1 = ");
  Serial.print(IR_READ1);
  Serial.print(" | IR2 = ");
  Serial.println(IR_READ2);

  // ultrasonic pulse 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // generating 10 microsec pulse to TRIG pin...
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measures duration of pulse from ECHO pin
  float duration_us = pulseIn(echoPin, HIGH);
  // calc distance
  float distance_cm = duration_us * 0.0172;

  Serial.print("Distance = ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // ultrasonic logic
  if (distance_cm <= 10) {
    emergencyOverride();
    Serial.println("Skipping IR logic due to obstacle.");
  } //// if distance is 10 cm or less, back up and turn on lights
  else {
    //lightsOff();
  }
   // if distance is more than 10 cm, stop and turn off lights

  // IR logic
  if (IR_READ1 == HIGH && IR_READ2 == HIGH) {
    moveForward();
  } // if both IR sensors are HIGH, move forward
  else if (IR_READ1 == LOW && IR_READ2 == HIGH) {
    turnRight();
  } // if L IR is LOW and R IR is HIGH, turn right
  else if (IR_READ1 == HIGH && IR_READ2 == LOW) {
    turnLeft();
  }  // if L IR is HIGH and R IR is LOW, turn left
  else {
    moveBackward();
    delay (80);
    stopMotors();
  } // move backwards and stop if all prior conditions are false
  }

  Serial.println("---------------------");
  delay(100);
}
