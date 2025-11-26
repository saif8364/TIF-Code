#include "SonarControl.h"

// Create NewPing object
NewPing sonar(SONAR_TRIG, SONAR_ECHO, MAX_DISTANCE);

// Initialize sonar (optional for NewPing)
void initSonar() {
  Serial.println("Sonar initialized");
}

// Read distance in cm
unsigned int readSonarCM() {
  unsigned int cm = sonar.ping_cm();
  if (cm == 0) cm = MAX_DISTANCE; // handle out-of-range
  Serial.print("Distance: ");
   Serial.print(cm);
 Serial.println( " cm");  
  return cm;
}

// Read distance in inch
unsigned int readSonarINCH() {
  unsigned int inch = sonar.ping_in();
  if (inch == 0) inch = MAX_DISTANCE / 2.54; // handle out-of-range
  Serial.print("Distance: ");
  Serial.print(inch);
  Serial.println( " Inch");

  return inch;
}

// Debug print
void debugSonar() {
  unsigned int cm = readSonarCM();
  unsigned int inch = readSonarINCH();
  
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print(" cm | ");
  Serial.print(inch);
  Serial.println(" inch");
}
