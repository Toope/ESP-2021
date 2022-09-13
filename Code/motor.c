#include "motor.h"
#include <inttypes.h>


void setup_motors()  //setup_pins() handles this for now
{
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

void update_motor(int motor_state, int motor_no)
{
	/*
	Motor states: 
	0 = No movement
	1 = Forward
	2 = Backwards
	
	Motor numbers:
	0 = Left
	1 = Right
	*/
	
	if(motor_no == 0)
	{
		switch(motor_state)
		{
			case 0:
				PORTA &= ~(1 << PA0);
				PORTA &= ~(1 << PA1);
				break;
			case 1:
				PORTA |= (1 << PA0);
				PORTA &= ~(1 << PA1);
				break;
			case 2:
				PORTA &= ~(1 << PA0);
				PORTA |= (1 << PA1);
				break;
			default:
				PORTA &= ~(1 << PA0);
				PORTA &= ~(1 << PA1);
				break;
			
		}	
	}
	else
	{
		switch(motor_state)
		{
			case 0:
				PORTA &= ~(1 << PA2);
				PORTA &= ~(1 << PA3);
				break;
			case 1:
				PORTA |= (1 << PA2);
				PORTA &= ~(1 << PA3);
				break;
			case 2:
				PORTA &= ~(1 << PA2);
				PORTA |= (1 << PA3);
				break;
			default:
				PORTA &= ~(1 << PA2);
				PORTA &= ~(1 << PA3);
				break;
					
		}
	}	
}

unsigned char ReadEncoderDirection(int motor_no){
	
	/* 		
	Motor numbers:
	0 = Left
	1 = Right
	
	
	Returns the direction the motor is moving:
	0 = Error reading the direction
	1 = Forwards
	2 = Backwards
	*/
	
	/* These are used to determine the state off the encoder pins */
	uint8_t EN0, EN1;
	
	if(motor_no == 0){
		EN0 = 0b00000001; //PIN B0
		EN1 = 0b00000010; //PIN B1
	}
	else
	{
		EN0 = 0b00000100; //PIN B2
		EN1 = 0b00001000; //PIN B3
	}
	
		int total;
		total = 0;
		uint8_t new;
		
		for(int i = 0; i < 10; i++)
		{
			if( (PINB & EN0) == EN0)
			{
				new = 0;
			}
			else
			{
				new = 1;
			}
			
			if(new == 0)
			{
				if( (PINB & EN1) == EN1)
				{
					total += 1; //Goes Either direction
				}
				else
				{
					total -= 1; //Goes the other direction			
				}
			}
			else
			{
				if( (PINB & EN1) == EN1 )
				{
					total -= 1; //Goes Either direction
				}
				else
				{
					total += 1; //Goes the other direction
				}
			}
		}
		
	if(total < 0){
		return 1;
	}
	else if(total > 0){
		return 2;
	}
	//else: total == 0
	return 0;
}


void MoveDirection(int cmd){
	/*
	Commands:
	0 = Stop
	1 = Forwards
	2 = Backwards
	3 = Left
	4 = Right
	*/
	
	switch(cmd){
		case 0:
			update_motor(0, 0);		// Stop
			update_motor(0, 1);		// Stop
			break;
		case 1:
			update_motor(1, 0);		// Forwards
			update_motor(1, 1);		// Forwards
			break;
		case 2:
			update_motor(2, 0);		// Backwards
			update_motor(2, 1);		// Backwards
			break;
		case 3:
			update_motor(2, 0);		// Backwards, Left
			update_motor(1, 1);		// Forwards, Right
			break;
		case 4:
			update_motor(1, 0);		// Backwards, Left
			update_motor(2, 1);		// Forwards, Right
			break;
		default:
			update_motor(0, 0);		// Stop
			update_motor(0, 1);		// Stop
			break;
	}
	
}