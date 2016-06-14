#include <sio.h>
#include <eZ8.h>             // special encore constants, macros and flash routines#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "timer.h"
/*
void ting(struct time *total){
	if((readkey() & 0x08)==0){       //split time 2
		while(1){
			if((readkey() & 0x08)!=0){
        		gotoxy(4,2);
       			printf("%d:%d:%d:%d", (*total).hour, (*total).minute, (*total).second, (*total).csecond);
				break;
			} else if((readkey() & 0x40)==0){
				while(1){
					if((readkey() & 0x08)!=0 && (readkey() & 0x40)!=0){
						DI();
						(*total).hour=0;
						(*total).minute=0;
						(*total).second=0;
						(*total).csecond=0;
						break;
					}
				}
			}
		}
	}

	if((readkey() & 0x40)==0){       //split time 1
		while(1){
			if((readkey() & 0x40)!=0){
     	 		gotoxy(3,2);
        		printf("%d:%d:%d:%d", (*total).hour, (*total).minute, (*total).second, (*total).csecond);
				break;
			} else if((readkey() & 0x08)==0){
				while(1){
					if((readkey() & 0x40)!=0 && (readkey() & 0x40)!=0){
						DI();
						(*total).hour=0;
						(*total).minute=0;
						(*total).second=0;
						(*total).csecond=0;
						break;
					}
				}
			}
			}
	}

	if((readkey() & 0x80)==0){       //start/stop
		while(1){
			if((readkey() & 0x80)!=0){
	      	DI();
				if((readkey() & 0x80)==0){       //start
					while(1){
						if((readkey() & 0x80)!=0){
							EI();
							break;
						}
					}
					break;
				}
			}
		}
	}
}*/
