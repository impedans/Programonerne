#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "game.h"


char readkey(){	     		//Reads key and return the key beeing pressed as binary number
	unsigned char states=0;

	PDDD   = 0x08;	        //high nibble = input, low nibble = output
	PFDD   = 0xC0;
	PGADDR = 0;		        //no function; provides some protection
 	states |= PDIN & 0x08;  //read the upper four I/O pins
	states |= PFIN & 0xC0;
	return states;
}


