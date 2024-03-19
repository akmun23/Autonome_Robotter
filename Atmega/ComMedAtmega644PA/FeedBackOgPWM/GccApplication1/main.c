// ADC_FreeRunning.c


#ifndef F_CPU					
#define F_CPU 184320000UL
#endif

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>


double dutyCycle = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	
	DDRD = (1 << PORTD4);
	
	
	TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);
	TIMSK1 = (1 << TOIE1);
			
	sei();
	
	TCCR1B = (1 << CS10); // starter timeren
	
    /*
	ADMUX - ADC Multiplexer Selection Register
	
	bit          7           6          5         4        3         2          1          0
	name       REFS1       REFS0      ADLAR       -       MUX3      MUX2       MUX1       MUX0
	set to       0           1          1         0        0         0          0          1
	
	REFS1 = 0    use AVCC for reference voltage
	REFS0 = 1
	
	ADLAR = 1    left justify ADC result in ADCH/ADCL
	
	bit 4 = 0
	
	MUX3 = 0     use PC1/ADC for input
	MUX2 = 0
	MUX1 = 0
	MUX0 = 1
	*/
	ADMUX = 0b01100001;
	
	/*
	ADCSRA - ADC Control and Status Register A
	
	bit          7           6            5          4          3            2           1           0
	name        ADEN        ADSC        ADATE       ADIF       ADIE        ADPS2       ADPS1       ADPS0
	set to       1           0            1          0          0            0           1           1
	
	ADEN = 1     enable ADC
	ADSC = 0     don't start ADC yet
	ADATE = 1    enable ADC auto trigger (i.e. use free running mode)
	ADIF = 0     don't set ADC interrupt flag
	ADIE = 0     don't set ADC interrupt enable
	
	ADPS2 = 0
	ADPS1 = 1    MHz clock / 8 
	ADPS0 = 1
	*/
	ADCSRA = 0b10100011;
	
	/*
	ADCSRB - ADC Control and Status Register B
	
	bit         7           6           5           4           3         2           1           0
	name        -          ACME         -           -           -       ADTS2       ADTS1       ADTS0
	set to      0           0           0           0           0         0           0           0
	
	bit 7 = 0
	ACME = 0     don't enable analog comparator multiplexer
	bit 5 = 0
	bit 4 = 0
	bit 3 = 0
	ADTS2 = 0
	ADTS1 = 0    free running mode
	ADTS0 = 0
	*/
	ADCSRB = 0b00000000;
	
	ADCSRA |= (1 << ADSC);		// start ADC
	
	while (1) {	
		
		//dutyCycle = 65535;
		dutyCycle = 0;
		_delay_ms(100);
		if (ADCH < 125)
		{
			
			dutyCycle = 0;
			_delay_ms(100);
		}
									
	}
	return(0);					
}


ISR(TIMER1_OVF_vect){
	
	//OCR1A = (dutyCycle/100)*255;
	OCR1B = dutyCycle;

}