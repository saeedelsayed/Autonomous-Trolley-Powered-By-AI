#include <QMC5883LCompass.h>
#include <NMEAGPS.h>
#include <AltSoftSerial.h>


#define QMC5883l_N 0
#define QMC5883l_NE 1
#define QMC5883l_E 2
#define QMC5883l_ES 3
#define QMC5883l_S 4
#define QMC5883l_SW 5
#define QMC5883l_W 6
#define QMC5883l_WN 7

#define Bluetooth Serial

AltSoftSerial gpsPort;
NMEAGPS gps;
gps_fix fix;

QMC5883LCompass compass;

int getDirecton(float angle);

void setup() {
  gpsPort.begin(9600);
  Bluetooth.begin(38400);

  compass.init();
  compass.setCalibration(-568, 988, 940, 2551, 558, 1963);
}

void loop() {
  if (Bluetooth.available()) {
    char BluetoothData = Bluetooth.read();
    if (BluetoothData == 'S') {
      if (gps.available(gpsPort)) {
        fix = gps.read();
      }

      compass.read();

      Bluetooth.print(fix.latitude(), 6);
      Bluetooth.print("\r\n");

      Bluetooth.print(fix.longitude(), 6);
      Bluetooth.print("\r\n");

      Bluetooth.print(getDirecton(compass.getAzimuth()));
      Bluetooth.print("\r\n");
    }
  }
}

int getDirecton(float angle) {
  int direction;

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