#ifndef BASIC_H_
#define BASIC_H_

/* Basic pin flip functions header file */

#include <avr/io.h>	
#include <util/delay.h>			// add this to use the delay function
#include "avr/interrupt.h"      //interrupts

/* Pin setups */
void setup_pins();

/* LED:s and Buzzer */
void pin_flip(volatile uint8_t *port, uint8_t pin);
void pin_on(volatile uint8_t *port, uint8_t pin);
void pin_off(volatile uint8_t *port, uint8_t pin);

/* Ultrasonic sensor */
void send_pulse(volatile uint8_t *port, uint8_t pin);

#endif