#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include <string.h>
#include "include\src\lut.h"
#include "include\src\ansi.h"
#include "include\src\gpio.h"
#include "include\src\charset.h"
//#include "include\src\timer.h"


#define FIX14_SHIFT 14
#define FIX14_MULT(a, b)	( (a)*(b) >> FIX14_SHIFT )
//#define FIX14_DIV(a, b)	( ((a) << FIX14_SHIFT) / (b) )
#define DIGIT_1 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<5);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT |= (1<<7);PEOUT &= ~(1<<7);}
#define DIGIT_2 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<6);PEOUT &= ~(1<<7);PGOUT &= ~(1<<7);PGOUT |= (1<<7);PGOUT &= ~(1<<7);}
#define DIGIT_3 {PEOUT &= ~(1<<6);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT |= (1<<5);PEOUT &= ~(1<<5);}
#define DIGIT_4 {PGOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT &= ~(1<<7);PEOUT &= ~(1<<6);PEOUT |= (1<<6);PEOUT &= ~(1<<6);}

char videoBuffer[5][6];
int nFlagClock=0;
int nTickTime=0;

#pragma interrupt
void timer0int(){
	nTickTime++;
	if(nFlagClock==1){
		nFlagClock=0;
	}else{
		nFlagClock=1;
	}
}

void LEDinit(){
	PEDD  = 0x00;
	PGDD  = 0x00;

	DI(); // dissable timer

	T0CTL = 0X39; // 00111001
	T0RH = 0x00;	//ovre halvdel af reload value ex. A0
	T0RL = 0x90;	//nedre halvdel af reload value ex. 02		(hele tal 0xA002)
	T0H = 0x00;		// saettes til 0
	T0L = 0x00;		// saettes til 0

	IRQ0ENH |= 0x00; // saet prioritet me H og L \/
	IRQ0ENL |= 0x20;

	T0CTL = 0xB9; // 10111001

	SET_VECTOR(TIMER0, timer0int);

	EI(); // enable timer
}

void LEDsetString(char string[]){
	int i,j;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5 ; j++){
			videoBuffer[i][j] = character_data[string[4-i]-0x20][4-j];
		}
		videoBuffer[i][5]=0x00;
	}
}

void LEDupdate(int i){
	int j;
	if(nFlagClock==1){			
		for(j=0; j < 4; j++){    //update

			PEOUT |= 0x1F;
			PEOUT &= ~(1<<i);
			PGOUT = videoBuffer[j][i] & 0x7F;

			switch(j){
				case 3:
					DIGIT_1
					break;
				case 2:
					DIGIT_2
					break;
				case 1:
					DIGIT_3
					break;
				default:
					DIGIT_4
					break;

			}
		}
	} 
}


void main(){
	char input[5]={'V','E','E','N','!'};
	int i,j,scrollA;
	init_uart(_UART0, _DEFFREQ, _DEFBAUD);
	LEDinit();
	LEDsetString(input);
	while(1){
		LEDupdate(0);
		LEDupdate(1);
		LEDupdate(2);
		LEDupdate(3);
		LEDupdate(4);
		if(nTickTime==500){
			scrollA = videoBuffer[4][5];
			for(i = 4; i >= 0; i--){
				for(j = 5; j >= 1; j--){
					videoBuffer[i][j] = videoBuffer[i][j-1];
				}
				if(i==0){
					videoBuffer[0][0] = scrollA;
				}else{
					videoBuffer[i][0] = videoBuffer[i-1][5];
				}
			}
			nTickTime=0;
		}
		
	}

	do{} while(1>0);
}
