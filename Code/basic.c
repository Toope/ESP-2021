/* Basic pin functions */
#include "basic.h"

void setup_pins()
{
	//setup pins as input or output
	DDRD |= (1 << PD5);			//LED Power
	DDRD |= (1 << PD6);			//LED BT
	DDRD |= (1 << PD7);			//Buzzer	
	DDRD |= (0 << PD3);			//Dist sensor echo
	DDRD |= (1 << PD4);			//Dist sensor trig
	EIMSK |= (1 << INT1);		//configure PIN1 = PD3 as interrupt pin
	EICRA |= (1 << ISC10);		//any interrupt for PIN1 counts
	
	//setup Motor pins as outputs
	DDRA |= (1 << PA0);
	DDRA |= (1 << PA1);
	DDRA |= (1 << PA2);
	DDRA |= (1 << PA3);
		
	//Setup MotorEncoder pins as inputs
	DDRB |= (0 << PB0);
	DDRB |= (0 << PB1);
	DDRB |= (0 << PB2);
	DDRB |= (0 << PB3);
		
	//Enable pull ups for MotorEncoder
	PORTB |= (1 << PB0);
	PORTB |= (1 << PB1);
	PORTB |= (1 << PB2);
	PORTB |= (1 << PB3);
	
}

void pin_flip(volatile uint8_t *port, uint8_t pin)
{
	*port ^= (1 << pin);	   // flip led state
}

void pin_on(volatile uint8_t *port, uint8_t pin)  
{
	*port |= (1 << pin);
}

void pin_off(volatile uint8_t *port, uint8_t pin)  
{
	*port &= ~(1 << pin);
}

/* Ultrasonic sensor */
void send_pulse(volatile uint8_t *port, uint8_t pin){  //use PORTD & PD4 for distance sensor
	*port |= (1 << pin);
	_delay_us(10);
	*port &= ~(1 << pin);
}