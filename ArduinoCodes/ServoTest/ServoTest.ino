#include <Servo.h>

int servoPin = 18;

Servo testServo;

void setup() {
  // put your setup code here, to run once:

  testServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  testServo.write(180);
}
