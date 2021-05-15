/*
 * LCD_4.c
 *
 * Created: 10/14/2020 6:45:53 PM
 *  Author: khaled
 */ 

#include "LCD_4.h"
#include "I_O_drives.h"
#include "ADC.h"
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTD			//ports used by LCD (wrote here to make it easy and fast to change at any time)
#define ctrl PORTD

#define LCD_Data_Pins DDRD
#define LCD_ctrl_Pins DDRD

#define RS 1					//commands pins used by LCD
#define Rw 2
#define en 3

void LCD_cmd(char comm){							//method used to enter LCD command 
	ctrl &= ~(1<<RS);								//rest ctrl pin
	LCD_DATA = (LCD_DATA & 0x0F) | (comm & 0xF0);	//send first part of data as I am working 4-bit mode
	ctrl |= 1<<en;									//set en pin
	_delay_ms(50);									//wait 50ms
	ctrl &= ~(1<<en);								//reset en pin
	_delay_ms(50);
	LCD_DATA = (LCD_DATA & 0x0F) | (comm << 4);		//send rest of data
	ctrl |= 1<<en;
	_delay_ms(50);
	ctrl &= ~(1<<en);
}

void LCD_Home(){									//return the courser to heme position in LCD 
	LCD_cmd(0x02);
}

void LCD_init(){						//method that starts the LCD
	LCD_Data_Pins=0xff;					//make the port pins LCD on output
	DDRB |= 1<<en;						//set the 3 pins en,RS & RW
	DDRB |= 1<<RS;
	DDRB |= 1<<Rw;
	ctrl &= ~(1<<Rw);					//reset Rw
	LCD_cmd(0x02);						//Return home
	_delay_ms(100);
	LCD_cmd(0x28);						//4-bit mode
	_delay_ms(100);
	LCD_cmd(0x01);						//Clear
	_delay_ms(100);
	_delay_ms(100);
	LCD_cmd(0x06);						//increment auto
	_delay_ms(100);
	LCD_cmd(0x0C);						//Display on, cursor off
	_delay_ms(100);
	LCD_cmd(0x80);						//Force cursor to beginning ( 1st line)
}

void LCD_Write(char data){							//method to write a char on the LCD
	ctrl |= 1<<RS;									//set RS pin
	LCD_DATA = (LCD_DATA & 0x0F) | (data & 0xF0);	//send first part of data
	ctrl |= 1<<en;
	_delay_ms(50);
	ctrl &= ~(1<<en);
	_delay_ms(50);
	LCD_DATA = (LCD_DATA & 0x0F) | (data << 4);		//send rest of data
	ctrl |= 1<<en;
	_delay_ms(50);
	ctrl &= ~(1<<en);
	
}
void LCD_Write_Str(char* data){						//method to write string on LCD(uses char method and while loop)
	while (*data != '\0'){
		LCD_Write(*data);
		data++;
	}
}

void LCD_num(int data){								//method to write integers on LCD
	char temp[8];									//create empty string
	itoa(data,temp,10);								//cast integer to string then use string method
	LCD_Write_Str(temp);
}

void LCD_Clear(){									//Clear the LCD
	LCD_cmd(0x01);
}

