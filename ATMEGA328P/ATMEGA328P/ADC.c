/*
 * ADC.c
 *
 * Created: 10/16/2020 1:57:19 PM
 *  Author: khaled
 */ 

#include <avr/io.h>
#include "ADC.h"
#include <math.h>


void ADC_CH(int channelNO){					//method to choose which channel the sensor is connected to
	if (channelNO<8){						//check if valid channel number
	ADMUX = (ADMUX & 0xe0)|channelNO;		//adjust value in ADMUX register to specific channel
	DDRC &= ~(1<<channelNO);				//make pin as input
	}
}


void ADC_Ref(int Ref){						//choose the reference voltage(internal,external)
	ADMUX = (ADMUX & 0x3f)|(Ref<<6);
}


void ADC_Freq(int prescaler){				//choose the pre-scaling wanted for calculation
	ADCSRA = (ADCSRA&0x07) |(prescaler);
	
}

void ADC_init(int channelNO,int Ref,int Prescaler){				//method that calls all 3 methods and gives them the values required
	ADC_CH(channelNO);
	ADC_Ref(Ref);
	ADC_Freq(Prescaler);
	ADCSRA |= (1<<ADEN);
}

void ADC_StartConv(){							//tells the ADC part in controller to read the signal coming from sensor 
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));				//wait until done reading
}

int ADC_read(){									//get the value of reading from stored in register and returns it to be used
	int val = ADCL;
	val |= (ADCH<<8);	
	return round(val*0.4887585532746823);		//eqution using ref volt=5 => (5/1023) then *100 so the output is 0.488758
}