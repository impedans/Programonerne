#include <stdio>;

struct vector{
  int x;
  int y;
};

int cells[xMAX][yMAX][2]; //x, y, life/type

struct vector v;

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

int angleCalc(int s, int v.x, int v.y){
    int vinkel, v.x, v.y;

    if(s==0){
      v.x=0;,
      v.y=1;
    }else if(s==1){
      v.x=1;
      v.y=0;
    }else {
      //error
    }

    vinkel = (180-arccos((v.x*v.x+v.y*v.y)/sqrt(pow(v.x,2)+pow(v.x,2))))/2;//udgangsvinklen af bolden

    return vinkel;
}

int newVector(){//ny vektor efter den har ramt en væg eller blok
  int a, b;

  a=sqrt(pow(v.x,2)+pow(v.y,2))*cos(vinkel);
  b=sqrt(pow(v.x,2)+pow(v.y,2))*sin(vinkel);

  return a,b;
}

int edge(){
  int s;
  switch (v.x){
      case 0:
        s = 0;
        break;
      case X_MAX:
        s = 0;
        break;
      case default:
        //error
        break;
  }

  switch (v.y){
      case 0:
        killPlayer();
        break;
      case X_MAX:
        s = 0;
        break;
      case default:
        //error
        break;
  }
  return s;
}

void releaseBall(){
  while (1){
    if (PLAYER_INPUT_RELEASE_BUTTON == 1){
      v.x = 1;
      v.y = 1;
      break;
    }
  }
}

void vectorNextCell(){
  /* typer:
  0 = ingenting
  1 = wall
  2 = brick
  3 = striker  */
  (int newX, int newY) = newVector();

  if (cells[newX][newY][1]==0){
    v.x = newX;
    v.y = newY;
  } else if (cells[newX][newY][1]==1){
    //angleCalc
  }else if (cells[newX][newY][1]==2){
    /*cells[newX][newY][0]--;
    alive??
    angleCalc
    */
  } else if (cells[newX][newY][1]==3){
    strikeCalc();
  } else {
    killPlayer();
  }

}

void killPlayer(){

}
