#include <Arduino.h>
#include "EncoderControl.h"
#include "MotorControl.h"

int enc1_counter = 0;
int enc2_counter = 0;

void enc1_isr() { enc1_counter++; }

void enc2_isr() { enc2_counter++; }

void forwardWithEncoder(int pwm, int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    forward(pwm);
    interrupts();
  }
  halt();
}

void backwardWithEncoder(int pwm, int ticks, int stopdelay)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    backward(pwm);
    interrupts();
  }
  delay(stopdelay);
  halt();
}

void left90(int pwm)
{
  enc1_counter = 0;
  while (enc1_counter < 235)
  {
    left(pwm);
    interrupts();
  }
  halt();
}

void leftTurnEncoder(int pwm, int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    left(pwm);
    interrupts();
  }
  halt();
}

void right90(int pwm1, int pwm2)
{
  pwm2 = pwm1;
  enc1_counter = 0;
  while (enc1_counter < 240)
  {
    right(pwm1, pwm2);
    interrupts();
  }
  halt();
}

void rightTurnEncoder(int pwm, int ticks, int pwm2)
{
  if (pwm2 == 0)
  {
    pwm2 = pwm;
  }

  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    right(pwm, pwm2);
    interrupts();
  }
  halt();
}
