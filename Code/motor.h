#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h> 
#include <inttypes.h>

void setup_motors();
void update_motor(int motor_state, int motor_no);
unsigned char ReadEncoderDirection(int motor_no);
void MoveDirection(int cmd);

#endif