#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "game.h"
#include "ansi.h"
#include "gpio.h"
#include "lut.h"


void gameInitial(struct positions *game){
  int i, j;
  int length = (*game).length * 3;
  int height = (*game).height;
  //blocks array that holds ccordinates and lives



  if ((length > YMAX * 3 || length < 0) || ( height > XMAX || height < 0)){
    printf("ERROR\n");
    return;
  }

  // draw window
  gameWindow(1,1,length,height);

  // draw striker
  (*game).strikerCenter = length/2;
  drawStriker((*game).strikerCenter, (*game).height);

  // draw ball
  (*game).ballY = height - 1;
  (*game).ballX = (*game).strikerCenter;

  drawBall((*game).ballY,(*game).ballX);

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
    (*game).oldBallY = (*game).ballY;
   (*game).oldBallX = (*game).ballX;

    if((*game).ballY <= 1){													//Hit top
      (*game).speedX *= -1;
      (*game).ballAngle = 512-(*game).ballAngle;

      (*game).ballY = (*game).ballY + (*game).speedY;
      (*game).ballX = (*game).ballX + (cos((*game).ballAngle)/sin((*game).ballAngle));      // sin(angle)/cos(angle)
	  i= (cos((*game).ballAngle)/sin((*game).ballAngle));
	  printf("fix osv lig: %d og bally: %d",i, (*game).ballX);

    } else if ((*game).ballX <= 1 || (*game).ballX >= (*game).length*3){		//Hit sides
      (*game).ballAngle = 256-(*game).ballAngle;

      (*game).ballY = (*game).ballY + (*game).speedY;
      (*game).ballX = (*game).ballX + (cos((*game).ballAngle)/sin((*game).ballAngle));

    } else if ((*game).ballY == (*game).height && ((*game).ballX > (*game).strikerCenter-8 && (*game).ballX < (*game).strikerCenter+8)){
		  if((*game).ballX > (*game).strikerCenter-1 && (*game).ballX < (*game).strikerCenter+1){
        (*game).speedX *= -1;
        (*game).ballAngle = 512-(*game).ballAngle;

	  	} else if ((*game).ballX > (*game).strikerCenter-4 && (*game).ballX < (*game).strikerCenter-1){
        (*game).speedX *= -1;
        (*game).ballAngle = (512-(*game).ballAngle) + 12;

	  	} else if ((*game).ballX > (*game).strikerCenter+1 && (*game).ballX < (*game).strikerCenter+4){
        (*game).speedX *= -1;
        (*game).ballAngle = (512-(*game).ballAngle) - 12;

	  	} else if ((*game).ballX > (*game).strikerCenter-8 && (*game).ballX < (*game).strikerCenter-4){
        (*game).speedX *= -1;
        (*game).ballAngle = (512-(*game).ballAngle) - 24;

	  	} else {
        (*game).speedX *= -1;
		    (*game).ballAngle = (512-(*game).ballAngle) - 24;
		}
    (*game).ballY = (*game).ballY + (*game).speedY;
	  (*game).ballX = (*game).ballX + (cos((*game).ballAngle)/sin((*game).ballAngle));
    } else if((*game).ballY > (*game).height){																//Out of bounds
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
   }else {
     (*game).ballY = (*game).ballY + (*game).speedY;
     (*game).ballX = (*game).ballX + (cos((*game).ballAngle)/sin((*game).ballAngle));
	 i = (FIX14_DIV((cos((*game).ballAngle)),(sin((*game).ballAngle))) >> 16);
	 printf("%d og s� %d",(*game).ballX, i);
   }

    deleteCharacter((*game).oldBallY,(*game).oldBallX);
	drawBall((*game).ballY,(*game).ballX);

  }
  /*------------------------------Striker position------------------------------------------*/
  if((readkey() & 0x08) == 0 && (*game).strikerCenter > 9){
     (*game).strikerCenter--;
	   deleteCharacter((*game).height, (*game).strikerCenter+8);
  } else if((readkey() & 0x80) == 0 && (*game).strikerCenter < (*game).length*3-7){
     (*game).strikerCenter++;
     deleteCharacter((*game).height, (*game).strikerCenter-8);
  }

  drawStriker((*game).strikerCenter, (*game).height);
}

void releaseBall(struct positions *game){
  int i,test;
  (*game).ballAngle = 64;
  test = (cos((*game).ballAngle)/sin((*game).ballAngle));
  printf("%d",test);
  (*game).ballY = (*game).height - 1;
  (*game).ballX = ((*game).length*3)/2;
  (*game).speedY = 0;
  drawBall((*game).ballY,(*game).ballX);
  for(i = -7; i <= 7; i++){
      deleteCharacter((*game).height, (*game).strikerCenter-i);
  }
  (*game).strikerCenter = (*game).length*3/2;
  drawStriker((*game).strikerCenter, (*game).height);
  while(1){
     if((readkey() & 0x40)==0){
       (*game).speedY = -1;
	   break;
     }
  }
}
