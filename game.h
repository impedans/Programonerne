#ifndef _GAME_H
#define _GAME_H
#define XMAX 50
#define YMAX 50

struct positions{
  int length;
  int height;
  int ballX;
  int ballY;
  int speedX;
  int speedY;
  int ballAngle;
  int strikerCenter;
};


void gameInitial(struct positions *game);
void nextPosition(struct positions *game, int BallTime);
void releaseBall(struct positions *game);


#endif
