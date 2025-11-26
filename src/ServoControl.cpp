#include <Arduino.h>
#include "ServoControl.h"

Servo mainServo;
Servo Servo1;
Servo Servo2;
Servo Servo3;

void mainServoMove(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      mainServo.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      mainServo.write(i);
      delay(10);
    }
  }
}

void Servo1Move(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      Servo1.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      Servo1.write(i);
      delay(10);
    }
  }
}



void Servo2Move(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      Servo2.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      Servo2.write(i);
      delay(10);
    }
  }
}


void Servo3Move(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      Servo3.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      Servo3.write(i);
      delay(10);
    }
  }
}
