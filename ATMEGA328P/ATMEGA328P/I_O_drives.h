/*
 * I_O_drives.h
 *
 * Created: 5/6/2021 8:46:44 PM
 *  Author: khaled
 */ 


#ifndef I_O_DRIVES_H_
#define I_O_DRIVES_H_



void setPinB(int pinNumber);
void setPinC(int pinNumber);
void setPinD(int pinNumber);



void resetPinB(int pinNumber);
void resetPinC(int pinNumber);
void resetPinD(int pinNumber);


int isPressedB(int pinNumber);
int isPressedC(int pinNumber);
int isPressedD(int pinNumber);



#endif /* I_O_DRIVES_H_ */