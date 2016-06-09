#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include <string.h>
#include "include\src\lut.h"
#include "include\src\ansi.h"
#include "include\src\gpio.h"
#include "include\src\timer.h"

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b)	( (a)*(b) >> FIX14_SHIFT )
//#define FIX14_DIV(a, b)	( ((a) << FIX14_SHIFT) / (b) )

struct time totalTime;

#pragma interrupt
void timer0int(){
	totalTime.csecond++;

	if(totalTime.csecond == 100){
		totalTime.second++;
		totalTime.csecond = 0;
	}
	if(totalTime.second == 60){
		totalTime.minute++;
		totalTime.second = 0;
	}
	if(totalTime.minute == 60){
		totalTime.hour++;
		totalTime.minute = 0;
	}
//		totalTime.hour = FIX14_DIV(totalTime.csecond, 360000);
//		totalTime.minute = FIX14_DIV((totalTime.csecond%360000) , 60);
//		totalTime.second = FIX14_DIV(((totalTime.csecond%360000)%60) , 100);
		//totalTime.csecond = FIX14_DIV((((totalTime.csecond%360000)%60)%60) , 100);


//	totalTime.cseconds+=1;
//	if (totalTime.cseconds == 360000){
//		totalTime.hour += 1;
//		totalTime.cseconds = 0;

}
void timer(){

}

void main(){

	init_uart(_UART0, _DEFFREQ, _DEFBAUD);
	DI();

	T0CTL = 0X39; // 00111001
	T0RH = 0x05;
	T0RL = 0xA0;
	T0H = 0x00;
	T0L = 0x00;

	IRQ0ENH |= 0x20;
  	IRQ0ENL |= 0x20;

	T0CTL = 0xB9; // 10111001

	SET_VECTOR(TIMER0, timer0int);

	EI();
	cleanscreen ();
	window(1, 1, 12, 5, 1, "klokke");
	
	while(1!=0){
		gotoxy(2,2);
		printf("%d:%d:%d:%d", totalTime.hour,totalTime.minute,totalTime.second, totalTime.csecond);
		ting(&totalTime);
	}
	do{} while(1>0);
}
