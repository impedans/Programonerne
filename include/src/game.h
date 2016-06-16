#ifndef _GAME_H
#define _GAME_H
#define XMAX 50
#define YMAX 50

struct positions{
  int length;
  short lives;
  int points;
  short level;
  int height;
  int ballX;
  int ballY;
  long speedX;
  long speedY;
  long vectorX;
  long vectorY;
  short numBlocks;
  short blockLength;
  short blockHeight;
  int ballAngle;
  int strikerCenter;
  short block[20][3];
};


void gameInitial(struct positions *game);
void nextPosition(struct positions *game, int BallTime);
void releaseBall(struct positions *game);


#endif
