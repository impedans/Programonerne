#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "game.h"
#ifndef GPIO_C
#define GPIO_C

char readkey(){
	unsigned char states=0;

	PDDD   = 0x08;	        //high nibble = input, low nibble = output
	PFDD   = 0xC0;
	PGADDR = 0;		        //no function; provides some protection
 	states |= PDIN & 0x08;  //read the upper four I/O pins
	states |= PFIN & 0xC0;
	return states;
}

/*
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

*/

#endif
