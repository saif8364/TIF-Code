#include "StepperControl.h"
#include <AccelStepper.h>

// --- CNC Shield Pinout --- 
#define X_STEP 22
#define X_DIR 26

#define Y_STEP 24
#define Y_DIR 28

#define EN_PIN 8  // shared enable pin

AccelStepper stepperX(AccelStepper::DRIVER, X_STEP, X_DIR);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP, Y_DIR);

void setupStepper() {
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable motor drivers

  stepperX.setMaxSpeed(300);
  stepperX.setAcceleration(150);

  stepperY.setMaxSpeed(300);
  stepperY.setAcceleration(150);
}

// ===========================================================
// STEP UP
// ===========================================================
void stepUp() {
  stepperY.setSpeed(200);  // Positive steps
  stepperX.setSpeed(-200);
  while (true) {
    stepperX.runSpeed();
    stepperY.runSpeed();
  }
}

// ===========================================================
// STEP DOWN
// ===========================================================
void stepDown() {
  stepperY.setSpeed(-200);  // Negative steps
  stepperX.setSpeed(200);
  while (true) {
    stepperX.runSpeed();
    stepperY.runSpeed();
  }
}

// ===========================================================
// STOP STEPPER
// ===========================================================
void stopStepper() {
  stepperY.stop();
  stepperX.stop();
}

// ===========================================================
// ROTATE CLOCKWISE
// ===========================================================
void rotateStep(int steps) {
  stepperY.move(steps);
  stepperX.move(-steps);
  while (stepperX.run() | stepperY.run()) {}
}

// ===========================================================
// ROTATE COUNTER-CLOCKWISE
// ===========================================================
void rotateDown(int steps) {
  stepperY.move(-steps);
  stepperX.move(steps);
  while (stepperX.run() | stepperY.run()) {}
}
