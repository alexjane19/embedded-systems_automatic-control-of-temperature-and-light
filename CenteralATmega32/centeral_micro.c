/*
* CenteralAtmega32.c
*
* Created: 1/29/2017 4:56:27 PM
* Author : AlexJane
*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "Include/graph.h"
#include "Include/glcd.h"
#include "Include/seq2.h"
char t[]="00.00'C";
int selNumMicro = 0;
int pageScreen = 0;
int selNumpatterm = 0;
int i =0;

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

ISR(USART_RXC_vect){
		t[i++] = UDR;
		if (i == 5)
		{
			if(pageScreen == 0)
				glcd_puts(t,8,3,0,2,0);
			i=0;
		}
	
}
unsigned char convertdectobin(int nBlock){
	if(0 == nBlock){
		return 0b00000000;
		}else if(1 == nBlock){
		return 0b00000001;
		}else if(2 == nBlock){
		return 0b00000010;
		}else if(3 == nBlock){
		return 0b00000011;
		}else if(4 == nBlock){
		return 0b00000100;
		}else if(5 == nBlock){
		return 0b00000101;
		}else if(6 == nBlock){
		return 0b00000110;
		}else if(7 == nBlock){
		return 0b00000111;
		}else if(8 == nBlock){
		return 0b00001000;
		}else if(9 == nBlock){
		return 0b00001001;
		}else if( 10 == nBlock){
		return 0b00001010;
		}else if(11 == nBlock){
		return 0b00001011;
		}else if(12 == nBlock){
		return 0b00001100;
		}else if(13 == nBlock){
		return 0b00001101;
		}else if(14 == nBlock){
		return 0b00001110;
		}else if(15 == nBlock){
		return 0b00001111;
	}
}
void createPattern(unsigned char key)
{//pattern[1]
	if (key == 0b11101110)
	{ paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00000001;
		//7  --- xor , bit0
}else if (key == 0b11011110)
{//8 --- bit1
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00000010;
}else if (key == 0b10111110)
{//9
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00000100;
}else if (key == 0b01111110)
{///
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00001000;
}else if (key == 0b11101101)
{//4
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00010000;
}else if (key == 0b11011101)
{//5
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b00100000;
}else if (key == 0b10111101)
{//6
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b01000000;
}else if (key == 0b01111101)
{//*
	paterns[selNumMicro][selNumpatterm*2 + 1] ^= 0b10000000;
}
//pattern[0]
else if (key == 0b11101011)
{//1  - xor , bit0
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00000001;
}else if (key == 0b11011011)
{//2
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00000010;
}else if (key == 0b10111011)
{//3
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00000100;
}else if (key == 0b01111011)
{//-
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00001000;
}
else if (key == 0b11100111)
{//onc
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00010000;
}else if (key == 0b11010111)
{//0
	paterns[selNumMicro][selNumpatterm*2] ^= 0b00100000;
}else if (key == 0b10110111)
{//=
	paterns[selNumMicro][selNumpatterm*2] ^= 0b01000000;
}else if (key == 0b01110111)
{//+
	paterns[selNumMicro][selNumpatterm*2] ^= 0b10000000;
}
}
void keyboard(char name []){
	unsigned char running = 0xff;
	while (running)
	{	
		glcd_clear();
		_delay_ms(5);
		glcd_puts(name,8,4,0,1,0);
		glcd_puts("Up(Save & Back)",8,0,0,1,0);
		drawPattern();
		unsigned char pushKey = (PIND>>2);
		pushKey &=0x1F;
		unsigned char rowKey = 0xff;
		unsigned char keyPressed;
		
		while (rowKey == 0xff)
		{
			DDRB = 0xf0;
			PORTB = 0x0f;
			rowKey = PINB;
			rowKey |=0xf0;
			pushKey = (PIND>>2);
			pushKey &=0x1F;
			if (pushKey == 0b00011101)
			{//up
				running = 0x00;
				unsigned char packetSel = 0b00000000;
				packetSel |=(convertdectobin(selNumMicro)<<3);
				packetSel |=convertdectobin(selNumpatterm);
				for(int c=0; c<3; c++){
				while(!(UCSRA & (1<<UDRE)));
				UDR = packetSel;
				if(c==0)
					packetSel = paterns[selNumMicro][selNumpatterm*2];
				if(c==1)
					packetSel = paterns[selNumMicro][selNumpatterm*2+1];
				}
				for (int v=0; v<16; v++)
				{
					eeprom_update_block (( const void *) paterns[v] , ( void *) (16*v), 16);
				}
				break;
			}
		}
		
		keyPressed = rowKey;
		DDRB = 0x00;
		PORTB = 0x00;

		DDRB = 0x0f;
		PORTB = 0xf0;
		rowKey = PINB;
		rowKey |= 0x0f;
		keyPressed &=rowKey;
		if(running)
			createPattern(keyPressed);				
	}
	
	//while(){
		//
	//}
}
int turnOnOff(int i, unsigned char pat){
	if (i == 0)
	{
		if (paterns[selNumMicro][selNumpatterm*2] & pat)
		{
			return 0;
		}
		return 1;
	}else{
		if ((paterns[selNumMicro][selNumpatterm*2 + 1] & pat))
		{
			return 0;
		}
		return 1;
	}
}
void drawPattern(void){
			circle(50,20,3,turnOnOff(1,0b00000001),1);
			circle(50,30,3,turnOnOff(1,0b00010000),1);
			circle(50,40,3,turnOnOff(0,0b00000001),1);
			circle(50,50,3,turnOnOff(0,0b00010000),1);
			
			circle(60,20,3,turnOnOff(1,0b00000010),1);
			circle(60,30,3,turnOnOff(1,0b00100000),1);
			circle(60,40,3,turnOnOff(0,0b00000010),1);
			circle(60,50,3,turnOnOff(0,0b00100000),1);
			
			circle(70,20,3,turnOnOff(1,0b00000100),1);
			circle(70,30,3,turnOnOff(1,0b01000000),1);
			circle(70,40,3,turnOnOff(0,0b00000100),1);
			circle(70,50,3,turnOnOff(0,0b01000000),1);
			
			
			circle(80,20,3,turnOnOff(1,0b00001000),1);
			circle(80,30,3,turnOnOff(1,0b10000000),1);
			circle(80,40,3,turnOnOff(0,0b00001000),1);
			circle(80,50,3,turnOnOff(0,0b10000000),1);
}
void menuPatern(){
	unsigned char namePattern[][8] = {"Pat1", "Pat2", "Pat3", "Pat4", "Pat5", "Pat6", "Pat7", "Pat8"};
		glcd_clear();
		_delay_ms(5);
		glcd_puts(namePattern[selNumpatterm],8,4,0,1,0);
		glcd_puts("Up(Back)",30,0,0,1,0);
		glcd_puts("Down(Edit)",30,7,0,1,0);
		glcd_puts("<",0,4,0,1,0);
		glcd_puts(">",120,4,0,1,0);
		drawPattern();
		
		while(1){
		unsigned char pushKey = (PIND>>2);
		pushKey &=0x1F;
		if (pushKey == 0b00011110)
		{//ok
			unsigned char packetSel = 0b10000000;
			packetSel |=(convertdectobin(selNumMicro)<<3);
			packetSel |=convertdectobin(selNumpatterm);
			while(!(UCSRA & (1<<UDRE)));
			UDR = packetSel;
		}
		if (pushKey == 0b00011101)
		{//up
			break;
		}
		if (pushKey == 0b00011011)
		{//down
			keyboard(namePattern[selNumpatterm]);
			glcd_clear();
			_delay_ms(5);
			glcd_puts(namePattern[selNumpatterm],8,4,0,1,0);
			glcd_puts("Up(Back)",30,0,0,1,0);
			glcd_puts("Down(Edit)",30,7,0,1,0);
			glcd_puts("<",0,4,0,1,0);
			glcd_puts(">",120,4,0,1,0);
			drawPattern();
			_delay_ms(500);

		}
		if (pushKey == 0b00010111)
		{
				glcd_clear();
				_delay_ms(5);
				selNumpatterm =  ++selNumpatterm>=8 ? 0 : selNumpatterm;
				glcd_puts(namePattern[selNumpatterm],8,4,0,1,0);
				glcd_puts("Up(Back)",30,0,0,1,0);
				glcd_puts("Down(Edit)",30,7,0,1,0);
				glcd_puts("<",0,4,0,1,0);
				glcd_puts(">",120,4,0,1,0);
				drawPattern();
				_delay_ms(500);
		}
		if (pushKey == 0b00001111)
		{//left
				glcd_clear();
				_delay_ms(5);
				selNumpatterm = --selNumpatterm <0 ? 7 : selNumpatterm;
				glcd_puts(namePattern[selNumpatterm],8,4,0,1,0);
				glcd_puts("Up(Back)",30,0,0,1,0);
				glcd_puts("Down(Edit)",30,7,0,1,0);
				glcd_puts("<",0,4,0,1,0);
				glcd_puts(">",120,4,0,1,0);
				drawPattern();
				_delay_ms(500);
			
		}
	}
}
void main(void)
{
#pragma used+

unsigned char nameMicro[][16] = {"Micro01", "Micro02", "Micro03", "Micro04", "Micro05", "Micro06",
	 "Micro07", "Micro08", "Micro09", "Micro10", "Micro11", "Micro12", 
	"Micro13", "Micro14", "Micro15", "Micro16"};
#pragma used-



DATADDR = 0xff;
DDRD=0x80;
DDRD &= 0x83;
PORTD |= 0x7c;
DDRC = 0x0F;

glcd_on();

UCSRB = (1<<RXEN) | (1<<RXCIE) |  (1<<TXEN);
UCSRC = (1<< UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
UBRRL = 0x33;
sei();

DDRD &= 0x83;
PORTD |= 0x7c;
for (int v=0; v<16; v++)
{
	eeprom_update_block (( const void *) paterns[v] , ( void *) (16*v), 16);
}
for (int z=0; z<16; z++)
{
eeprom_read_block (( void *) paterns[z] , ( const void *) (16*z), 16) ;
}

unsigned char resetMenu = 0xff;
while(1){
	unsigned char pushKey = (PIND>>2);
	pushKey &=0x1F;
	if (pushKey == 0b00011111 && resetMenu)
	{
		if(pageScreen == 0){
			glcd_clear();
			_delay_ms(5);
			glcd_puts(t,8,3,0,2,0);
			glcd_puts("Down",50,7,0,1,0);
			
		}else{
				glcd_clear();
				_delay_ms(5);
				glcd_puts(nameMicro[selNumMicro],8,3,0,2,0);
				glcd_puts("Up",50,0,0,1,0);
				glcd_puts("<",0,4,0,1,0);
				glcd_puts(">",120,4,0,1,0);
		}
		resetMenu = 0x00;
	}
	if (pushKey == 0b00011110)
	{//ok
		if (pageScreen == 1)
		{
		resetMenu = 0xff;
		menuPatern();
		PORTD |= 0x7c;
		_delay_ms(500);
		pushKey = (PIND>>2);
		pushKey &=0x1F;
		pageScreen = 1;
		}
	}
	else if (pushKey == 0b00011101)
	{//up
		pageScreen--;		
		if(pageScreen == 0){
			glcd_clear();
			_delay_ms(5);
			glcd_puts(t,8,3,0,2,0);
			glcd_puts("Down",50,7,0,1,0);
		}
		else{
			pageScreen = 0;
		}
	}
	else if (pushKey == 0b00011011)
	{//down
		pageScreen++;

		if(pageScreen == 1){
			glcd_clear();
			_delay_ms(5);
			glcd_puts(nameMicro[selNumMicro],8,3,0,2,0);
			glcd_puts("Up",50,0,0,1,0);
			glcd_puts("<",0,4,0,1,0);
			glcd_puts(">",120,4,0,1,0);
		}else{
			pageScreen = 1;
		}

	}
	else if (pushKey == 0b00010111)
	{
		if(pageScreen == 1){
		//glcd_clear();
		//_delay_ms(5);
		
		selNumMicro =  ++selNumMicro>=16 ? 0 : selNumMicro;
		glcd_puts(nameMicro[selNumMicro],8,3,0,2,0);
		_delay_ms(500);
			//glcd_puts("Up",50,0,0,1,0);
			//glcd_puts("<",0,4,0,1,0);
			//glcd_puts(">",120,4,0,1,0);
		}
	}
	else if (pushKey == 0b00001111)
	{//left
		if(pageScreen == 1){
		//glcd_clear();
		//_delay_ms(5);
		selNumMicro = --selNumMicro <0 ? 15 : selNumMicro;
		glcd_puts(nameMicro[selNumMicro],8,3,0,2,0);
		_delay_ms(500);
		//glcd_puts("Up",50,0,0,1,0);
		//glcd_puts("<",0,4,0,1,0);
		//glcd_puts(">",120,4,0,1,0);
		}
	}
}
}
