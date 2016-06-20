#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "game.h"

#ifndef GAME_C
#define GAME_C

void gameInitial(struct positions *game){
	short i = 0, j = 0;
	int length = (*game).length * 3;
	int height = (*game).height;

	cleanscreen();

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
	drawBall((*game).ballX,(*game).ballY);

	//set amount of lives, write info text
	gotoxy(55,10);
	printf("Lives: ");
	(*game).lives = 3;
	//(*game).points = 0;
	gotoxy(56,10);
	printf("Points: ");
	//(*game).level = 1;
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
	(*game).blockHeight = 3;
	(*game).blockLength = 13;
	if((*game).level == 1){
		//Level 1//
		(*game).numBlocks = 8;
		for(i = 0; i < 8; i++){
			(*game).block[i][2] = 3;
		}
		/*for(i = 8; i < 16; i++){
			(*game).block[i][2] = 2;
		}
		for(i = 16; i < 24; i++){
			(*game).block[i][2] = 1;
		}*/
		drawBlock(5, 15 ,0 ,game);
		drawBlock(5, 31 ,1 ,game);
		drawBlock(5, 47 ,2 ,game);
		drawBlock(5, 63 ,3 ,game);
		drawBlock(5, 79 ,4 ,game);
		drawBlock(5, 95 ,5 ,game);
		drawBlock(5, 111 ,6 ,game);
		drawBlock(5, 127 ,7 ,game);

	/*	drawBlock(10, 15 ,8 ,game);
		drawBlock(10, 31 ,9 ,game);
		drawBlock(10, 47 ,10 ,game);
		drawBlock(10, 63 ,11 ,game);
		drawBlock(10, 79 ,12 ,game);
		drawBlock(10, 95 ,13 ,game);
		drawBlock(10, 111 ,14 ,game);
		drawBlock(10, 127 ,15 ,game);

		drawBlock(15, 15 ,16 ,game);
		drawBlock(15, 31 ,17 ,game);
		drawBlock(15, 47 ,18 ,game);
		drawBlock(15, 63 ,19 ,game);
		drawBlock(15, 79 ,20 ,game);
		drawBlock(15, 95 ,21 ,game);
		drawBlock(15, 111 ,22 ,game);
		drawBlock(15, 127 ,23 ,game);*/
	}

}

void nextPosition(struct positions *game, int BallTime){
	short i = 0, j = 0, l = 0, v = 0;
  
	//gotoxy(0,0);																								//testing area
	//printf("%d   :    %d    :    %d                   ",(*game).speedX,(*game).speedY,(*game).ballAngle);
  
	if(BallTime == 1){

/*----------------------------------------------Ball position---------------------------------------------------------*/
	  
		(*game).oldBallX = (*game).ballX >> 4;						//save old ball position
		(*game).oldBallY = (*game).ballY >> 4;

		(*game).ballX += (*game).speedX >> 10;				//set new ball position
		(*game).ballY += (*game).speedY >> 10;
	
/*---------------------------------------------Block Tester SE--------------------------------------------------------*/
	
		if((*game).speedX > 0 && (*game).speedY > 0){         
			for(i = 0; i < (*game).numBlocks; i++){//For loop runs through blocks
				for(j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && ((*game).ballX >> 4) == (*game).block[i][0]){
						v++;
					}
				}
				for(j = 0; j < (*game).blockHeight; j++){					
					if(((*game).ballX >> 4) == (*game).block[i][0] + j && ((*game).ballY >> 4) == (*game).block[i][1]){
						l++;
					}
				}
				if(l == v && l > 0){
				
					(*game).ballAngle = 256 + (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;

					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (l > v){
				
					(*game).ballAngle = 512 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest = 1;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (v > l){
				
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;

					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
				l = 0, v = 0;
			}
		
/*---------------------------------------------Block Tester NE--------------------------------------------------------*/		
		
		} else if((*game).speedX < 0 && (*game).speedY > 0) { 
			for( i = 0; i < (*game).numBlocks; i++){
				for(j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && ((*game).ballX >> 4) == (*game).block[i][0] + (*game).blockHeight-1){
						v++;
					}
				}
				for(j = 0; j < (*game).blockHeight; j++){					
					if(((*game).ballX >> 4) == (*game).block[i][0] + j && ((*game).ballY >> 4) == (*game).block[i][1]){
						l++;
					}
				}
				if(l == v && l > 0){
					
					(*game).ballAngle = 256 + (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (l > v){
					
					(*game).ballAngle = 512 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (v > l){
					
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
				l = 0, v = 0;
			}

	/*---------------------------------------------Block Tester SW--------------------------------------------------------*/		
			
		} else if((*game).speedX > 0 && (*game).speedY < 0){  						

			for( i = 0; i < (*game).numBlocks; i++){
				for (j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && (((*game).ballX >> 4) == (*game).block[i][0])){
						v++;
						//gotoxy(0,0);
						//printf("v: %d", v);
					}
				}
				for(j = 0; j < (*game).blockHeight; j++){					
					if(((*game).ballX >> 4) == (*game).block[i][0] + j && ((*game).ballY >> 4) == ((*game).block[i][1] + (*game).blockLength-1)){
						l++;
						// gotoxy(0,7);
						// printf("l: %d", l);
					}
				}
				if(l == v && l > 0){
					
					(*game).ballAngle = 256 + (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (l > v){
					
					(*game).ballAngle = 512 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (v > l){
					
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
				l = 0, v = 0;
			}
			
	/*---------------------------------------------Block Tester NW--------------------------------------------------------*/		
			
		} else if ((*game).speedX < 0 && (*game).speedY < 0) {                                              
			for( i = 0; i < (*game).numBlocks; i++){
				for (j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && ((*game).ballX >> 4) == (*game).block[i][0] + (*game).blockHeight-1){
						v++;
					}
				}
				for(j = 0; j < (*game).blockHeight; j++){					
					if(((*game).ballX >> 4) == (*game).block[i][0] + j && ((*game).ballY >> 4) == (*game).block[i][1] + (*game).blockLength-1){
						l++;
					}
				}
				if(l == v && l > 0){
					
					(*game).ballAngle = 256 + (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (l > v){
					
					(*game).ballAngle = 512 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballY     = (*game).oldBallY << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (v > l){
					
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
				l = 0, v = 0;
			}
			
	/*---------------------------------------------Block Tester North-----------------------------------------------------*/		
			
		} else if ((*game).speedX < 0 && (*game).speedY == 0){                                                                                      
			for (i = 0; i < (*game).numBlocks; i++){
				for (j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && ((*game).ballX >> 4) == (*game).block[i][0] + (*game).blockHeight){
						v++;
					}
				}

				if (v > 0){
					
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					PEOUT = 0x08;
					PEOUT &= 0x00;
					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
				l = 0, v = 0;
			}
			
	/*---------------------------------------------Block Tester South-----------------------------------------------------*/		
			
		} else {
			for (i = 0; i < (*game).numBlocks; i++){                                                                         //South
				for (j = 0; j < (*game).blockLength; j++){
					if(((*game).ballY >> 4) == (*game).block[i][1] + j && ((*game).ballX >> 4) == (*game).block[i][0] - 1){
						v++;
					}
					
					if (v > 0){
					
						(*game).ballAngle = 256 - (*game).ballAngle;	   
						(*game).ballAngle =(*game).ballAngle & 511;
						(*game).hitTest   = 1;
						(*game).ballX     = (*game).oldBallX << 4;
						PEOUT = 0x08;
						PEOUT &= 0x00;
					
						(*game).block[i][2]--;
						drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
					}
					l = 0, v = 0;
				}
			}
		}
			
	/*---------------------------------------------Wall Tester---------------------------------------------------------*/	
		if(((*game).ballX >> 4) <= 1){					//Hit top
			PEOUT = 0x04;
			PEOUT &= 0x00;
			(*game).ballAngle = 256 - (*game).ballAngle;	   
			(*game).ballAngle =(*game).ballAngle & 511;
			(*game).ballX = 2 << 4;                       //Returns ball to fiels
			(*game).hitTest = 1;
		}
		
		if (((*game).ballY >> 4) <= 1 || ((*game).ballY >> 4) >= (*game).length*3){		//Hit sides 
	    	PEOUT = 0x04;
			PEOUT &= 0x00;
			(*game).ballAngle = 512 - (*game).ballAngle;	  
			(*game).ballAngle =(*game).ballAngle & 511;
			if(((*game).ballY >> 4) <= 1){                                        //if/else that returns ball to field
				(*game).ballY = 2 << 4;
			 
			} else {
				(*game).ballY = (*game).length*3-1 << 4;
			}
				(*game).hitTest = 1;
		}

	/*---------------------------------------------Striker Tester------------------------------------------------------*/
		
		if (((*game).ballX >> 4) == (*game).height-1 && (((*game).ballY >> 4) > (*game).strikerCenter-8 && ((*game).ballY >> 4) < (*game).strikerCenter+8)){  //Striker tester
			PEOUT = 0x10;
			PEOUT &= 0x00;
			if(((*game).ballY >> 4) > (*game).strikerCenter-1 && ((*game).ballY >> 4) < (*game).strikerCenter+1){				//Striker middle field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).hitTest = 1;
		  


			} else if (((*game).ballY >> 4) > (*game).strikerCenter-4 && ((*game).ballY >> 4) < (*game).strikerCenter-1){		//Striker inner left field

				(*game).ballAngle = 256 - (*game).ballAngle;		// turn ball
				(*game).ballAngle =(*game).ballAngle & 511;		// repair angle
	
				if(((*game).ballAngle+24)<374){
					(*game).ballAngle =(*game).ballAngle + 24;			// add to angle if the result will be inside the max angle range
				}
				(*game).hitTest = 1;	 							// set hitTest to 1
			  
			} else if (((*game).ballY >> 4) > (*game).strikerCenter+1 && ((*game).ballY >> 4) < (*game).strikerCenter+3){		//Striker inner right field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;
	
				if(((*game).ballAngle-24)<374){
					(*game).ballAngle =(*game).ballAngle - 24;			
				}
				(*game).hitTest = 1;
			  
			} else if (((*game).ballY >> 4) > (*game).strikerCenter-8 && ((*game).ballY >> 4) < (*game).strikerCenter-3){		//Striker outer left field 
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;
				(*game).ballAngle =(*game).ballAngle + 24;
				if(((*game).ballAngle+24)<374){
					(*game).ballAngle =(*game).ballAngle + 24;			
				}
				(*game).hitTest = 1;
			  
			} else {																											//Striker outer right field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;

				if(((*game).ballAngle-24)<374){
					(*game).ballAngle =(*game).ballAngle - 24;			
				}
				(*game).hitTest = 1;
			}

	/*---------------------------------------------Death Tester------------------------------------------------------*/

		}else if(((*game).ballX >> 4) >= (*game).height){						//Out of bounds
			(*game).lives--;
			drawFlag((*game).lives);
			drawInfo(game);
			if ((*game).lives == 0){
				for(i = -7; i <= 7; i++){
					deleteCharacter((*game).height, (*game).strikerCenter-i);
				}
				gotoxy(55, 50);
				printf("Mexico triumpfed. Press right button to restart");
				(*game).points = 0;
				PEOUT = 0x02;
				while(1){
					if((readkey() & 0x80)==0){
						for(i=0; i <= 46; i++){
							deleteCharacter(55, 50+i);
							PEOUT &= 0x00;
						}
						break;
					}
				}
				gameInitial(game);
			} else {
				PEOUT = 0x30;
				PEOUT &= 0x00;
			}
			releaseBall(game);
		}

	/*---------------------------------------------New ball position--------------------------------------------------*/

		if((*game).hitTest == 1){						//runs if hit test is 1 and changes speedX and speedY
			(*game).ballAngle =(*game).ballAngle & 511;	
			(*game).speedX = cosinus((*game).ballAngle);
			(*game).speedY = sinus((*game).ballAngle);
			(*game).hitTest = 0;
		}
		deleteCharacter((*game).oldBallX,(*game).oldBallY);         //deletes old ball and draws new one
		drawBall(((*game).ballX) >> 4,((*game).ballY) >> 4);
	}

  /*-------------------------------------------Striker position---------------------------------------------------*/
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

	for(i = -7; i <= 7; i++){
		deleteCharacter((*game).height, (*game).strikerCenter-i);   //Deletes old striker
	}
	(*game).strikerCenter = (*game).length*3/2;                     //Draws new striker
	drawStriker((*game).strikerCenter, (*game).height);

	while(1){                                                       //Restarts game
		if((readkey() & 0x40)==0){
			(*game).ballAngle = 256;   					//start angle
			(*game).speedX = cosinus((*game).ballAngle);
			(*game).speedY = sinus((*game).ballAngle);
		break;
		}
	}
}

#endif

