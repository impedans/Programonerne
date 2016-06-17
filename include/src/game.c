#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "game.h"
#include "ansi.h"
#include "gpio.h"
#include "lut.h"


void gameInitial(struct positions *game){
  short i = 0, j = 0;
  int length = (*game).length * 3;
  int height = (*game).height;

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
  (*game).ballAngle = 0;

  drawBall((*game).ballX,(*game).ballY);

  //set amount of lives, write info text
  (*game).lives = 3;                      //Set lives
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
  color(15,0);											//SW(TOP bounce ~ side igennem)    SE virker    NE god men sletter     NW sletter

  // draw Blocks
  (*game).blockHeight = 3;
  (*game).blockLength = 3;
  if((*game).level == 1){
    //Level 1//
	  (*game).numBlocks = 17;
    for(i = 0; i < (*game).numBlocks; i++){
      (*game).block[i][2] = 3;
    }
    drawBlock(3, 3 ,0 ,game);
    drawBlock(9, 9 ,1 ,game);
    drawBlock(18, 18 ,2 ,game);
    drawBlock(30, 30 ,3 ,game);
    drawBlock(30, 50 ,4 ,game);
    drawBlock(30, 60 ,5 ,game);
	drawBlock(30, 100 ,6 ,game);
    drawBlock(40, 120 ,7 ,game);
	drawBlock(40, 130 ,8 ,game);
	drawBlock(20, 73 ,9 ,game);
	drawBlock(20, 90 ,10 ,game);
	drawBlock(20, 60 ,11 ,game);
	drawBlock(10, 140 ,12 ,game);
	drawBlock(15, 30 ,13 ,game);
	drawBlock(20, 50 ,14 ,game);
	drawBlock(20, 10 ,15 ,game);
	drawBlock(40, 120 ,16 ,game);
	drawBlock(20, 135 ,17 ,game);
	}

}

void nextPosition(struct positions *game, int BallTime){
  short i = 0, j = 0, l = 0, v = 0;
  int angleLimit = 512;
  /*------------------------------Ball position------------------------------------------*/
  if(BallTime == 1){
	(*game).ballX = (*game).ballX >> 4;
	(*game).ballY = (*game).ballY >> 4;
	deleteCharacter((*game).ballX,(*game).ballY);
	if((*game).speedX > 0 && (*game).speedY > 0){         //SE
  for(i = 0; i < (*game).numBlocks; i++){//For loop runs through blocks
    for(j = 0; j < (*game).blockLength; j++){
      if((*game).ballY + 1 == (*game).block[i][1] + j && (*game).ballX + 1 == (*game).block[i][0]){
        v++;
      }
	}
	for(j = 0; j < (*game).blockHeight; j++){					//Ready if blockHeight != blockLength
      if((*game).ballX + 1 == (*game).block[i][0] + j && (*game).ballY + 1 == (*game).block[i][1]){
        l++;
      }
	}
		
		
      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
  }
} else if((*game).speedX < 0 && (*game).speedY > 0) { //NE
  for( i = 0; i < (*game).numBlocks; i++){
    for(j = 0; j < (*game).blockLength; j++){
      if((*game).ballY + 1 == (*game).block[i][1] + j && (*game).ballX - 1 == (*game).block[i][0] + (*game).blockHeight-1){
        v++;
      }
	}
	for(j = 0; j < (*game).blockHeight; j++){					//Ready if blockHeight != blockLength
      if((*game).ballX - 1 == (*game).block[i][0] + j && (*game).ballY + 1 == (*game).block[i][1]){
        l++;
      }
	}


      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
  }

} else if((*game).speedX > 0 && (*game).speedY < 0){  						//SW

  for( i = 0; i < (*game).numBlocks; i++){
    for (j = 0; j < (*game).blockLength; j++){
      if((*game).ballY - 1 == (*game).block[i][1] + j && ((*game).ballX + 1 == (*game).block[i][0])){
        v++;
	  	//gotoxy(0,0);
		//printf("v: %d", v);
      }
    }
	for(j = 0; j < (*game).blockHeight; j++){					//Ready if blockHeight != blockLength
        if((*game).ballX + 1 == (*game).block[i][0] + j && (*game).ballY - 1 == ((*game).block[i][1] + (*game).blockLength-1)){
          l++;
		 // gotoxy(0,7);
		 // printf("l: %d", l);
        }
	}
  

      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
}

} else if ((*game).speedX < 0 && (*game).speedY < 0) {                                              //NW
  for( i = 0; i < (*game).numBlocks; i++){
    for (j = 0; j < (*game).blockLength; j++){
      if((*game).ballY - 1 == (*game).block[i][1] + j && (*game).ballX - 1 == (*game).block[i][0] + (*game).blockHeight-1){
        v++;
      }
	}
	for(j = 0; j < (*game).blockHeight; j++){					//Ready if blockHeight != blockLength
      if((*game).ballX - 1 == (*game).block[i][0] + j && (*game).ballY - 1 == (*game).block[i][1] + (*game).blockLength-1){
        l++;
      }
	}
      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
  }
} else if ((*game).speedX < 0 && (*game).speedY == 0){                                                                                      // North
  for (i = 0; i < (*game).numBlocks; i++){
    for (j = 0; j < (*game).blockHeight; j++){
      if((*game).ballY - 1 == (*game).block[i][1] + j && (*game).ballX == (*game).block[i][0] + (*game).blockHeight-1){
        v++;
      }
    }

      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
  }

} else {
  for (i = 0; i < (*game).numBlocks; i++){                                                                         //South
    for (j = 0; j < (*game).blockLength; j++){
      if((*game).ballY + 1 == (*game).block[i][1] + j && (*game).ballX == (*game).block[i][0]){
        v++;
      }

      if(l == v && l > 0){
        (*game).speedX *= -1;
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (l > v){
        (*game).speedY *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      } else if (v > l){
        (*game).speedX *= -1;
        (*game).block[i][2]--;
        drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
      }
	  l = 0, v = 0;
    }
  }
}
	(*game).ballX = (*game).ballX << 4;
	(*game).ballY = (*game).ballY << 4;
    //deleteCharacter((*game).ballX  >> 2,(*game).ballY  >> 2);
	//initVector(game,(*game).ballAngle);
  	(*game).ballX = (*game).ballX + (*game).speedX ;
    (*game).ballY = (*game).ballY + (*game).speedY ;
	//printf("Anfdfnn %d . %d   :    ", (*game).ballX >> 2, (*game).ballY >> 2);
	//printf("Anfdfnn %d . %d   :    ", (*game).speedX >> 2, (*game).speedY >> 2);
    //(*game).ballAngle = 0;

    if(((*game).ballX >> 4) <= 1){													                  //Hit top
       (*game).speedX *= -1;
       (*game).ballX = 2 << 4;                                             //EDIT: returns ball to fiels
    }

    if (((*game).ballY >> 4) <= 1 || ((*game).ballY >> 4) >= (*game).length*3){		//Hit sides (EDIT: runs every time)
       (*game).speedY *= -1;
       if(((*game).ballY >> 4) <= 1){                                        //EDIT: if/else that returns ball to field
         (*game).ballY = 2 << 4;
       } else {
         (*game).ballY = (*game).length*3-1 << 4;
       }

    }

    if (((*game).ballX >> 4) == (*game).height-1 && (((*game).ballY >> 4) > (*game).strikerCenter-8 && ((*game).ballY >> 4) < (*game).strikerCenter+8)){
		if(((*game).ballY >> 4) > (*game).strikerCenter-1 && ((*game).ballY >> 4) < (*game).strikerCenter+1){
          (*game).speedX *= -1;
		  //(*game).speedY *= -1;
		  //(*game).vectorX *= -1;

		} else if (((*game).ballY >> 4) > (*game).strikerCenter-4 && ((*game).ballY >> 4) < (*game).strikerCenter-1){
          (*game).speedX *= -1;
		  //(*game).vectorX *= -1;
        //if((*game).ballAngle > -angleLimit){
		   // initVector(game,-10);                            // her er lavet om !!!!!

        //}
		} else if (((*game).ballY >> 4) > (*game).strikerCenter+1 && ((*game).ballY >> 4) < (*game).strikerCenter+4){
          (*game).speedX *= -1;
		  //(*game).speedY *= -1;
		  //(*game).vectorX *= -1;
        //if((*game).ballAngle < angleLimit){
          //  initVector(game,10);                            // her er lavet om !!!!!

        //}

		} else if (((*game).ballY >> 4) > (*game).strikerCenter-8 && ((*game).ballY >> 4) < (*game).strikerCenter-4){
          (*game).speedX *= -1;
		  //(*game).speedY *= -1;
		  //(*game).vectorX *= -1;
   //   if((*game).ballAngle > -angleLimit){
         // initVector(game,-10);                            // her er lavet om !!!!!

   //   }

		} else {
		  (*game).speedX *= -1;
		  //(*game).speedY *= -1;
		  //(*game).vectorX *= -1;
   //       if((*game).ballAngle > angleLimit){
           // initVector(game,10);                            // her er lavet om !!!!!

     //     }
		}

    }else if(((*game).ballX >> 4) >= (*game).height){																//Out of bounds
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
     //printf("BNnjnfjsdf  %d . %d", (*game).ballX >> 2, (*game).ballY >> 2);
     drawBall(((*game).ballX) >> 4,((*game).ballY) >> 4);
	// gotoxy(0,0);
    // printf("Venn: %d %d", (*game).ballX, (*game).ballY);
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
  (*game).ballX = (*game).ballX << 4;
  (*game).ballY = (*game).ballY << 4;
 // printf("%d . %d", (*game).ballX >> 4, (*game).ballY >> 4);

  for(i = -7; i <= 7; i++){
      deleteCharacter((*game).height, (*game).strikerCenter-i);   //Deletes old striker
  }
  (*game).strikerCenter = (*game).length*3/2;                     //Draws new striker
  drawStriker((*game).strikerCenter, (*game).height);

  while(1){                                                       //Restarts game
     if((readkey() & 0x40)==0){
       (*game).speedX = -1 << 4;
       (*game).speedY = -1 << 4;
	   (*game).vectorX = -1;
       (*game).vectorY = -1;
	   break;
     }
  }
}
