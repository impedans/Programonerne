#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include <string.h>

#define FIX14_SHIFT 14

#define FIX14_MULT(a,b)  ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b)  ( (a) << FIX14_SHIFT / (b))

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void cleanscreen();
void clreol ();
void gotoxy(int x, int y);
void underline(char on);
void blink(char on);
void reverse(int bg, int fg);
void window(int x1, int y1, int x2, int y2, int style, char* title);
void gameWindow(int x1, int y1, int x2, int y2);
void drawStriker(int strikerCenter, int height);
void drawBall(int x,int y);
void deleteCharacter(int x,int y);
void drawBlock(int x1, int y1, int x2, int y2);
