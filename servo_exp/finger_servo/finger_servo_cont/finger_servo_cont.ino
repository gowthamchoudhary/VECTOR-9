#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

void setup() {
  Wire.begin(21, 22);
  pca.begin();
  pca.setPWMFreq(50);
  delay(500);
}

void loop() {
  // Move all 4 servos to 0 degrees
  for (int i = 0; i < 4; i++) {
    pca.setPWM(i, 0, 150);
  }
  delay(1000);

  // Move all 4 servos to 90 degrees
  for (int i = 0; i < 4; i++) {
    pca.setPWM(i, 0, 375);
  }
  delay(1000);
}