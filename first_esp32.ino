int trigPin = 18;
int echoPin = 4;

int redPin = 23;
int greenPin = 22;

long duration;
long cm;

bool redState = false;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  cm = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  // Object is close
  if (cm <= 20) {

    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);

    if (redState == false) {
      Serial.println("RED");
      redState = true;
    }

  }

  // Object is far
  else {

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);

    redState = false;
  }

  delay(100);
}