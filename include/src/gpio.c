#include <sio.h>
#include <eZ8.h>             // special encore constants, macros and flash routines

char readkey(){
	unsigned char states=0;

	PDDD   = 0x08;	//high nibble = input, low nibble = output
	PFDD   = 0xC0;
	PGADDR = 0;		//no function; provides some protection
 	states |= PDIN & 0x08;//read the upper four I/O pins
	states |= PFIN & 0xC0;
	return states;
}

void ledClock(int n){
	if(n==0){
		PEOUT &= ~(1<<6);
		PEOUT &= ~(1<<5);
		PGOUT &= ~(1<<7);

		PEOUT &= ~(1<<7);
		PEOUT |= (1<<7);
		PEOUT &= ~(1<<7);
	}else if(n==1){
		PEOUT &= ~(1<<6);
		PEOUT &= ~(1<<5);
		PEOUT &= ~(1<<7);

		PGOUT &= ~(1<<7);
		PGOUT |= (1<<7);
		PGOUT &= ~(1<<7);
	}else if(n==2){
		PEOUT &= ~(1<<6);
		PGOUT &= ~(1<<7);
		PEOUT &= ~(1<<7);

		PEOUT &= ~(1<<5);
		PEOUT |= (1<<5);
		PEOUT &= ~(1<<5);
	}else{
		PGOUT &= ~(1<<7);
		PEOUT &= ~(1<<5);
		PEOUT &= ~(1<<7);

		PEOUT &= ~(1<<6);
		PEOUT |= (1<<6);
		PEOUT &= ~(1<<6);
	}
}

void led(int *a, int *b, int *c){
	int total = (*a) + (*b) + (*c);
	PEDD  = 0x00;
	PGDD  = 0x00;
	printf("Led-funktion siger: %d\n", total);

	PEOUT &= ~0x01;

	PGOUT = total & 0x7F;

	ledClock(2);
}

void counter(int *a, int *b, int *c){
	if((readkey() & 0x08)==0){
		while(1){
			if((readkey() & 0x08)!=0){
				(*a)++;
				printf("a: %d\n", *a);
				led(a, b, c);
				break;
			}
		}
	}

	if((readkey() & 0x40)==0){
		while(1){
			if((readkey() & 0x40)!=0){
				(*b)++;
				printf("b: %d\n", *b);
				led(a, b, c);
				break;
			}
		}
	}

	if((readkey() & 0x80)==0){
		while(1){
			if((readkey() & 0x80)!=0){
				(*c)++;
				printf("c: %d\n", *c);
				led(a, b, c);
				break;
			}
		}
	}
}
