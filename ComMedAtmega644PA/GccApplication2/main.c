#define F_CPU 184320000UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>


// Definerer funktioner
void WriteMessage();
void swrite(uint8_t byte);
uint8_t sread();
void InitPWMandADC();
void PWMStart();


/*
Test PWM signaler der kører på konstant værdi
void PWM100();
void PWM75();
void PWM50();
void PWM25();*/


//Sætter variabler
double dutyCycle = 0;
char stopcommand[1];
int main(void)
{

	UBRR1L = 119;							// UBBR = Freq / (16 * (BaudRate)) – 1
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);	// Tænder for reading og writing

	while (1) {
		
		
		char ReceivedMessage[1];
		ReceivedMessage[0] = sread();		// Venter hele tiden på signal fra pc medmindre anden operation i koden er igang
		
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
			swrite(ReceivedMessage[0]);

		}
		if (ReceivedMessage[0] == '2')
		{
			DDRD = 0b00000000;
			PORTD = 0b00000000;
			swrite(ReceivedMessage[0]);
			
		}
		if (ReceivedMessage[0] == '3')
		{
			//PWM100();
			DDRD = 0b00010000;
			PORTD = 0b00010000;
			swrite(ReceivedMessage[0]);

		}
		if (ReceivedMessage[0] == '4')
		{
			//PWM75();
			DDRD = 0b00000000;
			PORTD = 0b00000000;
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '5')
		{
			//PWM50();
			swrite(ReceivedMessage[0]);
		}
		if (ReceivedMessage[0] == '6')
		{
			//PWM25();
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

void swrite(uint8_t byte) {
	while (!( UCSR1A & (1<<UDRE1) ));				// Venter på at der er intet i reiceveren så der er frit til at sende
	UDR1 = byte;									// Outputter dataen ud på porten
}

uint8_t sread(){
	while (!( UCSR1A & (1<<RXC1) ));				// Venter på at alt data er læst
	return UDR1;									// Returnere den data der er modtaget til en variabel
}


void WriteMessage(char* sendthis){
	
	for (int i = 0; i < strlen(sendthis); i++){		// Tager en større mængde tal/bogstaver og sender dem 1 af gangen 
		swrite(sendthis[i]);						// Benytter write komandoen
	}
}





void InitPWMandADC(){
	DDRD = (1 << PORTD4);									// Åbner for at der kan komme strøm ud af porten til PWM 
	
	
	TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);	// Sætter mode til PWM, Phase Correct, 10-bit måske slet WGM11 så bliver det til 8bit
	TIMSK1 = (1 << TOIE1);
			
	sei();													// Sætter interupten til PWM
	
	TCCR1B = (1 << CS10);									// starter timeren
	
    /*
	ADMUX - ADC Multiplexer Selection Register
	
	bit          7           6          5         4        3         2          1          0
	name       REFS1       REFS0      ADLAR       -       MUX3      MUX2       MUX1       MUX0
	set to       0           1          1         0        0         0          0          1
	
	REFS1 = 0    use AVCC for reference voltage
	REFS0 = 1
	
	ADLAR = 1    left justify ADC result in ADCH/ADCL
	
	bit 4 = 0
	
	MUX3 = 0     use PC1/ADC1 for input
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
	
	
}

void PWMStart(){
	dutyCycle = 65535;				// Full speed 16 bit
	_delay_ms(100);
	while (ADCH < 125) {			// Laver en evigt loop der venter på at strømmen bliver for stor også slutter den
	}
	dutyCycle = 65535/2;			// half speed
	
	while (stopcommand[0] != 8){
		stopcommand[0] = sread();	// Venter på at den får sendt signal af robot der siger den er hvor der skal slippes
	}
	PORTC = 0b00001000;				// Vender retningen på strømmen til motoren så den kører baglæns
	DDRC = 0b00001000;
	_delay_ms(300);					// Find værdi her der passer med at den er åben
	dutyCycle = 0;					// half speed
	PORTC = 0b00000000;				// Vender retningen til den anden vej igen og slukker motoren
	DDRC = 0b00000000;
	
}


ISR(TIMER1_OVF_vect){
	
	OCR1B = dutyCycle;				// Styrer hvor hurtigt den skal interupt alt efter hvor høj dutycyle er

}

























































/*

void setupADC(){
	
	ADMUX = (1 << REFS0) ;
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	DIDR0 = (1 << ADC5D);
	void startConversion(){

}

void startConversion(){
	
	ADCSRA |= (1 << ADSC);
	
}



*/

/*void PWM100(){
	DDRD |= (1 << DDD5);
	// PD5 is now an output
	
	ICR1 = 0xFFFF;
	// set TOP to 16bit
	
	OCR1A = 0xBFFF;
	// set PWM for 25% duty cycle @ 16bit
	
	
	TCCR1A |= (1 << COM1A1);
	// set none-inverting mode
	
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	
	TCCR1B |= (1 << CS10);
	// START the timer with no prescaler


}




 void PWM75(){
	    DDRD |= (1 << DDD5);
	    // PD5 is now an output
	    
	    ICR1 = 0xFFFF;
	    // set TOP to 16bit
	    
	    OCR1A = 0xBFFF;
	    // set PWM for 25% duty cycle @ 16bit
	    
	    
	    TCCR1A |= (1 << COM1A1);
	    // set none-inverting mode
	    
	    TCCR1A |= (1 << WGM11);
	    TCCR1B |= (1 << WGM12)|(1 << WGM13);
	    // set Fast PWM mode using ICR1 as TOP
	    
	    TCCR1B |= (1 << CS10);
	    // START the timer with no prescaler


}

void PWM50(){
	DDRD |= (1 << DDD5);
	// PD5 is now an output
	
	ICR1 = 0xFFFF;
	// set TOP to 16bit
	
	OCR1A = 0x7FFF;
	// set PWM for 25% duty cycle @ 16bit
	
	
	TCCR1A |= (1 << COM1A1);
	// set none-inverting mode
	
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	
	TCCR1B |= (1 << CS10);
	// START the timer with no prescaler


}

void PWM25(){
	DDRD |= (1 << DDD5);
	// PD5 is now an output
	
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


}*/ 