#ifndef _SONARCONTROL_H_
#define _SONARCONTROL_H_

#include <Arduino.h>
#include <NewPing.h>

// Sonar Pins
#define SONAR_TRIG 32
#define SONAR_ECHO 30
#define MAX_DISTANCE 200  // cm

// External NewPing object
extern NewPing sonar;

// Functions
void initSonar();
unsigned int readSonarINCH();
unsigned int readSonarCM();
void debugSonar();

#endif
