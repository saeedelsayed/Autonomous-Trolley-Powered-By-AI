/*
pins 6,7

pins 4,5

pins 12,13

*/

#include <Arduino.h>
#include <Wire.h>

// Define constants
#define SLAVE_ADDRESS 0x0F  // Address of the I2C slave device
#define NUMBER_OF_ROTATIONS 2

#define DELAY_TIME 1500

const int OBSTACLE_DISTANCE = 80;
const int ROTATION_OBSTACLE_DISTANCE = 40;  // Rotate if obstacle detected within this distance
const int STABLE_DISTANCE = 60;             // Threshold for considering the distance stable from Left and Right sensors

// Sensor pins
const int Trig_forward = 6;
const int Echo_forward = 7;
const int Trig_left = 12;
const int Echo_left = 13;
const int Trig_right = 9;
const int Echo_right = 10;
//const int Stop_Pin = 2;
const int interrupt_pin = 3;

// Function prototypes
void setupSensors();
void Robot_Move_Forward();
void Robot_Move_Left(int distance_forward, int distance_left);
void Robot_Move_Right(int distance_forward, int distance_right);
void Robot_Stop();
void turn_right();
void turn_left();
void Robot_Move_Back();
float get_distance(int Trig, int Echo);

void setup() {
  Serial.begin(9600);

  setupSensors();

  Wire.begin();

  //pinMode(Stop_Pin, OUTPUT);
  //digitalWrite(Stop_Pin, HIGH);

  pinMode(interrupt_pin, OUTPUT);
  digitalWrite(interrupt_pin, HIGH);
}

void loop() {
  int distance_forward = get_distance(Trig_forward, Echo_forward);
  int distance_left = get_distance(Trig_left, Echo_left);
  int distance_right = get_distance(Trig_right, Echo_right);

  Serial.print("distance_forward: ");
  Serial.println(distance_forward);
  Serial.print("distance_left: ");
  Serial.println(distance_left);
  Serial.print("distance_right: ");
  Serial.println(distance_right);

  if (distance_forward > OBSTACLE_DISTANCE) {
    if (distance_left > STABLE_DISTANCE && distance_right > STABLE_DISTANCE) {
      //Robot_Move_Forward();  // No OBSTACLE found - Move forward
    } else if (distance_right <= STABLE_DISTANCE) {
      // Right OBSTACLE - Stop and Turn Left
      Robot_Stop();
      delay(500);

      sendMessage("060L");
      delay(DELAY_TIME);
    } else if (distance_left <= STABLE_DISTANCE) {
      // Left OBSTACLE - Stop and Turn Right
      Robot_Stop();
      delay(500);

      sendMessage("060R");
      delay(DELAY_TIME);
    }
  } else {  // OBSTACLE Found - Stop and move back

    Robot_Stop();
    delay(500);
    Robot_Move_Back();
    delay(DELAY_TIME);

    distance_left = get_distance(Trig_left, Echo_left);
    distance_right = get_distance(Trig_right, Echo_right);

    // Both OBSTACLE - Move Left or Right based on the distance from Left and Right sensors
    if (distance_right > distance_left) {
      // There is a free distance on the right side, so move right
      Robot_Move_Right(distance_forward, distance_right);
    } else {
      // There is a free distance on the left side, so move left
      Robot_Move_Left(distance_forward, distance_left);
    }
  }

}  // end of loop

void setupSensors() {
  pinMode(Trig_forward, OUTPUT);
  pinMode(Echo_forward, INPUT);
  pinMode(Trig_left, OUTPUT);
  pinMode(Echo_left, INPUT);
  pinMode(Trig_right, OUTPUT);
  pinMode(Echo_right, INPUT);
}

void Robot_Move_Left(int distance_forward, int distance_left) {
  char directions = 0, i;

  for (i = 1; i <= NUMBER_OF_ROTATIONS; i++) {
    if (distance_left > ROTATION_OBSTACLE_DISTANCE) {
      //  Robot_Move_LEFT_with_45_degree
      turn_left();
      directions = i;
      delay(DELAY_TIME);
    } else {
      return;
    }

    // Check if the distance is stable after the rotation
    distance_forward = get_distance(Trig_forward, Echo_forward);
    if (distance_forward > OBSTACLE_DISTANCE) {
      break;
    }

    // update the distance_left
    distance_left = get_distance(Trig_left, Echo_left);
  }

  // Move forward after the rotation
  Robot_Move_Forward();
  delay(DELAY_TIME);

  // Robot_Move_RIGHT_with_(45*direction)_degree
  while (directions) {
    turn_right();
    delay(DELAY_TIME);
    directions--;
  }
}

void Robot_Move_Right(int distance_forward, int distance_right) {
  char directions = 0, i;

  for (i = 1; i <= NUMBER_OF_ROTATIONS; i++) {
    if (distance_right > ROTATION_OBSTACLE_DISTANCE) {
      //  Robot_Move_RIGHT_with_45_degree
      turn_right();
      directions = i;
      delay(DELAY_TIME);
    } else {
      return;
    }

    // Check if the distance is stable after the rotation
    distance_forward = get_distance(Trig_forward, Echo_forward);
    if (distance_forward > OBSTACLE_DISTANCE) {
      break;
    }

    // update the distance_right
    distance_right = get_distance(Trig_right, Echo_right);
  }

  // Move forward after the rotation
  Robot_Move_Forward();
  delay(DELAY_TIME);

  // Robot_Move_LEFT_with_(45*direction)_degree
  while (directions) {
    turn_left();
    delay(DELAY_TIME);
    directions--;
  }
}

void Robot_Move_Forward() {
  sendMessage("100F");
}

void Robot_Stop() {
  //digitalWrite(Stop_Pin, LOW);
  //delay(100);
  //digitalWrite(Stop_Pin, HIGH);

  sendMessage("000F");
}

void turn_right() {
  // Robot_Move_RIGHT_with_45_degree
  sendMessage("045R");
}

void turn_left() {
  // Robot_Move_LEFT_with_45_degree
  sendMessage("045L");
}

void Robot_Move_Back() {
  sendMessage("100B");
}

float get_distance(int Trig, int Echo) {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  unsigned long t = pulseIn(Echo, HIGH);
  float cm = (t * 0.0343) / 2.0;
  return cm;
}

void sendMessage(String message) {

  int returnValue = 1;

  while (returnValue != 0) {
    digitalWrite(interrupt_pin, LOW);
    delay(100);
    digitalWrite(interrupt_pin, HIGH);

    Wire.beginTransmission(SLAVE_ADDRESS);  // Begin transmission to slave device

    for (char i = 0; i < 4; i++) {
      Wire.write(message[i]);
    }

    returnValue = Wire.endTransmission();

    Serial.println(message);
  }
}