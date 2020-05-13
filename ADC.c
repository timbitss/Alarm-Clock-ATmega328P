#include "ADC.h"

void ADCInit(void){

    ADMUX |= (1<<REFS0); //Voltage Reference Selection = AVCC with external capacitor at AREF pin
    ADCSRA |= ((1<<ADPS1) | (1<<ADPS0)); //prescaler of 8 
    ADCSRA |= ((1<<ADEN) | (1<<ADATE)); // enables the ADC and free running mode
}

void ADCSelectTemp(void){
    ADCSRA &= ~(1<<ADEN); //disable ADC
    ADMUX |= (1<<2); //measure temp on ADC4
    ADCSRA |= ((1<<ADEN) | (1<<ADSC)); //enable ADC and start conversions
    
}

