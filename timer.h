#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines


struct time {
	int hour;
	int minute;
	int second;
	int csecond; // centi seconds
};

void ting(struct time *total);
