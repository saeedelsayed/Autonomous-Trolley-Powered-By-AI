/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is based on the Arduino WiFi Shield library, but has significant changes as newer WiFi functions are supported.
 *  E.g. the return value of `encryptionType()` different because more modern encryption is supported.
 */
#include "WiFi.h"
#include "SVM.h"

#ifndef _MAP_H_
#define _MAP_H_

#define NOT_OK 0
#define OK 1

// Macros for the map
typedef enum Map {
  EMPTY,
  EXIT,
  REHABILITATION,
  STUDENT_LAB,
  INTERSECTION,
  LECTURE_HALL,
  ELEVATORS,
  CALIBRATION_LAB
} map_t;

// Macros for the direction
typedef enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
} direction_t;

// Pair of map and direction
typedef struct
{
  int destination;
  int status;
} pair;

// Function prototypes
int update_position(pair *current_position_local, map_t target_position_local);

pair current_position = { LECTURE_HALL, WEST };
map_t target_position = CALIBRATION_LAB;
int state = NOT_OK;

// bit_two bit_one bit_zero   command
//  0        0        0       idel
//  0        0        1       080F
//  0        1        0       000F
//  0        1        1       180R
//  1        0        0       090L
//  1        0        1       090R
int bit_zero = 9;
int bit_one = 10;
int bit_two = 11;

#endif  // _MAP_H_


// network names --> rssi array index
// "Abyusif" --> 0
// "abram Gad " --> 1
// "STUDBME2" --> 2
// "BMES_Secrelary" --> 3
// "ESP32_One" --> 4
// "Saeed" --> 5
// "Sbme-Staff" --> 6
// "CMP LAB1" --> 7
// "CMP LAB2" --> 8
// "CMP LAB3" --> 9
// "CMP LAB4" --> 10
// "CMP_LAB1" --> 11
// "CMP_LAB2" --> 12
// "CMP_LAB3" --> 13
// "CMP_LAB4" --> 14
// "Lab-admin" --> 15
// "RehabLab" --> 16

#define TOTAL_NUMBER_OF_NETWORK 17

float rssi[TOTAL_NUMBER_OF_NETWORK] = { 0 };

Eloquent::ML::Port::SVM model;
int label;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // initilaize rssi array
  for (int i = 0; i < TOTAL_NUMBER_OF_NETWORK; i++) {
    rssi[i] = -100;
  }

  pinMode(bit_zero, OUTPUT);
  pinMode(bit_one, OUTPUT);
  pinMode(bit_two, OUTPUT);

  digitalWrite(bit_zero, LOW);
  digitalWrite(bit_one, LOW);
  digitalWrite(bit_two, LOW);
}

void loop() {
  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("no networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == "Abyusif") {
        rssi[0] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "abram Gad ") {
        rssi[1] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "STUDBME2") {
        rssi[2] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "BMES_Secrelary") {
        rssi[3] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "ESP32_One") {
        rssi[4] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "Saeed") {
        rssi[5] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "Sbme-Staff") {
        rssi[6] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP LAB1") {
        rssi[7] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP LAB2") {
        rssi[8] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP LAB3") {
        rssi[9] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP LAB4") {
        rssi[10] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP_LAB1") {
        rssi[11] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP_LAB2") {
        rssi[12] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP_LAB3") {
        rssi[13] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "CMP_LAB4") {
        rssi[14] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "Lab-admin") {
        rssi[15] = WiFi.RSSI(i);
      } else if (WiFi.SSID(i) == "RehabLab") {
        rssi[16] = WiFi.RSSI(i);
      }
    }
  }

  label = model.predict(rssi) + 1;

  current_position.destination = label;

  Serial.println(label);

  state = update_position(&current_position, target_position);

  if (state == NOT_OK) {
    // move forward
    Serial.print("080F");

    digitalWrite(bit_zero, HIGH);
    digitalWrite(bit_one, LOW);
    digitalWrite(bit_two, LOW);

  } else {
    // Stop
    Serial.print("000F");

    digitalWrite(bit_zero, LOW);
    digitalWrite(bit_one, HIGH);
    digitalWrite(bit_two, LOW);
  }


  // make rssi zeros again
  for (int i = 0; i < TOTAL_NUMBER_OF_NETWORK; i++) {
    rssi[i] = -100;
  }

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();
}


int update_position(pair *current_position_local, map_t target_position_local) {

  int updating_current_position = (*current_position_local).destination;
  int updating_status = (*current_position_local).status;

  if (updating_current_position == target_position) {
    return OK;
  } else {
    // 1 <-----> 2 <-----> 3 -----> 4
    if (updating_current_position < INTERSECTION) {
      // 1 -----> 2 -----> 3 -----> 4
      if (updating_current_position < target_position) {
        updating_current_position = updating_current_position + 1;
        if (updating_status == WEST) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);
        }
        updating_status = EAST;
      } else  // 1 <----- 2 <----- 3 ----- 4
      {
        updating_current_position = updating_current_position - 1;
        if (updating_status == EAST) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);
        }
        updating_status = WEST;
      }
    }
    // [4]
    else if (updating_current_position == INTERSECTION) {
      // 4 -->-->--> 5
      if (target_position == LECTURE_HALL) {
        updating_current_position = updating_current_position + 1;
        // <- 4 -->-->--> 5
        if (updating_status == WEST) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);

        }
        // | 4 -->-->--> 5
        else if (updating_status == SOUTH) {
          // rotate 90 degrees to the left
          Serial.print("090L");

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        }
        // ^ 4 -->-->--> 5
        else if (updating_status == NORTH) {
          // rotate 90 degrees to the right
          Serial.print("090R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);
        }
        updating_status = EAST;
      }
      /*
                4 ------ 5
                |
                |
                7
                */
      else if (target_position == CALIBRATION_LAB) {
        updating_current_position = updating_current_position + 3;
        if (updating_status == WEST) {
          // rotate 90 degrees to the left
          Serial.print("090L");

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        } else if (updating_status == EAST) {
          // rotate 90 degrees to the right
          Serial.print("090R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        } else if (updating_status == NORTH) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);
        }
        updating_status = SOUTH;
      }
      /*
                6
                ^
                |
                ^
                |
                4 ------ 5
                */
      else if (target_position == ELEVATORS) {
        updating_current_position = updating_current_position + 2;
        if (updating_status == WEST) {
          // rotate 90 degrees to the right
          Serial.print("090R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        } else if (updating_status == EAST) {
          // rotate 90 degrees to the left
          Serial.print("090L");

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        } else if (updating_status == SOUTH) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);
        }
        updating_status = NORTH;
      }
      // 3 <--<-- 4
      else {
        updating_current_position = updating_current_position - 1;
        if (updating_status == EAST) {
          // rotate 180 degrees
          Serial.print("180R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, HIGH);
          digitalWrite(bit_two, LOW);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(3000);

        } else if (updating_status == NORTH) {
          // rotate 90 degrees to the left
          Serial.print("090L");

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);

        } else if (updating_status == SOUTH) {
          // rotate 90 degrees to the right
          Serial.print("090R");

          digitalWrite(bit_zero, HIGH);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, HIGH);

          delay(100);

          digitalWrite(bit_zero, LOW);
          digitalWrite(bit_one, LOW);
          digitalWrite(bit_two, LOW);

          delay(2000);
        }
        updating_status = WEST;
      }
    }
    // 4 <--<--<-- 5
    else if (updating_current_position == LECTURE_HALL) {
      updating_current_position = updating_current_position - 1;
      if (updating_status == EAST) {
        // rotate 180 degrees
        Serial.print("180R");

        digitalWrite(bit_zero, HIGH);
        digitalWrite(bit_one, HIGH);
        digitalWrite(bit_two, LOW);

        delay(100);

        digitalWrite(bit_zero, LOW);
        digitalWrite(bit_one, LOW);
        digitalWrite(bit_two, LOW);

        delay(3000);
      }
      updating_status = WEST;
    }
    /*
            4 ------ 5
            ^
            |
            ^
            |
            7
            */
    else if (updating_current_position == CALIBRATION_LAB) {
      updating_current_position = updating_current_position - 3;
      if (updating_status == SOUTH) {
        // rotate 180 degrees
        Serial.print("180R");

        digitalWrite(bit_zero, HIGH);
        digitalWrite(bit_one, HIGH);
        digitalWrite(bit_two, LOW);

        delay(100);

        digitalWrite(bit_zero, LOW);
        digitalWrite(bit_one, LOW);
        digitalWrite(bit_two, LOW);

        delay(3000);
      }
      updating_status = NORTH;
    }
    /*
            6
            |
            |
            4 ------ 5
            */
    else if (updating_current_position == ELEVATORS) {
      updating_current_position = updating_current_position - 2;
      if (updating_status == NORTH) {
        // rotate 180 degrees
        Serial.print("180R");

        digitalWrite(bit_zero, HIGH);
        digitalWrite(bit_one, HIGH);
        digitalWrite(bit_two, LOW);

        delay(100);

        digitalWrite(bit_zero, LOW);
        digitalWrite(bit_one, LOW);
        digitalWrite(bit_two, LOW);

        delay(3000);
      }
      updating_status = SOUTH;
    }

    (*current_position_local).destination = updating_current_position;
    (*current_position_local).status = updating_status;
  }

  return NOT_OK;
}
