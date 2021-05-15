/*
 * I_O_drives.c
 *
 * Created: 5/6/2021 8:44:44 PM
 *  Author: khaled
 */ 
#include "I_O_drives.h"
#include <avr/io.h>


void setPinB(int pinNumber)			//3 methods to set any output pin 
{
	PORTB |= (1<<pinNumber);
}
void setPinC(int pinNumber)
{
	PORTC |= (1<<pinNumber);
}
void setPinD(int pinNumber)
{
	PORTD |= (1<<pinNumber);
}





void resetPinB(int pinNumber)			//3 methods to reset any output pin
{
	PORTB &= ~(1<<pinNumber);
}
void resetPinC(int pinNumber)
{
	PORTC &= ~(1<<pinNumber);
}
void resetPinD(int pinNumber)
{
	PORTD &= ~(1<<pinNumber);
}





int isPressedB(int pinNumber){				//3 to check input signals
	if(PINB & (1<<pinNumber))return 1;
	else return 0;
}
int isPressedC(int pinNumber){
	if(PINC & (1<<pinNumber))return 1;
	else return 0;
}
int isPressedD(int pinNumber){
	if(PIND & (1<<pinNumber))return 1;
	else return 0;
}

