#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600

const int SERVO_COUNT = 4;

int previousCount = -1;

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void moveServos(int fingerCount) {
  int activeServos = constrain(fingerCount, 0, SERVO_COUNT);

  for (int channel = 0; channel < SERVO_COUNT; channel++) {
    int angle = (channel < activeServos) ? 90 : 0;

    int pulse = angleToPulse(angle);

    pca.setPWM(channel, 0, pulse);
  }

  Serial.print("Finger count: ");
  Serial.println(fingerCount);
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  pca.begin();
  pca.setPWMFreq(50);

  delay(500);

  moveServos(0);
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    message.trim();

    if (message.length() > 0) {
      int fingerCount = message.toInt();
      fingerCount = constrain(fingerCount, 0, 5);

      if (fingerCount != previousCount) {
        moveServos(fingerCount);
        previousCount = fingerCount;
      }
    }
  }
}