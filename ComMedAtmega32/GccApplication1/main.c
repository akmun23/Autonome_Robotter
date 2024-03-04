#define F_CPU 8000000UL

#include <stdint.h>
#define __AVR_ATmega32A__
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>



#define led_off0() PORTB |= (1 << 0)
#define led_on0() PORTB &= ~(1 << 0)
#define led_off1() PORTB |= (1 << 1)
#define led_on1() PORTB &= ~(1 << 1)
#define led_off2() PORTB |= (1 << 2)
#define led_on2() PORTB &= ~(1 << 2)
#define led_off3() PORTB |= (1 << 3)
#define led_on3() PORTB &= ~(1 << 3)
#define led_off4() PORTB |= (1 << 4)
#define led_on4() PORTB &= ~(1 << 4)
#define led_off5() PORTB |= (1 << 5)
#define led_on5() PORTB &= ~(1 << 5)
#define led_off6() PORTB |= (1 << 6)
#define led_on6() PORTB &= ~(1 << 6)
#define led_off7() PORTB |= (1 << 7)
#define led_on7() PORTB &= ~(1 << 7)


void Blank();
void Number0();
void Number1();
void Number2();
void Number3();
void Number4();
void Number5();
void Number6();
void Number7();
void Number8();
void Number9();
void WriteMessage();








void swrite(uint8_t byte) {
	while (!( UCSRA & (1<<UDRE) ));
	UDR = byte;
}

uint8_t sread(){
	while (!( UCSRA & (1<<RXC) ));
	return UDR;
}

int main(void)
{
	UBRRL = 51;                         // UBBR = Freq / (16 * (BaudRate)) – 1
	UCSRB = (1 << RXEN) | (1 << TXEN);  // Enable reading and writing

	DDRB = 0xFF;
	led_off0();
	led_off1();
	led_off2();
	led_off3();
	led_off4();
	led_off5();
	led_off6();
	led_off7();
	char Besked[40] = "Aksel er Stalin";

	while (1) {
		
		
		char ReceivedMessage[1];
		ReceivedMessage[0] = sread();
		
		if (ReceivedMessage[0] == 's')
		{
			Blank();
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		
		if (ReceivedMessage[0] == '0')
		{
			Blank();
			Number0();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '1')
		{
			Blank();
			Number1();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		if (ReceivedMessage[0] == '2')
		{
			Blank();
			Number2();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
			
		}
		if (ReceivedMessage[0] == '3')
		{
			Blank();
			Number3();
			_delay_ms(1000);
			swrite('p');
			WriteMessage(Besked);
			WriteMessage(' ');
			swrite(ReceivedMessage[0]);
			swrite('\n');

		}
		if (ReceivedMessage[0] == '4')
		{
			Blank();
			Number4();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '5')
		{
			Blank();
			Number5();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '6')
		{
			Blank();
			Number6();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '7')
		{
			Blank();
			Number7();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '8')
		{
			Blank();
			Number8();
			_delay_ms(1000);
			swrite('p');
			swrite(ReceivedMessage[0]);
			swrite('\n');
		}
		if (ReceivedMessage[0] == '9')
		{
			Blank();
			Number9();
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

void Blank(){
	
	led_off0();
	led_off1();
	led_off2();
	led_off3();
	led_off4();
	led_off5();
	led_off6();
	led_off7();
	
}
void Number0(){
	led_on0();
	led_on1();
	led_on2();
	led_on3();
	led_on4();
	led_on6();
	
	
}
void Number1(){

	led_on2();
	led_on3();
	
	
}

void Number2(){
	led_on0();
	led_on1();
	led_on3();
	led_on5();
	led_on6();
	
	
}
void Number3(){
	led_on1();
	led_on2();
	led_on3();
	led_on5();
	led_on6();
	
	
}
void Number4(){
	led_on2();
	led_on3();
	led_on4();
	led_on5();
	
	
}
void Number5(){
	led_on1();
	led_on2();
	led_on4();
	led_on5();
	led_on6();
	
	
}
void Number6(){
	led_on0();
	led_on1();
	led_on2();
	led_on4();
	led_on5();
	led_on6();
	led_on7();
	
	
}
void Number7(){
	led_on2();
	led_on3();
	led_on6();
	
	
}
void Number8(){
	led_on0();
	led_on1();
	led_on2();
	led_on3();
	led_on4();
	led_on5();
	led_on6();
	
	
}
void Number9(){
	led_on1();
	led_on2();
	led_on3();
	led_on4();
	led_on5();
	led_on6();
	led_on7();
	
	
}