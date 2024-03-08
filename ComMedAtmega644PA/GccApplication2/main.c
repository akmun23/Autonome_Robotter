#define F_CPU 184320000UL
//#define F_CPU 160000000UL
#define outp(a, b) b = a

#include <stdint.h>
//#define __AVR_ATmega644PA__
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void WriteMessage();
void PWM();

void swrite(uint8_t byte) {
	while (!( UCSR1A & (1<<UDRE1) ));
	UDR1 = byte;
}

uint8_t sread(){
	while (!( UCSR1A & (1<<RXC1) ));
	return UDR1;
}

int main(void)
{

	// UBRR1L = 103;
	UBRR1L = 119;                         // UBBR = Freq / (16 * (BaudRate)) – 1
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);  // Enable reading and writing

	while (1) {
		
		
		char ReceivedMessage[1];
		ReceivedMessage[0] = sread();
		
		if (ReceivedMessage[0] == 's')
		{
			swrite(ReceivedMessage[0]);

		}
		
		if (ReceivedMessage[0] == '0')
		{
			//Timer250us();
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '1')
		{
			
			DDRD = 0b00100000; 
			PORTD = 0b00100000;
			swrite('p');
			swrite(ReceivedMessage[0]);

		}
		if (ReceivedMessage[0] == '2')
		{
			DDRD = 0b00000000;
			PORTD = 0b00000000;
			swrite('p');
			swrite(ReceivedMessage[0]);
			
		}
		if (ReceivedMessage[0] == '3')
		{
			DDRD = 0b00100000;
			PORTD = 0b00100000;
			_delay_ms(1000);
			DDRD = 0b00000000;
			PORTD = 0b00000000;
			swrite(ReceivedMessage[0]);

		}
		if (ReceivedMessage[0] == '4')
		{
			PWM();
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '5')
		{
			//PWM(500,500);
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '6')
		{
			//PWM(200,200)
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '7')
		{
			//PWM(50,100)
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '8')
		{
			//PWM(100,50);
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '9')
		{
			_delay_ms(1000);
			swrite(ReceivedMessage[0]);
		}
		
		
	}
}

void WriteMessage(char* sendthis){
	
	for (int i = 0; i < strlen(sendthis); i++){
		swrite(sendthis[i]);
	}
}
/*
void PWM(){
	
	for (int i = 0; i < 25; i++)
	{
		DDRD = 0b00100000;
		PORTD = 0b00100000;
		_delay_ms(5);
		DDRD = 0b00000000;
		PORTD = 0b00000000;
		_delay_ms(5);

	}
}*/


 void PWM(){
	    DDRD |= (1 << DDD5);
	    // PB1 and PB2 is now an output
	    
	    ICR1 = 0xFFFF;
	    // set TOP to 16bit
	    
	    OCR1A = 0x3FFF;
	    // set PWM for 25% duty cycle @ 16bit
	    
	    
	    TCCR1A |= (1 << COM1A1);
	    // set none-inverting mode
	    
	    TCCR1A |= (1 << WGM11);
	    TCCR1B |= (1 << WGM12)|(1 << WGM13);
	    // set Fast PWM mode using ICR1 as TOP
	    
	    TCCR1B |= (1 << CS10);
	    // START the timer with no prescaler
	    
	    /*while (1);
	    {
		    // we have a working Fast PWM
	    }*/
		_delay_ms(1000);
		DDRD = 0b00000000;
		PORTD = 0b00000000;
}