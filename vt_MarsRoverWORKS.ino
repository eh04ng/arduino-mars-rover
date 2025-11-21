const int LEDL = 0; 
const int LEDR = 1;

const int IR_SENSOR1 = 2;
const int IR_SENSOR2 = 3;

const int trigPin = 4;
const int echoPin = 5;

const int inA1 = 6;
const int inA2 = 7;
const int inB1 = 8;
const int inB2 = 9;

const int inC1 = 10;
const int inC2 = 11;
const int inD1 = 12;
const int inD2 = 13;

void setup() {
  Serial.begin(9600);
  Serial.println("Robot Starting...");

  pinMode(LEDL, OUTPUT);
  pinMode(LEDR, OUTPUT);

  pinMode(IR_SENSOR1, INPUT);
  pinMode(IR_SENSOR2, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

  pinMode(inC1, OUTPUT);
  pinMode(inC2, OUTPUT);
  pinMode(inD1, OUTPUT);
  pinMode(inD2, OUTPUT);
}

void moveForward() {
  Serial.println("Action: Move FORWARD");

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
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
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
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
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD1, HIGH);
  digitalWrite(inD2, LOW);
}

void moveBackward() {
  Serial.println("Action: Move BACKWARD");

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
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
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
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

void loop() {

  // Read IR sensors
  bool IR_READ1 = digitalRead(IR_SENSOR1);
  bool IR_READ2 = digitalRead(IR_SENSOR2);

  Serial.print("IR1 = ");
  Serial.print(IR_READ1);
  Serial.print(" | IR2 = ");
  Serial.println(IR_READ2);

  // Ultrasonic pulse (correct timing)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration_us = pulseIn(echoPin, HIGH);
  float distance_cm = duration_us * 0.0172;

  Serial.print("Distance = ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Emergency override
  if (distance_cm <= 10) {
    emergencyOverride();
    Serial.println("Skipping IR logic due to obstacle.");
  } else {
    lightsOff();
  }

  // IR logic
  if (IR_READ1 == LOW && IR_READ2 == LOW) {
    moveForward();
  }
  else if (IR_READ1 == LOW && IR_READ2 == HIGH) {
    turnRight();
  }
  else if (IR_READ1 == HIGH && IR_READ2 == LOW) {
    turnLeft();
  }
  else {
    stopMotors();
  }

  Serial.println("---------------------");
  delay(100);
}
