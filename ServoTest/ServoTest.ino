#include <Servo.h>

int servoPin = 9;

Servo testServo;

void setup() {
  // put your setup code here, to run once:

  testServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  testServo.write(0);
}
