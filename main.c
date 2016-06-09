#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include <string.h>
#include "include\src\lut.h"
#include "include\src\ansi.h"

// endnu en test


void main(){
	struct TVector pt = {-4,2};
	init_uart(_UART0, _DEFFREQ, _DEFBAUD);
	
	printf("(%d,%d)\n",pt.x,pt.y);

	initVector(&pt,-49); //vinkel skal skrives som 512 format

	printFix(expand(pt.x));
	printFix(expand(pt.y));

	do{} while(1>0);
}

