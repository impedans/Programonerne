#define BuzzerPin 9

#define tone_a0 220
#define tone_b0 246

#define tone_c 261
#define tone_cs 277
#define tone_d 294
#define tone_ds 311
#define tone_e 330
#define tone_f 349
#define tone_fs 370
#define tone_g 392
#define tone_gs 415
#define tone_a 440
#define tone_as 466
#define tone_b 493

#define tone_c2 522
#define tone_cs2 554
#define tone_d2 588
#define tone_ds2 622
#define tone_e2 660
#define tone_f2 698
#define tone_fs2 740
#define tone_g2 784
#define tone_gs2 824
#define tone_a2 880
#define tone_as2 932
#define tone_b2 988



void mexicoWins() {
  tone(BuzzerPin, tone_c2);
  delay(166);
  tone(BuzzerPin, tone_b);
  delay(166);
  tone(BuzzerPin, tone_c2);
  delay(166);
  tone(BuzzerPin, tone_a);
  delay(166);
  tone(BuzzerPin, tone_gs);
  delay(166);
  tone(BuzzerPin, tone_a);
  delay(166);
  tone(BuzzerPin, tone_f);
  delay(166);
  tone(BuzzerPin, tone_e);
  delay(166);
  tone(BuzzerPin, tone_f);
  delay(166);
  tone(BuzzerPin, tone_c);
  delay(498);

  tone(BuzzerPin, tone_a0);
  delay(166);
  tone(BuzzerPin, tone_b0);
  delay(166);
  tone(BuzzerPin, tone_c);
  delay(166);
  tone(BuzzerPin, tone_d);
  delay(166);
  tone(BuzzerPin, tone_e);
  delay(166);
  tone(BuzzerPin, tone_f);
  delay(166);
  tone(BuzzerPin, tone_g);
  delay(166);
  tone(BuzzerPin, tone_a);
  delay(166);
  tone(BuzzerPin, tone_as);
  delay(166);
  tone(BuzzerPin, tone_g);
  delay(498);

  tone(BuzzerPin, tone_as);
  delay(166);
  tone(BuzzerPin, tone_a);
  delay(166);
  tone(BuzzerPin, tone_as);
  delay(166);
  tone(BuzzerPin, tone_g);
  delay(166);
  tone(BuzzerPin, tone_fs);
  delay(166);
  tone(BuzzerPin, tone_g);
  delay(166);
  tone(BuzzerPin, tone_e);
  delay(166);
  tone(BuzzerPin, tone_ds);
  delay(166);
  tone(BuzzerPin, tone_e);
  delay(166);
  tone(BuzzerPin, tone_c);
  delay(498);

  tone(BuzzerPin, tone_c2);
  delay(125);
  noTone(BuzzerPin);
  delay(41);
  tone(BuzzerPin, tone_c2);
  delay(125);
  noTone(BuzzerPin);
  delay(41);
  tone(BuzzerPin, tone_c2);
  delay(125);
  noTone(BuzzerPin);
  delay(41);
  tone(BuzzerPin, tone_d2);
  delay(166);
  tone(BuzzerPin, tone_c2);
  delay(166);
  tone(BuzzerPin, tone_as);
  delay(166);
  tone(BuzzerPin, tone_a);
  delay(166);
  tone(BuzzerPin, tone_g);
  delay(166);
  tone(BuzzerPin, tone_f);
  delay(498);

  noTone(BuzzerPin);

  delay(2500);
}

void hitBlock(){
  tone(BuzzerPin, tone_c);
  delay(35);
  tone(BuzzerPin, tone_g);
  delay(35);
  noTone(BuzzerPin);
}

void releaseBall(){
  tone(BuzzerPin, tone_c2);
  delay(25);
  tone(BuzzerPin, tone_f);
  delay(25);
  tone(BuzzerPin, tone_c);
  delay(25);
  tone(BuzzerPin, tone_f);
  delay(25);
  tone(BuzzerPin, tone_c2);
  delay(25);
  noTone(BuzzerPin);
}

void hitWall(){
  tone(BuzzerPin, tone_e);
  delay(25);
  noTone(BuzzerPin);
  delay(25);
  tone(BuzzerPin, tone_e);
  delay(25);
  noTone(BuzzerPin);
  
}

void setup() {
  pinMode(BuzzerPin, OUTPUT);
  hitWall();
  delay(500);
  hitBlock();
  delay(500);
  releaseBall();
  delay(500);
  hitWall();
  mexicoWins();
}


void loop() {
  // Tjek for 3.3Vish input her på forskellige porte.
    //mexicoWins();
  
}
