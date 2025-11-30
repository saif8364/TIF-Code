#ifndef _STEPPERCONTROL_H_
#define _STEPPERCONTROL_H_

#include <Arduino.h>

// Stepper functions
void setupStepper();
void stepUp();
void stepDown();
void stopStepper();
void rotateStep(int steps);
void rotateDown(int steps);

#endif // _STEPPERCONTROL_H_
