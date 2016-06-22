#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "include\src\lut.h"
#include "include\src\ansi.h"
#include "include\src\gpio.h"
#include "include\src\game.h"

#define DIGIT_1 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<5);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT |= (1<<7);PEOUT &= ~(1<<7);}
#define DIGIT_2 {PEOUT &= ~(1<<6);PEOUT &= ~(1<<6);PEOUT &= ~(1<<7);PGOUT &= ~(1<<7);PGOUT |= (1<<7);PGOUT &= ~(1<<7);}
#define DIGIT_3 {PEOUT &= ~(1<<6);PGOUT &= ~(1<<7);PEOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT |= (1<<5);PEOUT &= ~(1<<5);}
#define DIGIT_4 {PGOUT &= ~(1<<7);PEOUT &= ~(1<<5);PEOUT &= ~(1<<7);PEOUT &= ~(1<<6);PEOUT |= (1<<6);PEOUT &= ~(1<<6);}

char videoBuffer[21][6] = { 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x00, 0x00, 0x5F, 0x5F, 0x00},	//! 
{0x00, 0x00, 0x00, 0x5F, 0x5F, 0x00},	//! 
{0x00, 0x00, 0x00, 0x5F, 0x5F, 0x00},	//! 
{0x00, 0x06, 0x09, 0x09, 0x09, 0x7F},	//P 
{0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F},	//M 
{0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F},	//U 
{0x00, 0x76, 0x09, 0x09, 0x09, 0x7F},	//R 
{0x00, 0x01, 0x01, 0x7F, 0x01, 0x01},	//T 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x40, 0x40, 0x40, 0x40, 0x7C},	//L 
{0x00, 0x00, 0x41, 0x7F, 0x41, 0x00},	//I 
{0x00, 0x7C, 0x0A, 0x09, 0x0A, 0x7C},	//A 
{0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F},	//H 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//SPACE 
{0x00, 0x40, 0x40, 0x40, 0x40, 0x7C},	//L 
{0x00, 0x40, 0x40, 0x40, 0x40, 0x7C},	//L 
{0x00, 0x7C, 0x0A, 0x09, 0x0A, 0x7C}	//A 
}; 


int nFlagClock = 0;
int nTickTime=0;
int nTickLEDTime=0;
int nBallTime=0;

#pragma interrupt
void timer0int(){
	nTickLEDTime++;
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
	PEOUT &= 0x00;

	DI(); // dissable timer

	T0CTL = 0X39; // 00111001
	T0RH = 0x00;	//upper half of reload value ex. 00
	T0RL = 0x90;	//first half of reload value ex. 90		(hele tal 0x0090)
	T0H = 0x00;		// set to 0
	T0L = 0x00;		// set to 0

	IRQ0ENH |= 0x00; // set prioritie ME, H og L \/
	IRQ0ENL |= 0x20;

	T0CTL = 0xB9; // 10111001

	SET_VECTOR(TIMER0, timer0int);

	EI(); // enable timer

	PCDD = 0x00;
	PCOUT &= 0x00;


	//PFDD   = 0xC0;
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
	struct positions game1;
	int ballTimer,i,j;
	char scrollA;
	game1.length = 25;
	game1.height = 25;
	game1.level  = 1;
	game1.points = 0;
	game1.pointBonus = 0;

	init_uart(_UART0, _DEFFREQ, _DEFBAUD);

	LEDinit();    //flyt timeren i sin egen funktion!!

	gameInitial(&game1);
	releaseBall(&game1);
	
	while(1){
		if(nTickTime>=game1.difficultyStriker){ //Striker
			nextPosition(&game1, 0);
			nTickTime = 0;
		}
		if(nBallTime>=game1.difficultyBall){ //Ball
			nextPosition(&game1, 1);
			//PEOUT &= 0x00;
			PCOUT &= 0x00;
			nBallTime = 0;
		}
		LEDupdate(0);
		LEDupdate(1);
		LEDupdate(2);
		LEDupdate(3);
		LEDupdate(4);
		if(nTickLEDTime>=250){
			scrollA = videoBuffer[20][5];
			for(i = 20; i >= 0; i--){
				for(j = 5; j >= 1; j--){
					videoBuffer[i][j] = videoBuffer[i][j-1];
				}
				if(i==0){
					videoBuffer[0][0] = scrollA;
				}else{
					videoBuffer[i][0] = videoBuffer[i-1][5];
				}
			}
			nTickLEDTime=0;
		}
	}

	do{} while(1>0);
}
