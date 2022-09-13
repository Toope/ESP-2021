#include "bt.h"

//base functions from atmega644p spec sheets, modified to fit our needs
void USART_Init( long baud )
{
	// Set baud rate
	UBRR0H = (unsigned char)(baud>>8);   //was typo UBRRH0
	UBRR0L = (unsigned char)baud;		 //was typo UBRRL0
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Set frame format: 0 = async(UMSEL00), 0 = no parity(UPM00), 0 = 1stop bit (USB0), 2 = 7data (UCSZ00), 0 = rising edge
	UCSR0C = 0b00000100;
}

/* Functions below are retired */

unsigned char USART_Receive(void){
	// Wait for data to be received
	while(!(UCSR0A&(1<<RXC0)));
	// Get and return received data from buffer
	return UDR0;
}

void USART_Transmit(unsigned char data){
	// Wait for empty transmit buffer
	while (!(UCSR0A&(1<<UDRE0)));
	// Put data into buffer, sends the data
	UDR0 = data;
}

void USART_Flush(void){
	unsigned char dummy;
	while(UCSR0A&(1<<RXC0))
	dummy = UDR0;
}
