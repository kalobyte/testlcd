#ifndef pulse_h
#define pulse_h

#include <Arduino.h>
#include <avr/interrupt.h>

void stopPulseSequence(void);
void startPulseSequence(void);
bool isPulseRunning(void);
void setPulseSequence(uint8_t, uint8_t, uint8_t);

#endif