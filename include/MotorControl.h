#ifndef _MOTORCONTROL_H_
#define _MOTORCONTROL_H_

#define L1 4
#define L2 5

#define R1 7
#define R2 6

void forward(int pwm1, int pwm2 = 0);
void backward(int pwm1, int pwm2 = 0);
void left(int pwm1, int pwm2 = 0);
void right(int pwm1, int pwm2 = 0);
void swerveLeft(int pwm1, int pwm2 = 0);
void swerveRight(int pwm1, int pwm2 = 0);
void halt();

#endif // _MOTORCONTROL_H_