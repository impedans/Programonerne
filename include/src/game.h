
#ifndef _GAME_H
#define _GAME_H
#define XMAX 50
#define YMAX 50

struct positions{
	int length;
	int lives;
	int points;
	int level;
	int height;
	short ballX;
	short ballY;
	short oldBallX;
	short oldBallY;
	short speedX;
	short speedY;
	short hitTest;
	int ballAngle;
	int strikerCenter;
	short numBlocks;
	short blockLength;
	short blockHeight;
	char block[100][3];
};


void gameInitial(struct positions *game);
void nextPosition(struct positions *game, int BallTime);
void releaseBall(struct positions *game);
void mate(struct positions *game, short l, short v, short i);


#endif
