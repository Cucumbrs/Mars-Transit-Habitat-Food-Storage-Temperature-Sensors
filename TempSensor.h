#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <Arduino.h>
#include "SDcard.h"

extern sdDataLogger logger;  // Global logger instance from main.cpp

// Initialize temperature/humidity sensor (call once in setup)

// Poll or process temperature/humidity (call frequently in loop)
void loopTempSensor();

#endif // TEMPSENSOR_H
