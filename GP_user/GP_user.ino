#include "TinyGPS.h"
#include <SoftwareSerial.h>
#include <QMC5883LCompass.h>


#define QMC5883l_N 0
#define QMC5883l_NE 1
#define QMC5883l_E 2
#define QMC5883l_ES 3
#define QMC5883l_S 4
#define QMC5883l_SW 5
#define QMC5883l_W 6
#define QMC5883l_WN 7

SoftwareSerial BTSerial(10, 11);  // RX | TX

const int RXPin = 3, TXPin = 4;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600

// int x_value;
// int y_value;
// int z_value;
int azimuth;   // 0° - 359°
char buffer[strlen("X=-99999 | Y=-99999 | Z=-99999 | A=259° | B=15 | D=NNE") + 1];

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXPin, TXPin); // the serial interface to the GPS device
QMC5883LCompass compass;

unsigned long lastPrintTime = 0;           // the time when the GPS data was last printed
const unsigned long printInterval = 1000;  // the interval between GPS prints in milliseconds

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
   gpsSerial.begin(GPSBaud);
   compass.init();
   compass.setCalibration(-568, 988, 940, 2551, 558, 1963);
  Serial.println(F("Arduino - GPS module"));
}

void loop() {

  if (BTSerial.available()) {
    char receivedChar = BTSerial.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
    if (receivedChar == 'S') {
      if (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
          if (gps.location.isValid()) {
            double lat = gps.location.lat();
            double lng = gps.location.lng();

            compass.read();  // Read compass values via I2C

            azimuth = compass.getAzimuth();  // Calculated from X and Y value

            sprintf(buffer,"A=%3d°",azimuth);

            BTSerial.print(lat);
            BTSerial.print("\r\n");
            BTSerial.print(lng);
            BTSerial.print("\r\n");
            BTSerial.print(getDirecton(azimuth));
            BTSerial.print("\r\n");

          }
        }
      }
    }
  }
}

char getDirecton(float angle) {
    char direction;

    if (angle < 0) {
      angle += 360;
    }
    if ((angle > 292.5) && (angle <= 337.5)) {
      direction = QMC5883l_WN;

    } else if ((angle > 22.5) && (angle <= 67.5)) {
      direction = QMC5883l_NE;
    } else if ((angle > 67.5) && (angle <= 112.5)) {
      direction = QMC5883l_E;
    } else if ((angle > 112.5) && (angle <= 157.5)) {
      direction = QMC5883l_ES;
    } else if ((angle > 157.5) && (angle <= 202.5)) {
      direction = QMC5883l_S;
    } else if ((angle > 202.5) && (angle <= 247.5)) {
      direction = QMC5883l_SW;
    } else if ((angle > 247.5) && (angle <= 292.5)) {
      direction = QMC5883l_W;
    } else {
      direction = QMC5883l_N;
    }
    return direction;
  }







      // char sendChar = 'G'; // Example character to send
      // BTSerial.write(sendChar);
      // Serial.print("Sent: ");
      //Serial.println(sendChar);

  //       unsigned long currentTime = millis();
  //       if (currentTime - lastPrintTime >= printInterval) {
  //         Serial.print(F("- latitude: "));
  //         Serial.println(lat, 14); // print latitude with 14 decimal places

  //         Serial.print(F("- longitude: "));
  //         Serial.println(lng, 14); // print longitude with 14 decimal places

  //         Serial.println(direction);
  //       unsigned long currentTime = millis();
  //       if (currentTime - lastPrintTime >= printInterval) {
  //         Serial.print(F("- latitude: "));
  //         Serial.println(lat, 14); // print latitude with 14 decimal places

  //         Serial.print(F("- longitude: "));
  //         Serial.println(lng, 14); // print longitude with 14 decimal places

  //         Serial.println(direction);


            //       unsigned long currentTime = millis();
            //       if (currentTime - lastPrintTime >= printInterval) {
            //         Serial.print(F("- latitude: "));
            //         Serial.println(lat, 14); // print latitude with 14 decimal places

            //         Serial.print(F("- longitude: "));
            //         Serial.println(lng, 14); // print longitude with 14 decimal places

            //         Serial.println(direction);