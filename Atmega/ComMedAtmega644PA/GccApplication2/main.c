#define F_CPU 184320000UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>


// Definerer funktioner
void swrite(uint8_t byte);
uint8_t sread();
void InitPWM();
void InitADC();
void PWMStart();




//S�tter variabler
double dutyCycle = 1023;
char stopcommand[1];
int main(void)
{
	UBRR1 = F_CPU/(16*96000)-1;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);	// T�nder for reading og writing
    InitPWM();
	InitADC();
	DDRD = 0x00;
	PORTD = 0x00;

	while (1) {
		
		
		char ReceivedMessage[1];
		ReceivedMessage[0] = sread();		// Venter hele tiden p� signal fra pc medmindre anden operation i koden er igang
		
		if (ReceivedMessage[0] == '2')
		{
			dutyCycle = 1023;
			DDRD = (1 << PORTD4);
		}
		
		if (ReceivedMessage[0] == '3')
		{
			DDRD = (0 << PORTD4);
		}
		
		if (ReceivedMessage[0] == '6')
		{
			PWMStart();
		}
		if (ReceivedMessage[0] == '8')
		{
			swrite(ReceivedMessage[0]);
		}
		
		
		
	}
}

void swrite(uint8_t byte) {
	while (!( UCSR1A & (1<<UDRE1) ));				// Venter p� at der er intet i reiceveren s� der er frit til at sende
	UDR1 = byte;									// Outputter dataen ud p� porten
}

uint8_t sread(){
	while (!( UCSR1A & (1<<RXC1) ));				// Venter p� at alt data er l�st
	return UDR1;									// Returnere den data der er modtaget til en variabel
}


void InitPWM(){
		DDRD = (1 << PORTD4);									// �bner for at der kan komme str�m ud af porten til PWM
		
		
		TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);	// S�tter mode til PWM, Phase Correct, 10-bit m�ske slet WGM11 s� bliver det til 8bit
		TIMSK1 = (1 << TOIE1);
		
		sei();													// S�tter interupten til PWM
		
		TCCR1B = (1 << CS10);									// starter timeren
		
	
}


void InitADC(){

    /*
	ADMUX - ADC Multiplexer Selection Register
	
	bit          7           6          5         4        3         2          1          0
	name       REFS1       REFS0      ADLAR      MUX4     MUX3      MUX2       MUX1       MUX0
	set to       0           1          0         0        0         0          0          1
	
	REFS1 = 0    
	REFS0 = 1	use AVCC with external capacitor at AREF pin
	
	ADLAR = 1    left justify ADC result in ADCH/ADCL
	
	bit 4 = 0
	
	MUX3 = 0     
	MUX2 = 0
	MUX1 = 0
	MUX0 = 1	use PC1/ADC1 for input
	*/
	ADMUX = 0b01000001;
	
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
	
	ADPS2 = 1
	ADPS1 = 0    MHz clock / 8 
	ADPS0 = 1
	*/
	ADCSRA = 0b10100101;
	
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
	
	
}

void PWMStart(){
	DDRD = 0b00010000;
	PORTD = 0b00010000;
	PORTC = 0b00000000;				// Vender retningen p� str�mmen til motoren s� den k�rer bagl�ns
	dutyCycle = 1023;				// Full speed 16 bit
	_delay_ms(150);	
	int i = 0;
	while (!(ADC < 464)) {			// Laver en evigt loop der venter p� at str�mmen bliver for stor ogs� slutter den
		
		//swrite('0');
		//swrite(ADCH); //Outputter sp�ndingen den m�ler p� porten
		//swrite(ADCL); //Outputter sp�ndingen den m�ler p� porten

	}
	//swrite(ADCH); //Outputter sp�ndingen den m�ler p� porten
	//swrite(ADCL); //Outputter sp�ndingen den m�ler p� porten
	//dutyCycle = dutyCycle/2;			// half speed
	dutyCycle = 0;
	swrite('7');
	stopcommand[0] = sread(); // Venter p� at den f�r sendt signal af robot der siger den er hvor der skal slippes
	
	dutyCycle = 1023;
	PORTC = 0b00001000;				// Vender retningen p� str�mmen til motoren s� den k�rer bagl�ns
	DDRC = 0b00001000;
	_delay_ms(150);					// Find v�rdi her der passer med at den er �ben
	while (!(ADC > 564)) {			// Laver en evigt loop der venter p� at str�mmen bliver for stor ogs� slutter den
		

		//swrite(ADCH); //Outputter sp�ndingen den m�ler p� porten
		//swrite(ADCL); //Outputter sp�ndingen den m�ler p� porten

	}				// half speed
	//swrite(ADCH); //Outputter sp�ndingen den m�ler p� porten
	//swrite(ADCL); //Outputter sp�ndingen den m�ler p� porten
	DDRD = 0b00000000;
	PORTD = 0b00000000;
	PORTC = 0b00000000;				// Vender retningen til den anden vej igen og slukker motoren
	DDRC = 0b00000000;
	swrite('7');

	
}


ISR(TIMER1_OVF_vect){
	
	OCR1B = dutyCycle;				// Styrer hvor hurtigt den skal interupt alt efter hvor h�j dutycyle er

}
