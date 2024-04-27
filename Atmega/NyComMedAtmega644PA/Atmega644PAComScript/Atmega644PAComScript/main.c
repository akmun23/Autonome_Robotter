#define F_CPU 18278281UL
/*
 * Atmega644PAComScript.c
 *
 * Created: 26-04-2024 16:39:04
 * Author : fluen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint16_t dutycycle = 0; // 10 bit value so max is 0x03ff
volatile unsigned char rxdata;
volatile uint16_t ADCData;
int ObjectGripped = 0;
int GripperOpen = 1;
int FirstFewLoop = 0;
int LastRead = 512;

void swrite(uint8_t byte);
void InitPWM();
void InitADC();
void CloseGripper();
void OpenGripper();

int main(void)
{
	UBRR1 = 119; // Sets the baudrate calculated by (F_CPU/(16*9600-1))
	UCSR1A = (1 << RXC1);  // Skal måske bare slettes da det bliver gjort gennem RXCIE1
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);	// Enables reading and writing and allows for read interupt flags
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);					// Sets frame as 8 bits
	
	sei();		// Enables global interupts
	InitPWM();	// Setup for PWM
	InitADC();	// Setup for ADC

	while (1){}
}


void swrite(uint8_t byte) {
	while (!( UCSR1A & (1<<UDRE1) ));		// Writing is set up in polling mode so here we wait the data bus to be ready for a msg			
	UDR1 = byte;							// Outputs the message
}


void InitPWM(){
	
	DDRD = (1 << PORTD4);									// Enables power for the PWM port	
	PORTD = (1 << PORTD4);									// Same
	TCCR1A = (1 << COM1B1)| (1 << WGM12)| (1 << WGM11) | (1 << WGM10);	// Sets up the timer for fast PWM 10-bit and non inverting mode
	TCCR1B = (1 << CS10);									// Sets prescaler to 1  ->  Måske ændre den her prescaler til en bedre en Måske 8
	TIMSK1 = (1 << TOIE1);									// Starts the timer
								


}



void InitADC(){
	
	ADMUX = (1 << REFS0) | (1 << MUX0);					// AVCC at AREF pin and ADC1 Chosen
	ADCSRA = (1 << ADEN) | (ADPS2);						// Aden enables ADC and then 32 division factor is set to reach between 200khz and 50khz
}


void CloseGripper(){
	PORTC = (0 << PORTC3);						// Makes sure the motor is going the correct way
	DDRC = (0 << PORTC3);
	dutycycle = 1023/2;							// Enables the motor at approximately 60% duty cycle 
	_delay_ms(300);								// Short delay before first reading since starting the motor requires more power than running
	int ObjectHit = 0;							// variable for checking when object is hit
	while (ObjectHit == 0) {					// Loop waiting for bool set true when object is hit
		ADCSRA |= (1 << ADSC);					// start ADC
		while ((ADCSRA & (1 << ADIF)) == 0){}	// Waits for a reading from the ADC to be done
		if(ADC <= 461){							// Compares the signal and checks if it is lower than picked value for power consumption when resistance if met
			ObjectHit = 1;						// Makes variable true telling the loop that a object has been grasped
		}
	}
	dutycycle = 0;								// Turn off motor
	swrite('7');								// Send signal to pc telling script that is has picked up a piece
	
}

void OpenGripper(){
	PORTC = (1 << PORTC3);						// Makes sure the motor is going the correct way
	DDRC = (1 << PORTC3);
	dutycycle = 1023/2;							// Enables the motor at max speed
	_delay_ms(300);								// Short delay before first reading since starting the motor requires more power than running
	int ObjectHit = 0;							// variable for checking when object is hit
	while (ObjectHit == 0) {					// Loop waiting for bool set true when object is hit
		ADCSRA |= (1 << ADSC);					// start ADC
		while ((ADCSRA & (1 << ADIF)) == 0){}	// Waits for a reading from the ADC to be done
		if(ADC >= 570){							// Compares the signal and checks if it is lower than picked value for power consumption when resistance if met
			ObjectHit = 1;						// Setting the variable to 1 telling the loop that the gripper is fully open
		}
	}
	dutycycle = 0;								// Turn off motor
	swrite('7');								// Send signal to pc telling script that is has picked up a piece
	
	
}


ISR(TIMER1_OVF_vect){
	
	OCR1B = dutycycle;		// Value for compare value for timer is set to dutycycle 
}

ISR(USART1_RX_vect){
	
	rxdata = UDR1;			// The received message is put into a variable to fix issue with reading directly from UDR1 causing it to show old message 
	if (rxdata == '6'){
		sei();
		CloseGripper();
	}
	
	else if (rxdata == '8'){
		sei();
		OpenGripper();
	}
	
}