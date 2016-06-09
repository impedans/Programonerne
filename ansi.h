#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include <string.h>

#define FIX14_SHIFT 14

#define FIX14_MULT(a,b)  ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b)  ( (a) << FIX14_SHIFT / (b))


