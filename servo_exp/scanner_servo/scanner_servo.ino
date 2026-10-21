  #include <ESP32Servo.h>

  const int SERVO_PIN = 18;
  const int TRIG_PIN = 19;
  const int ECHO_PIN = 5;


  Servo scanner;

  void setup(){
    Serial.begin(115200);
    scanner.attach (SERVO_PIN);
    scanner.write(0);
    pinMode(TRIG_PIN,OUTPUT);
    pinMode(ECHO_PIN,INPUT);

    }
  void loop(){
    for(int angle = 0;angle<=60;angle++){
      scanner.write(angle);  
      delay(15);
      
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);

digitalWrite(TRIG_PIN, LOW);
    unsigned long  duration = pulseIn(ECHO_PIN,HIGH,30000);
    float distance = duration*0.0343/2;
    Serial.print(distance);
Serial.println(" cm");
      }
  }