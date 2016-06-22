#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "lut.h"
#include "ansi.h"
#include "gpio.h"
#include "game.h"


void gameInitial(struct positions *game){
	short i = 0, j = 0;
	int length = (*game).length * 3;
	int height = (*game).height;

	cleanscreen();
	difficultyMenu(game);

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
	(*game).blockHeight = 2;
	(*game).blockLength = 4;
	if((*game).level == 1){
		//Level 1//
		(*game).numBlocks = 42;
		for(i = 0; i < 14; i++){
			(*game).block[i][2] = 3;
		}
		for(i = 14; i < 28; i++){
			(*game).block[i][2] = 2;
		}
		for(i = 28; i < (*game).numBlocks; i++){
			(*game).block[i][2] = 1;
		}
		drawBlock(5, 4 ,0 ,game);
		drawBlock(5, 9 ,1 ,game);
		drawBlock(5, 14 ,2 ,game);
		drawBlock(5, 19 ,3 ,game);
		drawBlock(5, 24 ,4 ,game);
		drawBlock(5, 29 ,5 ,game);
		drawBlock(5, 34 ,6 ,game);
		drawBlock(5, 39 ,7 ,game);
		drawBlock(5, 44 ,8 ,game);
		drawBlock(5, 49 ,9 ,game);
		drawBlock(5, 54 ,10 ,game);
		drawBlock(5, 59 ,11 ,game);
		drawBlock(5, 64 ,12 ,game);
		drawBlock(5, 69 ,13 ,game);	

		drawBlock(10, 4 ,14 ,game);
		drawBlock(10, 9 ,15 ,game);
		drawBlock(10, 14 ,16 ,game);
		drawBlock(10, 19 ,17 ,game);
		drawBlock(10, 24 ,18 ,game);
		drawBlock(10, 29 ,19 ,game);
		drawBlock(10, 34 ,20 ,game);
		drawBlock(10, 39 ,21 ,game);
		drawBlock(10, 44 ,22 ,game);
		drawBlock(10, 49 ,23 ,game);
		drawBlock(10, 54 ,24 ,game);
		drawBlock(10, 59 ,25 ,game);
		drawBlock(10, 64 ,26 ,game);
		drawBlock(10, 69 ,27 ,game);

		drawBlock(15, 4 , 28 ,game);
		drawBlock(15, 9 ,29 ,game);
		drawBlock(15, 14 ,30 ,game);
		drawBlock(15, 19 ,31 ,game);
		drawBlock(15, 24 ,32 ,game);
		drawBlock(15, 29 ,33 ,game);
		drawBlock(15, 34 ,34 ,game);
		drawBlock(15, 39 ,35 ,game);
		drawBlock(15, 44 ,36 ,game);
		drawBlock(15, 49 ,37 ,game);
		drawBlock(15, 54 ,38 ,game);
		drawBlock(15, 59 ,39 ,game);
		drawBlock(15, 64 ,40 ,game);
		drawBlock(15, 69 ,41 ,game);
	} else if ((*game).level == 2){
		(*game).numBlocks = 38;
		for(i = 0; i < 28; i++){
			(*game).block[i][2] = 3;
		}
		for(i = 28; i < 30; i++){
			(*game).block[i][2] = 2;
		}
		for(i = 30; i < (*game).numBlocks; i++){
			(*game).block[i][2] = 1;
		}

		drawBlock(2, 14 ,0 ,game);
		drawBlock(5, 14 ,1 ,game);
		drawBlock(8, 14 ,2 ,game);
		drawBlock(11, 14 ,3 ,game);
		drawBlock(14, 14 ,4 ,game);
		drawBlock(17, 14 ,5 ,game);

		drawBlock(2, 59 ,6 ,game);
		drawBlock(5, 59 ,7 ,game);
		drawBlock(8, 59 ,8 ,game);
		drawBlock(11, 59 ,9 ,game);
		drawBlock(14, 59 ,10 ,game);
		drawBlock(17, 59 ,11 ,game);

		drawBlock(2, 19 ,12 ,game);
		drawBlock(2, 24 ,13 ,game);
		drawBlock(2, 29 ,14 ,game);
		drawBlock(2, 34 ,15 ,game);
		drawBlock(2, 39 ,16 ,game);
		drawBlock(2, 44 ,17 ,game);
		drawBlock(2, 49 ,18 ,game);
		drawBlock(2, 54 ,19 ,game);

		drawBlock(17, 19 ,20 ,game);
		drawBlock(17, 24 ,21 ,game);
		drawBlock(17, 29 ,22 ,game);
		drawBlock(17, 34 ,23 ,game);
		drawBlock(17, 39 ,24 ,game);
		drawBlock(17, 44 ,25 ,game);
		drawBlock(17, 49 ,26 ,game);
		drawBlock(17, 54 ,27 ,game);

		drawBlock(5, 27 ,28 ,game);
		drawBlock(5, 46 ,29 ,game);

		drawBlock(14, 24 ,30 ,game);
		drawBlock(14, 29 ,31 ,game);
		drawBlock(14, 34 ,32 ,game);
		drawBlock(14, 39 ,33 ,game);
		drawBlock(14, 44 ,34 ,game);
		drawBlock(14, 49 ,35 ,game);
		drawBlock(12, 49 ,36 ,game);
		drawBlock(12, 24 ,37 ,game);


	} else if((*game).level == 3){
		//Level 3//
		(*game).numBlocks = 57;

		for(i = 0; i < (*game).numBlocks; i++){
			(*game).block[i][2] = 3;
		}
		drawBlock(5, 2 ,0 ,game);
		drawBlock(5, 6 ,1 ,game);

		drawBlock(7, 2 ,2 ,game);
		drawBlock(7, 6 ,3 ,game);
		drawBlock(7, 10 ,4 ,game);
		drawBlock(7, 14 ,5 ,game);
		drawBlock(7, 18 ,6 ,game);

		drawBlock(9, 2 ,7 ,game);
		drawBlock(9, 6 ,8 ,game);
		drawBlock(9, 10 ,9 ,game);
		drawBlock(9, 14 ,10 ,game);
		drawBlock(9, 18 ,11 ,game);
		drawBlock(9, 22 ,12 ,game);
		drawBlock(9, 26 ,13 ,game);
		drawBlock(9, 30 ,14 ,game);

		drawBlock(11, 2 ,15 ,game);
		drawBlock(11, 6 ,16 ,game);
		drawBlock(11, 10 ,17 ,game);
		drawBlock(11, 14 ,18 ,game);
		drawBlock(11, 18 ,19 ,game);
		drawBlock(11, 22 ,20 ,game);
		drawBlock(11, 26 ,21 ,game);
		drawBlock(11, 30 ,22 ,game);
		drawBlock(11, 34 ,23 ,game);
		drawBlock(11, 38 ,24 ,game);
		drawBlock(11, 42 ,25 ,game);

		drawBlock(13, 2 ,26 ,game);
		drawBlock(13, 6 ,27 ,game);
		drawBlock(13, 10 ,28 ,game);
		drawBlock(13, 14 ,29 ,game);
		drawBlock(13, 18 ,30 ,game);
		drawBlock(13, 22 ,31 ,game);
		drawBlock(13, 26 ,32 ,game);
		drawBlock(13, 30 ,33 ,game);
		drawBlock(13, 34 ,34 ,game);
		drawBlock(13, 38 ,35 ,game);
		drawBlock(13, 42 ,36 ,game);
		drawBlock(13, 46 ,37 ,game);
		drawBlock(13, 50 ,38 ,game);
		drawBlock(13, 54 ,39 ,game);

		drawBlock(15, 2 , 40 ,game);
		drawBlock(15, 6 ,41 ,game);
		drawBlock(15, 10 ,42 ,game);
		drawBlock(15, 14 ,43 ,game);
		drawBlock(15, 18 ,44 ,game);
		drawBlock(15, 22 ,45 ,game);
		drawBlock(15, 26 ,46 ,game);
		drawBlock(15, 30 ,47 ,game);
		drawBlock(15, 34 ,48 ,game);
		drawBlock(15, 38 ,49 ,game);
		drawBlock(15, 42 ,50 ,game);
		drawBlock(15, 46 ,51 ,game);
		drawBlock(15, 50 ,52 ,game);
		drawBlock(15, 54 ,53 ,game);
		drawBlock(15, 58 ,54 ,game);
		drawBlock(15, 62 ,55 ,game);
		drawBlock(15, 66 ,56 ,game);
	}
	//set amount of lives, write info text
	gotoxy(2,79);
	(*game).lives = 3;
	printf("Lives: ");
	//(*game).points = 0;
	gotoxy(3,79);
	printf("Tacos: ");
	//(*game).level = 1;
	gotoxy(4,79);
	printf("Level: ");
	drawInfo(game);

}

void mate(struct positions *game, short l, short v, short i){
	if(l == v && l > 0){
				
					(*game).ballAngle = 256 + (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest   = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					(*game).ballY     = (*game).oldBallY << 4;
					//PEOUT = 0x08;
					PCOUT = 0x08;

					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (l > v){
				
					(*game).ballAngle = 512 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest = 1;
					(*game).ballY     = (*game).oldBallY << 4;
					//PEOUT = 0x08;
					PCOUT = 0x08;

					
					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				} else if (v > l){
				
					(*game).ballAngle = 256 - (*game).ballAngle;	   
					(*game).ballAngle =(*game).ballAngle & 511;
					(*game).hitTest = 1;
					(*game).ballX     = (*game).oldBallX << 4;
					//PEOUT = 0x08;
					PCOUT = 0x08;


					(*game).block[i][2]--;
					drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
				}
}

void nextPosition(struct positions *game, int BallTime){
	short i = 0, j = 0, l = 0, v = 0;
  	//PEOUT &= 0x00;
	PCOUT &= 0x00;
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
				
				mate(game, l, v, i);

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
				mate(game, l, v, i);
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
				mate(game, l, v, i);
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
				mate(game, l, v, i);
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
					//PEOUT = 0x08;
					PCOUT = 0x08;

					
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
						//PEOUT = 0x08;
						PCOUT = 0x08;

					
						(*game).block[i][2]--;
						drawBlock((*game).block[i][0], (*game).block[i][1], i, game);
					}
					l = 0, v = 0;
				}
			}
		}
			
	/*---------------------------------------------Wall Tester---------------------------------------------------------*/	
		if(((*game).ballX >> 4) <= 1){					//Hit top
			//PEOUT = 0x10;
			PCOUT = 0x10;
			
			(*game).ballAngle = 256 - (*game).ballAngle;	   
			(*game).ballAngle =(*game).ballAngle & 511;
			(*game).ballX = 2 << 4;                       //Returns ball to fiels
			(*game).hitTest = 1;
		}
		
		if (((*game).ballY >> 4) <= 1 || ((*game).ballY >> 4) >= (*game).length*3){		//Hit sides 
	    	//PEOUT = 0x10;
			PCOUT = 0x10;
			
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
			//PEOUT = 0x30;
			PCOUT = 0x30;
			(*game).pointBonus = 0;
			drawInfo(game);
			
			if(((*game).ballY >> 4) > (*game).strikerCenter-1 && ((*game).ballY >> 4) < (*game).strikerCenter+1){				//Striker middle field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).hitTest = 1;
		  


			} else if (((*game).ballY >> 4) > (*game).strikerCenter-4 && ((*game).ballY >> 4) < (*game).strikerCenter-1){		//Striker inner left field

				(*game).ballAngle = 256 - (*game).ballAngle;		// turn ball
				(*game).ballAngle =(*game).ballAngle & 511;		// repair angle
	
				if(((*game).ballAngle + 10) > 374){
					(*game).ballAngle = 374;			// add to angle if the result will be inside the max angle range
				}else{
					(*game).ballAngle += 10;
				}
				(*game).hitTest = 1;	 							// set hitTest to 1
			  
			} else if (((*game).ballY >> 4) > (*game).strikerCenter+1 && ((*game).ballY >> 4) < (*game).strikerCenter+3){		//Striker inner right field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;
	
				if(((*game).ballAngle - 10) < 148){
					(*game).ballAngle = 148;			
				}else{
					(*game).ballAngle -= 10;
				}
				(*game).hitTest = 1;
			  
			} else if (((*game).ballY >> 4) > (*game).strikerCenter-8 && ((*game).ballY >> 4) < (*game).strikerCenter-3){		//Striker outer left field 
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;
				(*game).ballAngle =(*game).ballAngle + 24;
				if(((*game).ballAngle + 24) > 374){
					(*game).ballAngle = 374;			
				} else{
					(*game).ballAngle += 24;
				}
				(*game).hitTest = 1;
			  
			} else {																											//Striker outer right field
				(*game).ballAngle = 256 - (*game).ballAngle;
				(*game).ballAngle =(*game).ballAngle & 511;

				if(((*game).ballAngle - 24) < 148){
					(*game).ballAngle = 148;			
				}else{
					(*game).ballAngle -= 24;
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
				gotoxy(20, 79);
				printf("Mexico triumpfed");
				gotoxy(21, 79);
				printf("Press right button to restart");
				(*game).points = 0;
				(*game).lives = 2;
				//PEOUT = 0x04;
				PCOUT = 0x04;
				while(1){
					if((readkey() & 0x80)==0){
						for(i=0; i <= 46; i++){
							deleteCharacter(55, 50+i);
							//PEOUT &= 0x00;
							PCOUT &= 0x00;
						}
						break;
					}
				}
				(*game).level = 1;
				gameInitial(game);
			} else {
				//PEOUT = 0x40;
				PCOUT = 0x40;

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

	//PEOUT &= 0x00;
	PCOUT &= 0x00;
	while(1){                                                       //Restarts game
		if((readkey() & 0x40)==0){
			(*game).ballAngle = 230;   					//start angle
			(*game).speedX = cosinus((*game).ballAngle);
			(*game).speedY = sinus((*game).ballAngle);
		break;
		}
	}
}

void difficultyMenu(struct positions *game){
	cleanscreen();
	gameWindow(1,1,54,18);
	gotoxy(3,5);
	printf("\t\tChoose Mexican difficulty:");
	gotoxy(7,5);
	color(10,0);
	printf("[MAIDS]");
	color(12,0);
	gotoxy(7,17);
	printf("[BEAN BOILERS]");
	gotoxy(8,18);
	printf("+1000 tacos");
	gotoxy(7,37);
	color(1,0);
	printf("[DRUG CARTEL]");
	gotoxy(8,38);
	printf("+5000 tacos");
	gotoxy(11,5);
	color(15,0);
	printf("\t\tUse the buttons to pick");
	while(1){
		if((readkey() & 0x08)==0){ //Easy
			//PEOUT = 0x10;
			PCOUT = 0x10;
			(*game).difficultyBall = 35;
			(*game).difficultyStriker = 10;
			break;
		} else if((readkey() & 0x40)==0){ //Medium
			//PEOUT = 0x20;
			PCOUT = 0x20;
			(*game).difficultyBall = 25;
			(*game).difficultyStriker = 7;
			(*game).points += 1000;			
			break;
		} else if((readkey() & 0x80)==0){ //Hard
			//PEOUT = 0x08;
			PCOUT = 0x08;
			(*game).difficultyBall = 20;
			(*game).difficultyStriker = 6;
			(*game).points += 5000;
			break;
		}
	}
	cleanscreen();
}

