#define F_CPU 8000000UL

#include <stdint.h>
#define __AVR_ATmega644PA__
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void WriteMessage();


void swrite(uint8_t byte) {
	while (!( UCSR0A & (1<<UDRE0) ));
	UDR0 = byte;
}

uint8_t sread(){
	while (!( UCSR0A & (1<<RXC0) ));
	return UDR0;
}

int main(void)
{

	UBRR0L = 51;                         // UBBR = Freq / (16 * (BaudRate)) – 1
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable reading and writing

	char Besked[40] = "Aksel is Stalin";

	while (1) {
		
		
		char ReceivedMessage[1];
		ReceivedMessage[0] = sread();
		
		if (ReceivedMessage[0] == 's')
		{
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		
		if (ReceivedMessage[0] == '0')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '1')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		if (ReceivedMessage[0] == '2')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
			
		}
		if (ReceivedMessage[0] == '3')
		{
			_delay_ms(1000);
			swrite('p');
			WriteMessage(Besked);
			WriteMessage(' ');
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		if (ReceivedMessage[0] == '4')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '5')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '6')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '7')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '8')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '9')
		{
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		
		
	}
}

void WriteMessage(char* sendthis){
	
	for (int i = 0; i < strlen(sendthis); i++){
		swrite(sendthis[i]);
	}
}