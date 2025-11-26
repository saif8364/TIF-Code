#ifndef _SERVOCONTROL_H_
#define _SERVOCONTROL_H_

#include <Servo.h>

#define M_SERVO 11
#define SERVO_1 10
#define SERVO_2 9
#define SERVO_3 8

extern Servo mainServo;
extern Servo Servo1;
extern Servo Servo2;
extern Servo Servo3;

void mainServoMove(int start, int end);
void Servo1Move(int start, int end);
void Servo2Move(int start, int end);
void Servo3Move(int start, int end);

#endif // _SERVOCONTROL_H_