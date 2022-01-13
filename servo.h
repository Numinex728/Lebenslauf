#ifndef SERVO_H
#define SERVO_H

#include "stdint.h"

// initialisiert PA0 und Timer6 fuer Nutzung durch Servo
void init_servo(void);

// setzt Servo auf gewuenschte Position
// Parameter position = 0, 10, 20, ...
// Stellvorgang dauert 0,5 s
// nutzt Timer 6 zur Pulsgenerierung
//Verändert zu signed Int
void set_servo(int16_t position);

#endif
