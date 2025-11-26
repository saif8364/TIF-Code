#include <Arduino.h>
#include "MotorControl.h"

void forward(int pwm1, int pwm2)
{
  Serial.println("Moving Forward........");
  if (pwm2 == 0)
    pwm2 = pwm1;
  if (pwm1 == 255)
    pwm2 = 255;
  
  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, pwm2 + 3);
  analogWrite(R2, 0);
}

void backward(int pwm1, int pwm2)
{
  Serial.println("Moving Backward........");
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, 0);
  analogWrite(L2, pwm1);
  analogWrite(R1, 0);
  analogWrite(R2, pwm2);
}

void halt()
{
  noInterrupts();
  analogWrite(L1, 0);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  interrupts();
}

void right(int pwm1, int pwm2)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(R1, pwm2);
  analogWrite(R2, 0);
  analogWrite(L1, 0);
  analogWrite(L2, pwm1);
}

void left(int pwm1, int pwm2)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, pwm2);
}

void swerveLeft(int pwm1, int pwm2)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, pwm2 - (pwm2 / 3));
  analogWrite(R2, 0);
}

void swerveRight(int pwm1, int pwm2)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1 - (pwm1 / 3));
  analogWrite(L2, 0);
  analogWrite(R1, pwm2);
  analogWrite(R2, 0);
}
