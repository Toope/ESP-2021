#ifndef BT_H_
#define BT_H_

#include <avr/io.h>

/* Bluetooth-module functions */

void USART_Init(long baud);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);
void USART_Flush(void);

#endif