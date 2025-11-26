#ifndef _ENCODECONTROL_H_
#define _ENCODECONTROL_H_

extern int enc1_counter;
extern int enc2_counter;

void enc1_isr();
void enc2_isr();

void forwardWithEncoder(int pwm, int ticks);
void backwardWithEncoder(int pwm, int ticks, int stopdelay = 0);
void left90(int pwm);
void leftTurnEncoder(int pwm, int ticks);
void right90(int pwm1, int pwm2 = 0);
void rightTurnEncoder(int pwm, int ticks, int pwm2 = 0);

#endif // _ENCODECONTROL_H_