#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "LineFollow.h"
#include "ServoControl.h"
#include "SonarControl.h"



#define ENC1 2
#define ENC2 3

#define ARENA 32

void readSensorValsDebugAnalog(int *sensors)
{
  for (int i = 0; i < 5; i++)
  {
    Serial.print(analogRead(sensors[i]));
    Serial.print("\t");
  }
  Serial.println();
  delay(100);
}

void readSensorValsDebugDigital(int *sensors)
{
  int leftm1 = analogRead(sensors[0]) > 800 ? 1 : 0;
  int left1 = analogRead(sensors[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(sensors[2]) > 800 ? 1 : 0;
  int right1 = analogRead(sensors[3]) > 800 ? 1 : 0;
  int rightm1 = analogRead(sensors[4]) > 800 ? 1 : 0;

  Serial.print(leftm1);
  Serial.print("  ");
  Serial.print(left1);
  Serial.print("  ");
  Serial.print(middle1);
  Serial.print("  ");
  Serial.print(right1);
  Serial.print("  ");
  Serial.println(rightm1);
  delay(100);
}

void stripCountDebug(int strips)
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
    Serial.println(strips_count);
  }
  else
  {
    // halt();
    Serial.print(strips_count);
    Serial.print(" ");
    Serial.println("End");
    strips_count = 0;
    return;
  }
}

void forwardUntilMiddleSensors()
{
  int mid1_val = analogRead(MID1) > 800 ? 1 : 0;
  int mid2_val = analogRead(MID2) > 800 ? 1 : 0;

  while (mid1_val == 1 && mid2_val == 1)
  {
    forward(50);
    mid1_val = analogRead(MID1) > 800 ? 1 : 0;
    mid2_val = analogRead(MID2) > 800 ? 1 : 0;
  }
  halt();
}

void Controller_Mode()
{
 if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "FORWARD") {
      Serial.print('Moving Forward');
      forward(80);
    }
    else if (cmd == "BACKWARD") {
      Serial.print('Moving Backward');
      backward(80);
    }
    else if (cmd == "LEFT") {
      Serial.print('Turning Left');
      left90(80);
    }
    else if (cmd == "RIGHT") {
        Serial.print('Turning Right');
      right90(80);
    }
    else if (cmd == "STOP") {
       Serial.print('Robot is Stopped');
      halt();
    }
     else if (cmd == "LineFollow") {
       Serial.print('Following Line');
      linefollow(80);
    }
    else{
      Serial.print('Invalid Instruction');
    }
}}

void configurePins()
{
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC1), enc1_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC2), enc2_isr, RISING);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  pinMode(ARENA, INPUT_PULLUP);

  pinMode(MID1, INPUT);
  pinMode(MID2, INPUT);

  mainServo.attach(M_SERVO);
  Servo1.attach(SERVO_1);
  Servo2.attach(SERVO_2);
  Servo3.attach(SERVO_3);


  
  mainServo.write(0);
  Servo1.write(0);
  Servo2.write(0);
  Servo3.write(0);

  for (size_t i = 0; i < sizeof(S1) / sizeof(int); i++)
  {
    pinMode(S1[i], INPUT);
  }

  for (size_t i = 0; i < sizeof(S2) / sizeof(int); i++)
  {
    pinMode(S2[i], INPUT);
  }

  delay(1000);
}


int modeSwitch = 7;
bool controllerMode = false;

void setup() {
  Serial.begin(9600);
  pinMode(modeSwitch, INPUT_PULLUP);


  if (digitalRead(modeSwitch) == LOW) {
    controllerMode = true;    // switch ON
  } else {
    controllerMode = false;   // switch OFF
  }

  initSonar();
}

void loop() {

  if (controllerMode) {
     Controller_Mode();
  
  } else {
   
    Serial.println("Autonomous Mode");
   }
  }