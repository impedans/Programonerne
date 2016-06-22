
#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void cleanscreen();
void gotoxy(int x, int y);
void reverse(int bg, int fg);
void window(int x1, int y1, int x2, int y2, int style, char* title);
void gameWindow(int x1, int y1, int x2, int y2);
void drawStriker(int strikerCenter, int height);
void drawBall(int x,int y);
void deleteCharacter(int x,int y);
void drawBlock(int x1, int y1, short N, struct positions *game);
void drawInfo(struct positions *game);
void drawFlag(int lives);

#endif
