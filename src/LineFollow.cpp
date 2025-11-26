#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "LineFollow.h"

int strips_count = 0;
bool is_line = false;

unsigned long previousMillis = 0; // Store the last time sensor was checked
const unsigned long intervalMillis = 500;

int S1[] = {A4, A3, A2, A1, A0};
int S2[] = { A8,A9,A10,A11,A12};



void startLineFollow()
{
  
  linefollowUntil(4);
  delay(500);
  leftTurnEncoder(80, 255);
  delay(500);

}

void finalDestination()
{
  backLinefollowUntil(5);
  delay(200);
  backLinefollowEncoder(130);
  delay(500);
  linefollowUntil(1);
  delay(500);
  leftTurnEncoder(80, 255);
  delay(500);
  linefollowUntil(5);
  delay(500);
  leftTurnEncoder(80, 255);
  delay(500);
  linefollowEncoder(120);
  delay(500);
  backLinefollowUntil(2);
  delay(500);
  right90(80);
  delay(500);
  linefollowEncoder(550);
  
}
void linefollow(int speed)
{
  // white 1
  // black 0

  int left1 = analogRead(S1[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(S1[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S1[3]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    forward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    forward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    left(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    right(speed);
  }
  else
  {
    forward(speed);
  }
}

void linefollowUntil(int strips)
{
  while (true)
  {
    int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
    unsigned long currentMillis = millis();

    if (leftm1 == 0 && !is_line)
    {
      strips_count++;
      is_line = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      is_line = false;
    }

    if (strips_count < strips)
    {
      linefollow();
      Serial.print("hello: ");
      Serial.println(strips_count);
    }
    else
    {
      halt();
      strips_count = 0;
      return;
    }
  }
}

void linefollowEncoder(int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    linefollow(30);
    interrupts();
  }
  halt();
}

void linefollowWithFive(int speed)
{
  // white 1
  // black 0

  int leftm1 = analogRead(S1[0]) > 800 ? 1 : 0;
  int left1 = analogRead(S1[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(S1[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S1[3]) > 800 ? 1 : 0;
  int rightm1 = analogRead(S1[4]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    forward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    forward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    left(speed);
  }
  else if (leftm1 == 0 && middle1 == 1 && right1 == 1)
  {
    left(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    right(speed);
  }
  else if (left1 == 1 && middle1 == 1 && rightm1 == 0)
  {
    right(speed);
  }
  else
  {
    forward(speed);
  }
}

void linefollowFiveUntil(int strips)
{
  while (true)
  {
    int leftm1 = digitalRead(MID2) ;
    Serial.println(leftm1);
    unsigned long currentMillis = millis();

    if (leftm1 == 0 && !is_line)
    {
      strips_count++;
      is_line = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      is_line = false;
    }

    if (strips_count < strips)
    {
      linefollowWithFive();
      Serial.println(strips_count);
    }
    else
    {
      halt();
      strips_count = 0;
      return;
    }
  }
}

void linefollowFiveEncoder(int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    linefollowWithFive(30);
    interrupts();
  }
  halt();
}

void backLinefollow(int speed)
{
  // white 1
  // black 0

  // S2[3] == left
  // S2[2] == middle
  // S2[1] == right

  int left1 = analogRead(S2[3]) > 800 ? 1 : 0;
  int middle1 = analogRead(S2[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S2[1]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    backward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    backward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    right(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    left(speed);
  }
  else
  {
    backward(speed);
  }
}

void backLinefollowUntil(int strips)
{
  while (true)
  {
    int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
    unsigned long currentMillis = millis();

    if (leftm1 == 0 && !is_line)
    {
      strips_count++;
      is_line = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      is_line = false;
    }

    if (strips_count < strips)
    {
      backLinefollow();
      Serial.print("hello: ");
      Serial.println(strips_count);
    }
    else
    {
      halt();
      strips_count = 0;
      return;
    }
  }
}

void backLinefollowEncoder(int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    backLinefollow(30);
    interrupts();
  }
  halt();
}

void backLinefollowWithFive(int speed)
{
  // white 1
  // black 0

  // S2[3] == left
  // S2[2] == middle
  // S2[1] == right

  int leftm1 = analogRead(S2[4]) > 800 ? 1 : 0;
  int left1 = analogRead(S2[3]) > 800 ? 1 : 0;
  int middle1 = analogRead(S2[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S2[1]) > 800 ? 1 : 0;
  int rightm1 = analogRead(S2[0]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    backward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    backward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    right(speed);
  }
  else if (leftm1 == 0 && middle1 == 1 && right1 == 1)
  {
    right(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    left(speed);
  }
  else if (left1 == 1 && middle1 == 1 && rightm1 == 0)
  {
    left(speed);
  }
  else
  {
    backward(speed);
  }
}

void backLinefollowFiveUntil(int strips)
{
  while (true)
  {
    int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
    unsigned long currentMillis = millis();

    if (leftm1 == 0 && !is_line)
    {
      strips_count++;
      is_line = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      is_line = false;
    }

    if (strips_count < strips)
    {
      backLinefollowWithFive();
      Serial.print("hello: ");
      Serial.println(strips_count);
    }
    else
    {
      halt();
      strips_count = 0;
      return;
    }
  }
}

void backLinefollowFiveEncoder(int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    backLinefollowWithFive(50);
    interrupts();
  }
  halt();
}