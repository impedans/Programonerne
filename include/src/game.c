#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "game.h"
#include "ansi.h"
#include "gpio.h"


void gameInitial(struct positions *game){
  int i, j;
  int length = (*game).length * 3;
  int height = (*game).height;
  //blocks array that holds ccordinates and lives



  if ((length > XMAX * 3 || length < 0) || ( height > YMAX || height < 0)){
    printf("ERROR\n");
    return;
  }

  // draw window
  gameWindow(1,1,length,height);

  // draw striker
  (*game).strikerCenter = length/2;
  drawStriker((*game).strikerCenter, (*game).height);

  // draw ball
  (*game).ballX = height - 1;
  (*game).ballY = (*game).strikerCenter;
  (*game).ballAngle = 128;

  drawBall((*game).ballX,(*game).ballY);

  //set amount of lives, write info text
  (*game).lives = 3;
  gotoxy(55,10);
  printf("Lives: ");
  (*game).points = 0;
  gotoxy(56,10);
  printf("Points: ");
  (*game).level = 1;
  gotoxy(57,10);
  printf("Level: ");
  drawInfo(game);

  // Remove Mexican flag
  for (i = 0; i < 7; i++){
    for (j = 0; j < 7; j++){
      deleteCharacter(55+i,99+j);
      deleteCharacter(55+i,106+j);
      deleteCharacter(55+i,113+j);
    }
  }
  color(15,0);

  // draw Blocks
  ////////////////LEVEL 1/////////////////////////////////////

  //drawBlock(10,10,20,20, (*game).block);       //block varable initialatation

  /*drawBlock(10,20,30,30);
  drawBlock(10,30,40,40);
  drawBlock(10,40,50,50);
  drawBlock(10,50,60,60);
  drawBlock(10,60,70,70);
  drawBlock(10,70,80,80);
  drawBlock(10,80,90,90);
  drawBlock(10,90,100,100);
  drawBlock(10,100,110,110);
  drawBlock(10,110,120,120);
  drawBlock(10,120,130,130);
  drawBlock(10,130,140,140);*/

}

void nextPosition(struct positions *game, int BallTime){
  int i;
  /*------------------------------Ball position------------------------------------------*/
  if(BallTime == 1){
     deleteCharacter((*game).ballX,(*game).ballY);
  	(*game).ballX = (*game).ballX + (*game).speedX;
    (*game).ballY = (*game).ballY + (*game).speedY;

    if((*game).ballX <= 1){													                  //Hit top
       (*game).speedX *= -1;
       (*game).ballX = 2;                                             //EDIT: returns ball to fiels
    } if ((*game).ballY <= 1 || (*game).ballY >= (*game).length*3){		//Hit sides (EDIT: runs every time)
       (*game).speedY *= -1;
       if((*game).ballY <= 1){                                        //EDIT: if/else that returns ball to field
         (*game).ballY = 2;
       } else {
         (*game).ballY = (*game).length*3-1;
       }

    } else if ((*game).ballX == (*game).height-1 && ((*game).ballY > (*game).strikerCenter-8 && (*game).ballY < (*game).strikerCenter+8)){
		if((*game).ballY > (*game).strikerCenter-1 && (*game).ballY < (*game).strikerCenter+1){
          (*game).speedX *= -1;

		} else if ((*game).ballY > (*game).strikerCenter-4 && (*game).ballY < (*game).strikerCenter-1){
      (*game).speedX *= -1;
		  (*game).speedY--;

		} else if ((*game).ballY > (*game).strikerCenter+1 && (*game).ballY < (*game).strikerCenter+4){
      (*game).speedX *= -1;
		  (*game).speedY++;

		} else if ((*game).ballY > (*game).strikerCenter-8 && (*game).ballY < (*game).strikerCenter-4){
      (*game).speedX *= -1;
		  (*game).speedY -= 2;

		} else {
		  (*game).speedX *= -1;
		  (*game).speedY += 2;
		}

    }else if((*game).ballX > (*game).height){																//Out of bounds
      (*game).lives--;
      drawFlag((*game).lives);
      drawInfo(game);

	    if ((*game).lives == 0){
	      for(i = -7; i <= 7; i++){
          deleteCharacter((*game).height, (*game).strikerCenter-i);
        }
        gotoxy(55, 50);
        printf("Mexico triumpfed. Press right button to restart");
        while(1){
          if((readkey() & 0x80)==0){
            for(i=0; i <= 46; i++){
              deleteCharacter(55, 50+i);
            }
	        break;
          }
        }
		    gameInitial(game);
	     }
       releaseBall(game);
     }
     drawBall((*game).ballX,(*game).ballY);
   }

  /*------------------------------Striker position------------------------------------------*/
  if((readkey() & 0x08) == 0 && (*game).strikerCenter > 9){
    (*game).strikerCenter--;
	  deleteCharacter((*game).height, (*game).strikerCenter+8);
    drawStriker((*game).strikerCenter, (*game).height);
  } else if((readkey() & 0x80) == 0 && (*game).strikerCenter < (*game).length*3-7){
    (*game).strikerCenter++;
    deleteCharacter((*game).height, (*game).strikerCenter-8);
    drawStriker((*game).strikerCenter, (*game).height);
  }
}

void releaseBall(struct positions *game){
  int i;

  (*game).ballX = (*game).height - 1;                             //Resets ball
  (*game).ballY = ((*game).length*3)/2;
  (*game).speedX = 0;
  (*game).speedY = 0;
  drawBall((*game).ballX,(*game).ballY);

  for(i = -7; i <= 7; i++){
      deleteCharacter((*game).height, (*game).strikerCenter-i);   //Deletes old striker
  }
  (*game).strikerCenter = (*game).length*3/2;                     //Draws new striker
  drawStriker((*game).strikerCenter, (*game).height);

  while(1){                                                       //Restarts game
     if((readkey() & 0x40)==0){
       (*game).speedX = -1;
       (*game).speedY = 1;
	   break;
     }
  }
}
