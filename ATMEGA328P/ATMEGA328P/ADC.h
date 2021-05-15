/*
 * ADC.h
 *
 * Created: 10/16/2020 2:51:42 PM
 *  Author: khaled
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_CH(int channelNO);
void ADC_Ref(int Ref);
void ADC_Freq(int prescaler);
void ADC_init(int channelNO,int Ref,int Prescaler);
void ADC_StartConv();
int ADC_read();

#endif /* ADC_H_ */