#include <Arduino.h>
#include <avr/interrupt.h>
#include "pulse.h"

#pragma region PULSE SETTINGS
    // используются в обработчиках вращения энкодера
    volatile uint16_t pulse_p1;
    volatile uint16_t pulse_t;
    volatile uint16_t pulse_p2;

    volatile uint8_t step; // используется в обработчике прерывания
    volatile bool sequenceActive = false;
#pragma endregion


void stopPulseSequence(void)
{
    cli();
    TCCR1B = 0;
    sei();
    TCCR1A = 0;
    // TCCR1C = 0;
    // TIMSK1 = 0;
    TCNT1 = 0;
    OCR1A = 0;
    step = 0;
    sequenceActive = false;
}

void startPulseSequence(void)
{
    if (sequenceActive) return;
    cli();
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCCR1C |= (1 << FOC1A);
    sei();
    sequenceActive = true;
}

void setPulseSequence(uint8_t _p1, uint8_t _t, uint8_t _p2)
{
    if (sequenceActive) return;// Проверка, если последовательность еще не закончена то выход

    pulse_p1 = 250 * _p1;
    pulse_t = 250 * _t;
    pulse_p2 = 250 * _p2;

    // cli();
    TCCR1B |= (1 << WGM12);
    TCCR1A |= (1 << COM1A0);
    TIMSK1 |= (1 << OCIE1A);
    // sei();
}

ISR(TIMER1_COMPA_vect)
{
    step++;
    switch (step)
    {
    case 1:
        OCR1A = pulse_p1;
        break;
    case 2:
        OCR1A = pulse_t;
        break;
    case 3:
        OCR1A = pulse_p2;
        break;
    case 4:
        stopPulseSequence();
        break;
    }
}

bool isPulseRunning(void)
{
    return sequenceActive ? true : false;
}