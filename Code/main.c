/*
Course:		521423S - Embedded Systems Programming
Project:	Bluetooth Controlled Mobile Robot
By:			Santtu Käpylä & Tiia Leinonen
*/

/*
Command for uploading the code via avrdude. Hex file can be found from the Debug folder
	avrdude -c usbtiny -p m644p -e -U flash:w:Robo_v2.hex 
*/

/* Clock frequency */
#define F_CPU 1000000UL  // 1 MHz


/* Needed header files */
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

/* Our own headers */
#include "basic.h"
#include "bt.h"
#include "motor.h"

/* Define UART baud rate */
#define USART_BAUDRATE      9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Ultrasonic sensor global variables */
static volatile int pulse = 0;
static volatile int i = 0;

/* BT global variable */
static volatile unsigned char ddata = 7;  // 7 is none of the control values

int main(void)
{
	/* Setup all pin directions */
	setup_pins();  

	/* Setup USART for BT connection*/
	USART_Init(BAUD_PRESCALE);
	UCSR0B |= (1 << RXCIE0);   //enable usart interrupt
	
	/* Turn on the P_LED to indicate that the device is turned on */
	pin_on(&PORTD, PD5);
	
	/* Other variables */
	int16_t distance = 0;  //distance

	sei();  //enable global interrupts
	
    while (1) 
    {
		/* Check if we're getting a valid value from BT module. */		
		if((int)ddata >= 0 && (int)ddata < 5)
		{
			pin_on(&PORTD, PD6);		 //turn LED BT on when we get valid value
			MoveDirection((int)ddata);	 //move the device for 0.1 seconds
			_delay_ms(100);
			MoveDirection((int)0);		 
			pin_off(&PORTD, PD6);
			ddata = 7;
		}
				
		/* Check the space for obstacles */
		send_pulse(&PORTD, PD4);				//send 10us pulse to PD4
		distance = pulse/58;					//pulse length to distance in cm
		if(distance > 0 && distance <= 20)		//if object in 20cm distance, beep
		{
			pin_on(&PORTD, PD7);
			_delay_ms(100);
			pin_off(&PORTD, PD7);
		}
		else
		{
			pin_off(&PORTD, PD7);  //no beep
		}
		_delay_ms(100);
    }
	return (0);
}

ISR(INT1_vect)  //interrupt for distance pulse, measures pulse length
{
	if(i == 0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
	else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}
}

ISR(USART0_RX_vect)	//interrupt for USART, echoes message back
{
	ddata = UDR0; // Fetch the received byte value 
	UDR0 = ddata; // Echo back the received byte
}
