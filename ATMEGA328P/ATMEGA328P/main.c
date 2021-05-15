/*
 * ATMEGA328P.c
 *
 * Created: 5/6/2021 8:43:19 PM
 * Author : khaled
 */ 
#define F_CPU 8000000UL		// Set system frequency
#include <avr/io.h>

#include "I_O_drives.h"		//input manually defined library that contain input output functions(as set reset output pins)
#include "LCD_4.h"			//library defined for LCD commands
#include "ADC.h"			//library defined for ADC commands used to read sensor


void update_temp(int temp);		//method used to update LCD view
void update_RPM(int rpm);		//method used to update LCD view

int main(void)
{	
	DDRC=0x02;							//define port C (pin 1 out rest in)
	LCD_init();							//initialize LCD
	ADC_init(0,1,7);					//initialize ADC on port ADC0 with ref volt(out source) and pre-scaling of 128 to get more accurate reading
	
	ADC_StartConv();					//tell ADC to convert signal coming from sensor
	int temp=ADC_read();				//get ADC readings
	int RPM=765;						//RPM at start
	
	LCD_Write_Str("Temp:");				//Write temp: on the LCD in first line
	LCD_cmd(0xc0);						//Go to second line
	LCD_Write_Str("RPM: ");				//Write RPM: on the LCD in second line
	
	update_temp(temp);				//Update LCD with the temp value
	update_RPM(RPM);				//Update LCD with the RPM value
	
	int new_temp;						//If temp changes it will be saved here
	int new_RPM=765;					//If RPM changes it will be saved here
	
	TCCR1A = (1<<WGM10) | (1<<COM1A1);	// Use timer 0 in the PWM mode 
	TCCR1B |=(1<<CS10);					//zero pre-scaling
	OCR1A=150;							//initial PWM for fan speed
    
    while (1) 
    {
		ADC_StartConv();		
		new_temp=ADC_read();		//Read current temp.
		
		if((isPressedB(0))&&(RPM<1300)){					//when pressing the first button the rpm increase by 100
			new_RPM += 76;									//Added value in RPM unit (values between 0-1300)
			OCR1A += 15;									//Added value in PWM (PWM=(RPM*1300)/255) (values between 0-255)
			}		
		if((isPressedB(2))&&(RPM>0)){						//when pressing the first button the rpm decrease by 100
			new_RPM -= 76;
			OCR1A -= 15;
			}			
		
		if(new_temp!=temp){				//if temp value changed this method updates the LCD with new values
			update_temp(new_temp);
			temp=new_temp;
		}
		if(new_RPM!=RPM){				//if RPM value changed this method updates the LCD with new values
			update_RPM(new_RPM);
			RPM=new_RPM;
		}
		
    }
}



void update_temp(int temp){				//This method erases old temp value on LCD and writes new one
	LCD_Home();
	for(int i=0;i<5;i++)LCD_cmd(0x14);
	LCD_num(temp);
	LCD_Write_Str("  ");
}

void update_RPM(int RPM){			//This method erases old RPM value on LCD and writes new one
	LCD_cmd(0xc0);
	for(int i=0;i<5;i++)LCD_cmd(0x14);
	LCD_num(RPM);
	LCD_Write_Str("   ");
}