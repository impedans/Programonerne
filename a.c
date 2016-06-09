#include <stdio>;

int int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

int angleCalc(int s, int v_v1, intv_v2){
    int vinkel, v_s1, v_s2;

    if(s==0){
      v_s1=0;,
      v_s2=1;
    }else if(s==1){
      v_s1=1;
      v_s2=0;
    }else {
      //error
    }

    vinkel = (180-arccos((v_s1*v_v1+v_s2*v_v2)/sqrt(pow(v_v1,2)+pow(v_v2,2))))/2;//udgangsvinklen af bolden

    return vinkel;
}

int new_vector(){//ny vektor efter den har ramt en væg eller blok
  int a, b;

  a=sqrt(pow(v_v1,2)+pow(v_v2,2))*cos(vinkel);
  b=sqrt(pow(v_v1,2)+pow(v_v2,2))*sin(vinkel);

  return a,b;
}
