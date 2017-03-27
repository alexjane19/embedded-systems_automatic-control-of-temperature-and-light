/*
* LightAtmega8.c
*
* Created: 1/29/2017 4:56:27 PM
* Author : AlexJane
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
char paterns[16][16]={{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111},
{0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111}};
int pat_cur [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int i = 0;

unsigned char pat1;
unsigned char pat2;
int numpat;
int numBlock;
char flag = 0xff;


int convertBinToDec(unsigned char nBlock){
	if(0b00000000 == nBlock){
		return 0;
		}else if(0b00000001 == nBlock){
		return 1;
		}else if(0b00000010 == nBlock){
		return 2;
		}else if(0b00000011 == nBlock){
		return 3;
		}else if(0b00000100 == nBlock){
		return 4;
		}else if(0b00000101 == nBlock){
		return 5;
		}else if(0b00000110 == nBlock){
		return 6;
		}else if(0b00000111 == nBlock){
		return 7;
		}else if(0b00001000 == nBlock){
		return 8;
		}else if(0b00001001 == nBlock){
		return 9;
		}else if(0b00001010 == nBlock){
		return 10;
		}else if(0b00001011 == nBlock){
		return 11;
		}else if(0b00001100 == nBlock){
		return 12;
		}else if(0b00001101 == nBlock){
		return 13;
		}else if(0b00001110 == nBlock){
		return 14;
		}else if(0b00001111 == nBlock){
		return 15;
	}
}


ISR(USART_RXC_vect){
	unsigned char pack = UDR;
	if ((pack & 0b10000000) && flag)
	{ 
		numBlock = convertBinToDec(((pack>>3) & 0b00001111));
		numpat = convertBinToDec((pack & 0b00000111));
		pat_cur[numBlock] = numpat;
		pat1 = paterns[numBlock][numpat*2];
		pat2 = paterns[numBlock][numpat*2 + 1];
		PORTB = pat1;
		PORTC = pat2;
		PORTD = pat2;
		PORTD = PORTD | 0x3E;
		eeprom_update_block (( const void *) pat_cur , ( void *)256 , 16);

		

 	}else
	{
		if (flag)
		{
			flag = 0x00;
			numBlock = convertBinToDec(((pack>>3) & 0b00001111));
			numpat = convertBinToDec((pack & 0b00000111));
		}
		if (i == 1)
		{
			pat1 = pack;
				
		}else if(i == 2){
			pat2 = pack;
			paterns[numBlock][numpat*2] = pat1;
			paterns[numBlock][numpat*2 + 1] = pat2;
			flag = 0xFF;
		}
		i++;
		if(i==3){
			i=0;
		}
	}
}



int main(void)
{
	DDRB = 0xFF;
	DDRC = 0XFF;
	DDRD = 0x00;
	DDRD = DDRD | (1<<7);
	DDRD = DDRD | (1<<6);
	PORTD= PORTD | 0x3E;
	for (int v=0; v<16; v++)
	{
		eeprom_update_block (( const void *) paterns[v] , ( void *) (16*v), 16);
	}
	for (int z=0; z<16; z++)
	{
		eeprom_read_block (( void *) paterns[z] , ( const void *) (16*z), 16) ;
	}
	eeprom_update_block (( const void *) pat_cur , ( void *)256 , 16);
	eeprom_read_block (( void *) pat_cur , ( const void *)256 , 16) ;
	UCSRB= (1<< RXEN)|(1<<RXCIE);
	UCSRC= (1<< UCSZ1)|(1<< UCSZ0)|(1<< URSEL);
	UBRRL= 0x33;
	sei();
	
	/* Replace with your application code */
	while (1)
	{
		unsigned char click = ~PIND;
		int num = convertBinToDec((click>>2) & 0x0F);
		int npat = pat_cur[num];
		unsigned char pa1 = paterns[num][npat*2];
		unsigned char pa2 = paterns[num][npat*2 + 1];
		PORTB = pa1;
		PORTC = pa2;
		PORTD = pa2;
		PORTD = PORTD | 0x3E;
		int e=0;
		while((~PIND) & 0b00000010){
				unsigned char click = ~PIND;
				num = convertBinToDec((click>>2) & 0x0F);
				pa1 = paterns[num][e*2];
				pa2 = paterns[num][e*2 + 1];
				PORTB = pa1;
				PORTC = pa2;
				PORTD = pa2;
				PORTD = PORTD | 0x3E;
				e++;
				if(e == 8)
					e=0;
				_delay_ms(100);
				
		}
		
		
	}
}

