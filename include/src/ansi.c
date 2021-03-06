#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "game.h"



#define ESC 0x1B

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void cleanscreen (){
	printf("%c[2J", ESC);
}

void gotoxy(int x, int y){
	printf("%c[%d;%dH", ESC, x, y);
}

void reverse(int bg, int fg) {
	color(bg, fg);
}

void gameWindow(int x1, int y1, int x2, int y2){ 	   //Draws game windows
	int i, j;
	gotoxy(x1,y1);
    printf("%c", 201);	

	for(i = 0 ; i < x2-x1 ; i++){   					//Horizontal line
		printf("%c",205);
    }
		printf("%c\n", 187);

    for (i = 1; i <= (y2-y1); i++){					    //Vertival lines
		gotoxy(x1+i,y1);
		printf("%c", 186);

		gotoxy(x1+i,(y2) * 3 + 1);
		printf("%c\n", 186);
    }
}

void drawStriker(int strikerCenter, int height){		 //Draws striker
	gotoxy(height, strikerCenter - 7);
	color(1,15);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
	resetbgcolor();

}

void drawBall(int x,int y){  							//Draws ball
	gotoxy(x,y);
	printf("%c",88);
}

void deleteCharacter(int x,int y){ 						//Deletes character
	gotoxy(x,y);
	printf("%c",32);
}
	
void drawBlock(int x1, int y1, short N, struct positions *game){ 	//Draws block
	short i = 0, j = 0;

	(*game).block[N][0] = x1;				//Saves block start coordinates
	(*game).block[N][1] = y1;

	if((*game).block[N][2] == 0){			//Lives = 0
		PCOUT = 0x20;

		for(i = 0 ; i < (*game).blockHeight ; i++){
			gotoxy(x1+i, y1);
			for(j = 0; j < (*game).blockLength; j++){
				printf("%c",32);
			}
		}
		(*game).block[N][0] = -10;   		//Sets block coordinates out of field, if block is dead
		(*game).block[N][1] = -10;
		(*game).points     += 20 + (*game).pointBonus;	   //Adds points for every destroyed block
		(*game).pointBonus += 10;						   //Adds bonus for every destroyed block
		j = 0;
		for(i = 0; i < (*game).numBlocks; i++){
			if((*game).block[i][0] == -10){
				j++;
			}
			
			if(j == (*game).numBlocks){
				if ((*game).level == 3){  					//Checks if player has won game
					gotoxy(20, 79);
					printf("You win the game!");
					gotoxy(21, 79);
					printf("The filthy Mexicans were kept out.");
					gotoxy(22, 79);
					printf("Press right button to kick their ass again");
					PCOUT = 0x01;
					drawInfo(game);
					for(i = -7; i <= 7; i++){
						deleteCharacter((*game).height, (*game).strikerCenter-i);
					}
					while(1){
						if((readkey() & 0x80)==0){
							for(i=0; i <= 46; i++){
								deleteCharacter(20, 79+i);
							}
							break;
						}
					}
					(*game).level = 1;
					(*game).lives = 2;
					(*game).points = 0;
					gameInitial(game);
					releaseBall(game);

				} else {
					
					(*game).level++;						//Checks if player has won game
					PCOUT = 0x01;
					drawInfo(game);
					for(i = -7; i <= 7; i++){
						deleteCharacter((*game).height, (*game).strikerCenter-i);
					}
					gotoxy(20, 79);
					printf("Level complete!");
					gotoxy(21, 79);
					printf("Press right button to continue");
					while(1){
						if((readkey() & 0x80)==0){
							for(i=0; i <= 46; i++){
								deleteCharacter(20, 79+i);
							}
							break;
						}
					}
					gameInitial(game);
					releaseBall(game);	
				}
			}
		}

	} else if((*game).block[N][2] == 1){	//Lives = 1  ---  Blue
		for(i = 0 ; i < (*game).blockHeight ; i++){
			color(4,0);
			gotoxy(x1+i, y1);
			for(j = 0; j < (*game).blockLength; j++){
				printf("%c",177);
			}
		}
	} else if((*game).block[N][2] == 2){	//Lives = 2  ---  White
		for(i = 0 ; i < (*game).blockHeight ; i++){
			color(15,0);
			gotoxy(x1+i, y1);
			for(j = 0; j < (*game).blockLength; j++){
				printf("%c",178);
			}
		}
	} else if((*game).block[N][2] == 3){	//Lives = 3  ---  Red
		for(i = 0 ; i < (*game).blockHeight ; i++){
			color(1,0);
			gotoxy(x1+i, y1);
			for(j = 0; j < (*game).blockLength; j++){
				printf("%c",219);
			}
		}
	} 
	color(15,0);
	drawInfo(game);
}

void drawInfo(struct positions *game){   	//Draws info on screen
	gotoxy(2,87);
	printf("%d", (*game).lives);
	gotoxy(3,87);
	printf("%d         Bonus: %d         ", (*game).points, (*game).pointBonus);
	gotoxy(4,87);
	printf("%d", (*game).level);
}

void drawFlag(int lives){	 				//Draws mexican flag gradually
	int i, j;
	if (lives == 2){
		gotoxy(10,79);
		for (i = 0; i < 7; i++){
			color(2,0);
			printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
			gotoxy(10+i,79);
			color(15,0);
		}
	} else if (lives == 1){
		gotoxy(10,86);
		for (i = 0; i < 7; i++){
			color(15,0);
			printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
			gotoxy(10+i,86);
			color(15,0);
		}
	} else if (lives == 0) {
		gotoxy(10,93);
		for (i = 0; i < 7; i++){
			color(1,0);
			printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
			gotoxy(10+i,93);
			color(15,0);
		}
	}
}


