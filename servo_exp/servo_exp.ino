#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

#define VRX 34
#define VRY 35

#define SERVOMIN 150
#define SERVOMAX 600

void setup() {
  Serial.begin(115200);

  pca.begin();
  pca.setPWMFreq(50);

  delay(500);
}

void loop() {
  int x = analogRead(VRX);
  int y = analogRead(VRY);

  int pulseX = map(x, 0, 4095, SERVOMIN, SERVOMAX);
  int pulseY = map(y, 0, 4095, SERVOMIN, SERVOMAX);

  pca.setPWM(0, 0, pulseX);
  pca.setPWM(1, 0, pulseY);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" | Pulse X: ");
  Serial.print(pulseX);

  Serial.print(" || Y: ");
  Serial.print(y);
  Serial.print(" | Pulse Y: ");
  Serial.println(pulseY);

  delay(20);
}