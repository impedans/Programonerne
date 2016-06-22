
#ifndef _GAME_H
#define _GAME_H
#define XMAX 50
#define YMAX 50

struct positions{
	char block[100][3];
	char lives;
	char level;

	int points;
	int ballAngle;
	int strikerCenter;
	int difficultyBall;
	int difficultyStriker;

	short height;
	short length;
	short ballX;
	short ballY;
	short oldBallX;
	short oldBallY;
	short speedX;
	short speedY;
	short hitTest;
	short numBlocks;
	short blockLength;
	short blockHeight;
	short pointBonus;
};


void gameInitial(struct positions *game);
void nextPosition(struct positions *game, short ballTime);
void releaseBall(struct positions *game);
void deflectionChecker(struct positions *game, short l, short v, short i);
void difficultyMenu(struct positions *game);


#endif
