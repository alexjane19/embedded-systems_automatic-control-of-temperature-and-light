/*
* TempatureATmega8.c
*
* Created: 1/28/2017 11:59:44 PM
* Author : AlexJane
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RS 5
#define RW 6
#define E 7

char t[5];
int i=0;
unsigned char flag = 0x00;
ISR(USART_UDRE_vect){
	
	if (i<5 && flag)
	{
		UDR = t[i++];
		//_delay_ms(500);
			
	}else if(i == 5){
		flag = 0x00;
		i=0;
		ADCSRA |= (1<<ADSC);
		while((ADCSRA&(1<<ADIF)) == 0);
		SendCommand(0x38);  //initialization
		SendCommand(0x0e);
		SendCommand(0x01);  //clear LCD
		unsigned char _adcl = ADCL;
		unsigned char _adch = ADCH;
		dispalyTempatuareLcd(_adcl);
		_delay_ms(1000);
		
			
	}
}


void SendCommand(char cmd){
	PORTD&=~(1<<RS);
	PORTD&=~(1<<RW);
	PORTB=cmd;
	PORTD|=1<<E;
	PORTD&=~(1<<E);
	_delay_ms(2);
}
void SendData(char Data){
	PORTD|=(1<<RS);
	PORTD&=~(1<<RW);
	PORTB=Data;
	PORTD|=1<<E;
	PORTD&=~(1<<E);
	_delay_ms(2);
}

void initTempature(void){
	DDRC = 0;
	ADCSRA = 0x87;
	ADMUX=0xc0; //right justify ; 2.25 v
}

void dispalyTempatuareLcd(unsigned char data)
{
	double d= data;
	d/=4;
	t[0] = ((int)d/10)+0x30;
	t[1] = ((int)d % 10)+0x30;
	t[2] = '.';
	t[3] = ((int)(d*10) % 10)+0x30;
	t[4] = ((int)(d* 100) % 10)+0x30;
	for(int a=0;a<5;a++)
		SendData(t[a]);

	flag = 0xFF;
	char c [] = "'C";
	SendData(c[0]);
	SendData(c[1]);	

}



main(){
	unsigned char i;
	char msg[]="This is a test_123456789";
	
	DDRB=0xff;
	DDRD=0xf0;
	initTempature();
	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF)) == 0);
	SendCommand(0x38);  //initialization
	SendCommand(0x0e);
	SendCommand(0x01);  //clear LCD
	unsigned char _adcl = ADCL;
	unsigned char _adch = ADCH;
	dispalyTempatuareLcd(_adcl);
	_delay_ms(1000);
	
	UCSRB = (1<<TXEN) | (1<<UDRIE);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRH = 0x00;
	UBRRL = 0x33;
	sei();

	while(1);
	
	
}
