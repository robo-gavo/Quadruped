//JUST DON'T FUCKING USE DIGITAL PIN 12
//JUST DON'T FUCKING DO IT.

/*
Analog pins can be used by using number 14 to 19
doesn't work past 19
Pin 14 = Analog in 0
Pin 15 = Analog in 1
Pin 16 = Analog in 2
Pin 17 = Analog in 3
Pin 18 = Analog in 4
Pin 19 = Analog in 5
*/

#include <Servo.h>

//front right leg: s1, s2, s9
//front left leg: s3, s4, s10
//back right leg: s5, s6, s12
//back left leg: s7, s8, s11

//int

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;
Servo s7;
Servo s8;
Servo s9;
Servo s10;
Servo s11;
Servo s12;

int incomingByte = 0;
//char frontBack = 'z';
//char rightLeft = 'z';
//char ankleKneeHip = 'z';
//int angle = -1;

void setup() {
  // put your setup code here, to run once:

  ServoSetup();

  Serial.begin(9600);
  
  s1.write(90);
  s2.write(0);
  s3.write(90);
  s4.write(180);
  s5.write(90);
  s6.write(180);
  s7.write(90);
  s8.write(0);
  s9.write(135);
  s10.write(45);
  s11.write(135);
  s12.write(45);
  
}

void ServoSetup()
{
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s4.attach(5);
  s5.attach(6);
  s6.attach(7);
  s7.attach(8);
  s8.attach(9);
  s9.attach(10);
  s10.attach(11);
  s11.attach(18);
  s12.attach(19);
}

void loop()
{
  // put your main code here, to run repeatedly:

  char frontBack = 'z';
  char leftRight = 'z';
  char ankleKneeHip = 'z';
  int angle = -1;


  frontBack = GetFrontBack();

  if (frontBack != 'z')
  {
    leftRight = GetLeftRight();
  }

  if (leftRight != 'z')
  {
    ankleKneeHip = GetAnkleKneeHip();
  }

  if (ankleKneeHip != 'z')
  {
    angle = GetAngle();
  }

  if (frontBack != 'z' && leftRight != 'z' && ankleKneeHip != 'z' && angle != -1)
  {
    ExecuteMech(frontBack, leftRight, ankleKneeHip, angle);
  }


  Serial.println("Leg Control");

}

char GetFrontBack()
{
  Serial.println("Front or back: f / b");

  bool received = false;
  char outputChar = 'z';

  while (!received)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      outputChar = Serial.read();
      //String newString = String(incomingByte);
      //outputChar = incomingByte;

      // say what you got:
      //Serial.print("I received: ");
      //Serial.println(incomingByte);
      //Serial.println(newString);
      //Serial.println(newChar);

      Serial.println(outputChar);

      if (outputChar == 'f' || outputChar == 'b')
      {
        //im drunk and i can't condition
      }
      else
      {
        Serial.println("Quitting...");
        outputChar = 'z';
      }

      received = true;
    }
  }

  return outputChar;
}

char GetLeftRight()
{
  Serial.println("Left or right: l / r");

  bool received = false;
  char outputChar = 'z';

  while (!received)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      outputChar = Serial.read();
      //String newString = String(incomingByte);

      // say what you got:
      //Serial.print("I received: ");
      //Serial.println(incomingByte);
      //Serial.println(newString);
      //Serial.println(newChar);

      if (outputChar == 'l' || outputChar == 'r')
      {
        //still drunk
      }
      else
      {
        Serial.println("Quitting...");
        outputChar = 'z';
      }

      received = true;
    }
  }

  return outputChar;
}

char GetAnkleKneeHip()
{
  Serial.println("Ankle, Knee, or Hip: a / k / h");

  bool received = false;
  char outputChar = 'z';

  while (!received)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      outputChar = Serial.read();
      //String newString = String(incomingByte);
      //      outputChar = incomingByte;

      // say what you got:
      //Serial.print("I received: ");
      //Serial.println(incomingByte);
      //Serial.println(newString);
      //Serial.println(newChar);

      if (outputChar == 'a' || outputChar == 'k' || outputChar == 'h')
      {
        //i shouldn't have drank... yea right.
      }
      else
      {
        Serial.println("Quitting...");
        outputChar = 'z';
      }

      received = true;
    }
  }

  return outputChar;
}

int GetAngle()
{
  Serial.println("Angle (0 - 180)");

  bool received = false;
  char inData[4];
  char inChar = -1;
  int index = 0;
  int outputAngle = -1;
  String angleString = "";

  while (!received)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      
      /*
      while (Serial.available() > 0)
      {
        inChar = Serial.read();
        Serial.print("inChar is ");
        Serial.println(inChar);
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
      //String newString = String(incomingByte);

      // say what you got:
      //Serial.print("I received: ");
      //Serial.println(incomingByte);
      //Serial.println(newString);
      //Serial.println(newChar);

      Serial.println(inData);
      
      
      angleString = inData;
      */
      
      angleString = Serial.readString();
      outputAngle = angleString.toInt();

      if (outputAngle > 180)
      {
        Serial.println("Lowered to 180");
        outputAngle = 180;
      }
      else if (outputAngle < 0)
      {
        Serial.println("Increased to 0");
        outputAngle = 0;
      }

      received = true;
    }
  }

  return outputAngle;
}

void ExecuteMech(char frontBack, char leftRight, char ankleKneeHip, int angle)
{
  int servoNumber = -1;

  if (frontBack == 'f' && leftRight == 'r' && ankleKneeHip == 'a')
  {
    servoNumber = 1;
  }
  else if (frontBack == 'f' && leftRight == 'r' && ankleKneeHip == 'k')
  {
    servoNumber = 2;
  }
  else if (frontBack == 'f' && leftRight == 'r' && ankleKneeHip == 'h')
  {
    servoNumber = 9;
  }
  else if (frontBack == 'f' && leftRight == 'l' && ankleKneeHip == 'a')
  {
    servoNumber = 3;
  }
  else if (frontBack == 'f' && leftRight == 'l' && ankleKneeHip == 'k')
  {
    servoNumber = 4;
  }
  else if (frontBack == 'f' && leftRight == 'l' && ankleKneeHip == 'h')
  {
    servoNumber = 10;
  }
  else if (frontBack == 'b' && leftRight == 'r' && ankleKneeHip == 'a')
  {
    servoNumber = 5;
  }
  else if (frontBack == 'b' && leftRight == 'r' && ankleKneeHip == 'k')
  {
    servoNumber = 6;
  }
  else if (frontBack == 'b' && leftRight == 'r' && ankleKneeHip == 'h')
  {
    servoNumber = 12;
  }
  else if (frontBack == 'b' && leftRight == 'l' && ankleKneeHip == 'a')
  {
    servoNumber = 7;
  }
  else if (frontBack == 'b' && leftRight == 'l' && ankleKneeHip == 'k')
  {
    servoNumber = 8;
  }
  else if (frontBack == 'b' && leftRight == 'l' && ankleKneeHip == 'h')
  {
    servoNumber = 11;
  }
  else
  {
    Serial.println("Why the fuck am i here?");
  }

  if (servoNumber == 1 || servoNumber == 9 || servoNumber == 4 || servoNumber == 6 || servoNumber == 7 || servoNumber == 11)
  {
    if (angle > 180)
    {
      Serial.println("Reducing angle to 90");
      angle = 180;
    }
    else if (angle < 90)
    {
      Serial.println("Increasing angle to 90");
      angle = 90;
    }
  }

  else
  {
    if (angle < 0)
    {
      Serial.println("Increasing angle to 0");
      angle = 0;
    }
    else if (angle > 90)
    {
      Serial.println("Decreasing angle to 90");
      angle = 90;
    }
  }

  Serial.print("Moving servo ");
  Serial.print(servoNumber);
  Serial.print(" to ");
  Serial.print(angle);
  Serial.println(" degrees");

  switch (servoNumber)
  {
    case 1:
      s1.write(angle);
      break;
    case 2:
      s2.write(angle);
      break;
    case 3:
      s3.write(angle);
      break;
    case 4:
      s4.write(angle);
      break;
    case 5:
      s5.write(angle);
      break;
    case 6:
      s6.write(angle);
      break;
    case 7:
      s7.write(angle);
      break;
    case 8:
      s8.write(angle);
      break;
    case 9:
      s9.write(angle);
      break;
    case 10:
      s10.write(angle);
      break;
    case 11:
      s11.write(angle);
      break;
    case 12:
      s12.write(angle);
      break;
    default:
      Serial.println("Why the fuck am i here");
      break;
  }
}
