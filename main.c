#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "include\src\lut.h"
#include "include\src\ansi.h"
#include "include\src\gpio.h"
//#include "include\src\charset.h"
#include "include\src\game.h"

#define DIGIT_1 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<5);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT |= (1<<7);PEOUT &= ~(1<<7);}
#define DIGIT_2 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<6);PEOUT &= ~(1<<7);PGOUT &= ~(1<<7);PGOUT |= (1<<7);PGOUT &= ~(1<<7);}
#define DIGIT_3 {PEOUT &= ~(1<<6);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT |= (1<<5);PEOUT &= ~(1<<5);}
#define DIGIT_4 {PGOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT &= ~(1<<7);PEOUT &= ~(1<<6);PEOUT |= (1<<6);PEOUT &= ~(1<<6);}

char videoBuffer[5][6];
int nFlagClock=0;
int nTickTime=0;
int nBallTime=0;

#pragma interrupt
void timer0int(){
	nTickTime++;
	nBallTime++;
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
	T0RH = 0x00;	//upper half of reload value ex. A0
	T0RL = 0x90;	//first half of reload value ex. 02		(hele tal 0xA002)
	T0H = 0x00;		// set to 0
	T0L = 0x00;		// set to 0

	IRQ0ENH |= 0x00; // set prioritie ME, H og L \/
	IRQ0ENL |= 0x20;

	T0CTL = 0xB9; // 10111001

	SET_VECTOR(TIMER0, timer0int);

	EI(); // enable timer
}


void main(){
	struct positions game1;
	int ballTimer;
	game1.length = 50;
	game1.height = 50;

	init_uart(_UART0, _DEFFREQ, _DEFBAUD);

	LEDinit();    //flydt timeren i sin egen funktion!!
	cleanscreen();
	gameInitial(&game1);
	releaseBall(&game1);
	
	while(1){
		if(nTickTime>=1){
			nextPosition(&game1, 0);
			nTickTime = 0;
		}
		if(nBallTime>=25){
			nextPosition(&game1, 1);
			nBallTime = 0;
		}
	}

	do{} while(1>0);
}
