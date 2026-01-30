/*
 * servo.h
 *
 * Created: 19-01-2026 12:39:41
 *  Author: NIVYA
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

void Servo_init(void);
void Servo_write(uint8_t angle);

#endif /* SERVO_H_ */