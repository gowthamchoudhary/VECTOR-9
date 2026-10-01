#include <ESP32Servo.h>

#define VRX 34
#define VRY 35

#define SERVO_PIN1 18
#define SERVO_PIN2 19

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(115200);
  servo1.attach(SERVO_PIN1);
  servo2.attach(SERVO_PIN2);
}

void loop() {

  int x = analogRead(VRX);
  int y = analogRead(VRY);
  int angle_X = map(x, 0, 4095, 0, 180);
  int angle_y = map(y,0,4095,0,180);
  servo1.write(angle_X);
  servo2.write(angle_y);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("   Angle: ");
  Serial.println(angle_X);
  Serial.print("y: ");
  Serial.print(y);
  Serial.println(angle_y);

  
  delay(20);
}