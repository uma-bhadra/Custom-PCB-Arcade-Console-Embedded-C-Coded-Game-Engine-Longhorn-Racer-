// Lab9Main.c
// Runs on MSPM0G3507
// Uma Bhadra 
// Last Modified: April 10, 2026

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"

void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

Arabic_t ArabicAlphabet[]={
alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,ta,thaa,twe,waaw,yaa,zaa,space,dot,null
};
Arabic_t Hello[]={alif,baa,ha,raa,meem,null}; // hello
Arabic_t WeAreHonoredByYourPresence[]={alif,noon,waaw,ta,faa,raa,sheen,null}; // we are honored by your presence
int main0(void){ // main 0, demonstrate Arabic output
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  Arabic_SetCursor(0,15);
  Arabic_OutString(Hello);
  Arabic_SetCursor(0,31);
  Arabic_OutString(WeAreHonoredByYourPresence);
  Arabic_SetCursor(0,63);
  Arabic_OutString(ArabicAlphabet);
  while(1){
  }
}
uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

uint16_t squirrel_start[]={0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110}; //squirrel starting x position -  11 possibilities


uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish} Language_t;
Language_t myLanguage=English;
typedef enum {LANGUAGE, SELECT, PLAYER1, PLAYER2, NICETRY, SCORE, HIGHSCORE} phrase_t;
const char Language_English[]="english ->";
const char Language_Spanish[]="espa\xA4ol <-";

const char Select_English[] = "select a player";
const char Select_Spanish[] = "selecciona un jugador";

const char Player1_English[]="player 1  ^";
const char Player1_Spanish[]="jugador 1  ^";

const char Player2_English[]="player 2  v";
const char Player2_Spanish[]="jugador 2  v";

const char NiceTry_English[] ="restart ->"; // previously nice try 
const char NiceTry_Spanish[]="reanudar ->";

const char Score_English[]="score:";
const char Score_Spanish[]="puntaje:";

const char Highscore_English[]="high score:";
const char Highscore_Spanish[]="mejor puntuaci\xA2n:";

const char *Phrases[7][2]={
  {Language_English,Language_Spanish},
  {Select_English,Select_Spanish},
  {Player1_English,Player1_Spanish},
  {Player2_English, Player2_Spanish},
  {NiceTry_English,NiceTry_Spanish},
  {Score_English,Score_Spanish},
  {Highscore_English,Highscore_Spanish}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=LANGUAGE; myPhrase<= SCORE; myPhrase++){
    for(Language_t myL=English; myL<= Spanish; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_WHITE); 
  ST7735_DrawBitmap(0, 159, speedway2, 128,160);
  ST7735_DrawBitmap(50, 159, longhorn, 33,37);
  ST7735_DrawBitmap(10, 20, squirrel, 18,19);
  ST7735_DrawBitmap(45, 20, whitesquirrel, 18,19);
  ST7735_DrawBitmap(80, 20, squirrel, 18,19);

  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    int input = Switch_In();
    if((input&8)!=0){
      input = 7;
    }
    else{
      input = input&7;
    }
    LED_Off(input);
    LED_On(input);
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int data, data1, language, player = 0;

int main5(void){ // final main5
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();


//language
  while(1){
    // data = ADCin(); // slidepot testing
    // data1 = Convert(data);
    uint16_t switch1 = 0;
    do{
    switch1 = Switch_In();}
    while(((switch1&8)==0)&&((switch1&2)==0));

    if((switch1&8)==8){ //right 
      language = 1; //1 is english
    }
    if((switch1&2)==2){ //left 
      language = 0; //0 is spanish
    }


//players 
    do{
    switch1 = Switch_In();}
    while(((switch1&1)==0)&&((switch1&4)==0));

    if((switch1&1)==1){ //up 
      player = 0; //0 is player 1 
    }
    if((switch1&4)==4){ //down 
      player = 1; //1 for player 2
    }
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}

#define FIX 7 //2**-7 pixels 
struct sprite{
  int32_t x; // 0 to 127<<FIX
  uint32_t y; // 0 to 159<<FIX
  int32_t old_x; 
  uint32_t old_y;
  const  unsigned short *image;
  const  unsigned short *black; 
  uint32_t h, w; // size 
  uint32_t life; // 0 is dead (do not draw), 1 (dying erase), 2 (alive)
  int32_t vy; // velocity 
};
typedef struct sprite sprite_t;
sprite_t longhorn1; 
sprite_t squirrel1; 
sprite_t squirrel2;
sprite_t squirrel3;
void Initialize_Sprites(void){
  //longhorn1.x = 50<<FIX; 
  longhorn1.y = 159<<FIX; //stays the same 
  longhorn1.image = longhorn; 
  longhorn1.black = longhorn; //fix//////////////////////////////////////////////
  longhorn1.h = 33;
  longhorn1.w = 37; 
  longhorn1.life = 2; //alive
  longhorn1.vy = 0; 


  //squirrel1.x = 10<<FIX; 
  squirrel1.y = 1<<FIX; //stays the same 
  squirrel1.image = squirrel; 
  squirrel1.black = squirrel; //fix//////////////////////////////////////////////
  squirrel1.h = 18;
  squirrel1.w = 19; 
  squirrel1.life = 2; //alive
  squirrel1.vy = 300; 

  //squirrel2.x = 10<<FIX; 
  squirrel2.y = 1<<FIX; //stays the same 
  squirrel2.image = whitesquirrel; 
  squirrel2.black = whitesquirrel; //fix//////////////////////////////////////////////
  squirrel2.h = 18;
  squirrel2.w = 19; 
  squirrel2.life = 0; //alive
  squirrel2.vy = 300;

  squirrel3.y = 1<<FIX; //stays the same 
  squirrel3.image = squirrel; 
  squirrel3.black = squirrel; //fix//////////////////////////////////////////////
  squirrel3.h = 18;
  squirrel3.w = 19; 
  squirrel3.life = 0; //alive
  squirrel3.vy = 300;
}
void Redscreen(void){

}

void Draw(void){//has to be in main
 //ST7735_DrawBitmap(squirrel1.old_x, squirrel1.old_y, speedway2, 19,18);
  
  int longhorndraw = 0;
  if(longhorn1.life == 2){
    if(((longhorndraw%100)==0)&&(longhorn1.x!=longhorn1.old_x)){
      ST7735_DrawBitMapGreenScreen(longhorn1.old_x>>FIX, longhorn1.y>>FIX, red, longhorn1.h, longhorn1.w, ST7735_RED, speedway2);
    
     
    }
    ST7735_DrawBitMapGreenScreen(longhorn1.x>>FIX, longhorn1.y>>FIX, longhorn1.image, longhorn1.h, longhorn1.w, ST7735_RED, speedway2);
    longhorndraw++;
  }
  if(squirrel1.life == 2){
    if((squirrel1.y - squirrel1.old_y)>19){
      ST7735_DrawBitMapGreenScreen(squirrel1.x>>FIX, squirrel1.old_y>>FIX, red, squirrel1.h, squirrel1.w, ST7735_RED, speedway2);
    }
    ST7735_DrawBitMapGreenScreen(squirrel1.x>>FIX, squirrel1.y>>FIX, squirrel1.image, squirrel1.h, squirrel1.w, ST7735_RED, speedway2);
  }

  if(squirrel3.life == 2){
    if((squirrel3.y - squirrel3.old_y)>19){
      ST7735_DrawBitMapGreenScreen(squirrel3.x>>FIX, squirrel3.old_y>>FIX, red, squirrel3.h, squirrel3.w, ST7735_RED, speedway2);
    }
    ST7735_DrawBitMapGreenScreen(squirrel3.x>>FIX, squirrel3.y>>FIX, squirrel3.image, squirrel3.h, squirrel3.w, ST7735_RED, speedway2);
  }
  

  if(squirrel2.life == 2){
    if((squirrel2.y - squirrel2.old_y)>19){
      ST7735_DrawBitMapGreenScreen(squirrel2.x>>FIX, squirrel2.old_y>>FIX, red, squirrel1.h, squirrel1.w, ST7735_RED, speedway2);
    }
    ST7735_DrawBitMapGreenScreen(squirrel2.x>>FIX, squirrel2.y>>FIX, squirrel2.image, squirrel2.h, squirrel2.w, ST7735_RED, speedway2);
    }
}
int x_position_longhorn = 50;
int cnt = 0;
int sum = 0;
int cnt1 = 0;
int sum1 = 0;
int cnt2 = 0;
int sum2 = 0;
void Move(void){ // will be called at 30 Hz in G12////////////////////////////////////////////////
  if(squirrel1.life == 2){
    if(cnt%5 == 1){
    sum = squirrel1.y;
    }
    squirrel1.y += squirrel1.vy;
    if(cnt%5==0){
      squirrel1.old_y = sum;
    }
    cnt++;
  }
  if(squirrel2.life == 2){
    if(cnt1%5 == 1){
    sum1 = squirrel2.y;
    }
    squirrel2.y += squirrel2.vy;
    if(cnt1%5==0){
      squirrel2.old_y = sum1;
    }
    cnt1++;
  }
  if(squirrel3.life == 2){
    if(cnt2%5 == 1){
    sum2 = squirrel3.y;
    }
    squirrel3.y += squirrel3.vy;
    if(cnt2%5==0){
      squirrel3.old_y = sum2;
    }
    cnt2++;
  }
   longhorn1.old_x = longhorn1.x;
   longhorn1.x = (x_position_longhorn<<FIX);
 }

int start = 0;
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    int input = 0;
    for(int i = 0; i<10; i++){
    input += ADCin();
    }
    input = input/10;
    x_position_longhorn = Convert(input);
    Move();
    start = 1;
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
  
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
int sound_done;
int dif(int n1, int n2){
   int diff = (n1>>FIX)-(n2>>FIX);
   if(diff<0){
     diff = diff*(-1);
   }
   return diff;
 }
static uint16_t highscore[] = {0,0};
uint16_t score = 0;
void game(void){

  
  
  score = 0;
  ST7735_DrawBitmap(0, 159, speedway2, 128,160);
  Initialize_Sprites();
  
  ST7735_FillScreen(ST7735_WHITE); 
  ST7735_DrawBitmap(0, 159, speedway2, 128,160);
  LED_On(1);
  Clock_Delay1ms(500);
  LED_Off(0);
  
  LED_On(2);
  Clock_Delay1ms(500);
  LED_Off(0);
 
  LED_On(4);
  Clock_Delay1ms(500);
  LED_Off(0);
  __enable_irq();
  //Clock_Delay1ms(300);
  squirrel1.x = (squirrel_start[1]<<FIX);
  squirrel2.x = (squirrel_start[5]<<FIX);
  squirrel3.x = (squirrel_start[10]<<FIX);
  while(longhorn1.life == 2){
    //Draw();
    //Move();
    //Clock_Delay1ms(33); ////////////////////////////////////delete this later 
    if((squirrel1.y>>FIX)>180){
      Sound_Shoot();
      //ST7735_DrawBitMapGreenScreen(squirrel1.x>>FIX, squirrel1.y>>FIX, red, squirrel1.h, squirrel1.w, ST7735_RED, speedway2);
      squirrel1.y = 1<<FIX;
      squirrel1.x = (squirrel_start[(Random(11))])<<FIX;
      score += 10;
      //squirrel1.vy += 10;
    }
    if((squirrel2.y>>FIX)>180){
      Sound_Shoot();
      squirrel2.y = 1<<FIX;
      squirrel2.x = (squirrel_start[(Random(11))])<<FIX;
      score += 10;
      //squirrel2.vy += 10;
    }
    if((squirrel3.y>>FIX)>180){
      Sound_Shoot();
      //ST7735_DrawBitMapGreenScreen(squirrel1.x>>FIX, squirrel1.y>>FIX, red, squirrel1.h, squirrel1.w, ST7735_RED, speedway2);
      squirrel3.y = 1<<FIX;
      squirrel3.x = (squirrel_start[(Random(11))])<<FIX;
      score += 10;
      //squirrel1.vy += 10;
    }
    while(dif(squirrel1.x,squirrel2.x)<=18){
      if((squirrel1.y>>FIX)<10){
        squirrel1.x = (squirrel_start[(Random(11))])<<FIX;
      }
      if((squirrel2.y>>FIX)<10){
      squirrel2.x = (squirrel_start[(Random(11))])<<FIX;
      }
    }
    while(dif(squirrel1.x,squirrel3.x)<=18){
      if((squirrel1.y>>FIX)<10){
        squirrel1.x = (squirrel_start[(Random(11))])<<FIX;
      }
      if((squirrel3.y>>FIX)<10){
      squirrel3.x = (squirrel_start[(Random(11))])<<FIX;
      }
      
    }
    while(dif(squirrel2.x,squirrel3.x)<=18){
      if((squirrel2.y>>FIX)<10){
        squirrel2.x = (squirrel_start[(Random(11))])<<FIX;
      }
      if((squirrel3.y>>FIX)<10){
      squirrel3.x = (squirrel_start[(Random(11))])<<FIX;
      }
    }
    if((squirrel1.y>>FIX)>50){
    squirrel2.life = 2;
    }
    if((squirrel1.y>>FIX)>100){
    squirrel3.life = 2;
    }
    

    if(((159-(squirrel1.y>>FIX))<34)){
      int overlap1 = (longhorn1.x>>FIX) - (squirrel1.x>>FIX);
      
    if(((overlap1<15)&&(overlap1>(-30)))){
      Sound_Killed();
      longhorn1.life = 0;      
    }
    }
    
    if(((159-(squirrel2.y>>FIX))<34)){
      int overlap2 = (longhorn1.x>>FIX) - (squirrel2.x>>FIX);

    if(((overlap2<15)&&(overlap2>(-30)))){
      Sound_Killed();
      longhorn1.life = 0;
    }
    }

    if(((159-(squirrel3.y>>FIX))<34)){
      int overlap3 = (longhorn1.x>>FIX) - (squirrel3.x>>FIX);

    if(((overlap3<15)&&(overlap3>(-30)))){
      Sound_Killed();
      longhorn1.life = 0;
    }
    }
    
   
   Draw();
   


  
  ST7735_SetCursor(0, 0);
  ST7735_OutUDec(score);
  }
  //Sound_Killed();
}
int player_1 (void){
uint16_t switch1 = 0;
    do{
    switch1 = Switch_In();}
    while(((switch1&4)==0)&&((switch1&1)==0));

    if((switch1&4)==4){ //down 
      switch1 = 1; //1 is player 2
      return switch1;
    }
    if((switch1&1)==1){ //up 
      switch1 = 0; //0 is player 1
      return switch1; 
    }
    return switch1;
}
int language_1 (void){
uint16_t switch1 = 0;
    do{
    switch1 = Switch_In();}
    while(((switch1&8)==0)&&((switch1&2)==0));

    if((switch1&8)==8){ //right 
      language = 0; //0 is english
    }
    if((switch1&2)==2){ //left 
      language = 1; //1 is spanish
    }
    return language; 
}

int main(void){ // maina
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Sound_Init();
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init();
  LED_Init(); // initialize switches
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo

  //ST7735_FillScreen(ST7735_BLACK);           
  
  ST7735_FillScreen(ST7735_WHITE); 

  
  while(1){
   
  ST7735_DrawBitmap(0, 159, gameover, 128,160); //start screen 
  ST7735_SetCursor(6, 6);
  ST7735_OutString("Welcome to");
  ST7735_SetCursor(4, 7);
  ST7735_OutString("Longhorn Racer");

  ST7735_SetCursor(6, 10);
  ST7735_OutString((char*)Phrases[LANGUAGE][English]);
  ST7735_SetCursor(6, 12);
  ST7735_OutString((char*)Phrases[LANGUAGE][Spanish]);
   Clock_Delay1ms(300);
  myLanguage = language_1(); // 0 = spanish (left); 1 = english (right)
  
  

  ST7735_DrawBitmap(0, 159, gameover, 128,160); //player screen
  ST7735_SetCursor(6, 7);
  ST7735_OutString((char*)Phrases[PLAYER1][myLanguage]);
  ST7735_SetCursor(6, 10);
  ST7735_OutString((char*)Phrases[PLAYER2][myLanguage]);
   Clock_Delay1ms(300);
  player = player_1(); // 0 = player 1 (up); 1 = player 2 (down)
  TimerG12_IntArm(80000000/30,2);
  
  game();
  while(sound_done!=0){

  };
  __disable_irq();
  // TIMG12->CPU_INT.IMASK &= 0x1;
  // NVIC->ISER[0] &= ~(1 << 21);
  
  if(score>(highscore[player])){
    highscore[player] = score;
  }
  // if (language1 == 0 || language1 == 1){
  //   game();
  // }
  
  LED_On(7);
  Clock_Delay1ms(200);
  LED_Off(0);
  Clock_Delay1ms(200);
  LED_On(7);
  Clock_Delay1ms(200);
  LED_Off(0);
  Clock_Delay1ms(200);
  LED_On(7);
  Clock_Delay1ms(200);
  LED_Off(0);
  
  //ST7735_FillScreen(ST7735_WHITE); 
  ST7735_DrawBitmap(0, 159, gameover, 128,160);

if(myLanguage == 1){ //spanish 
ST7735_SetCursor(7, 6);
}
else { //english 
ST7735_SetCursor(8, 6);
}
  
  ST7735_OutString((char*)Phrases[SCORE][myLanguage]);
  ST7735_SetCursor(9, 7);
  ST7735_OutUDec(score);

if(myLanguage == 1){ //spanish 
  ST7735_SetCursor(3, 9);
}
else { //english 
  ST7735_SetCursor(5, 9);
}
  ST7735_OutString((char*)Phrases[HIGHSCORE][myLanguage]);
  ST7735_SetCursor(9, 10);
  ST7735_OutUDec(highscore[player]);


  ST7735_SetCursor(5, 12);
  ST7735_OutString((char*)Phrases[NICETRY][myLanguage]);

 
 int switch1 = 0;
 do{
    switch1 = Switch_In();}
    while(switch1!=8);

  }

  
  return 0;
}



 

