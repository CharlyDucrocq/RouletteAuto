#include <ServoTimer2.h>
#include <TimerOne.h>


#define S0    7  
#define S1    6  
#define S2     5  
#define S3     4
#define OUT    2  
                  
#define LED    8  

ServoTimer2 servo1;  //triage 12
ServoTimer2 servo2;  //stop 9
ServoTimer2 servo3;  //tourner 13
ServoTimer2 servo4;  //redistribuer 

int angle=0;
float g_SF[3];     
int   g_count = 0; 
int   g_array[3]; 
int   g_flag = 0;   
int  var [3];
bool condition = false;
int y = 0;
int vert = 0;
int blanc = 0;
int noir = 0;
int bleu = 0;
int rouge = 0;
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(S0, LOW); 
  digitalWrite(S1, HIGH);
}
 
void TSC_Filtervar(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
  if(Level02 != 0)
    Level02 = HIGH;
  digitalWrite(S2, Level01);
  digitalWrite(S3, Level02);
}
 

void TSC_Count()
{
  g_count ++ ;
}
 

void TSC_Callback()
{
  switch(g_flag)
  {
    case 0:
         Serial.println("->WB Start");
         TSC_WB(LOW, LOW);   // Filtre sans rouge
         break;
    case 1:
         Serial.print("->Frequency R=");
         Serial.println(g_count);  
         g_array[0] = g_count;    
         TSC_WB(HIGH, HIGH);   // Filtre sans vert
         break;
    case 2:
         Serial.print("->Frequency G=");
         Serial.println(g_count);  
         g_array[1] = g_count;    
         TSC_WB(LOW, HIGH);    // Filtre sans bleu
         break;
 
    case 3:
         Serial.print("->Frequency B=");
         Serial.println(g_count);   
         Serial.println("->WB End");
         g_array[2] = g_count;    
         TSC_WB(HIGH, LOW);    // Pas de filtre 
         break;
   default:
         g_count = 0;     
         break;
  }
}

void TSC_WB(int Level0, int Level1)   // Balance des blancs   
{
  g_count = 0;   
  g_flag ++;     
  TSC_Filtervar(Level0, Level1); 
  Timer1.setPeriod(1000000);     
}

void setup()
{
  
  TSC_Init();
  Serial.begin(9600); 
  Timer1.initialize();   // defaulte is 1s
  servo1.attach(12);
  servo2.attach(9);
  Timer1.attachInterrupt(TSC_Callback); 
  attachInterrupt(0, TSC_Count, RISING);
  digitalWrite(LED, HIGH);
  delay(500); 
  g_SF[0] = 255.0/g_array[1];     // valeur R
  g_SF[1] = 255.0/g_array[2];    // valeur G
  g_SF[2] = 255.0/g_array[3];    // valeur B
}

int color(){
   g_flag = 0;
   delay(500);
   for(int i=0; i<3; i++){
    var[i]=g_array[i]*g_SF[i];
    Serial.println(int(var[i]));
   }
    if(var[1]>var[2] && var[1]>110 && var[0]<100){vert=vert+1;Serial.print("vert:");Serial.println(vert);return 1;}//1000
    if(300>var[0]>200 && 300>var[1]>200 && 300>var[2]>200){blanc=blanc + 1;Serial.print("blanc:");Serial.println(blanc);return 2;}//1250
    if(var[0]>100 && var[1]<80 && var[2]<80){rouge=rouge+1;Serial.print("rouge:");Serial.println(rouge);return 3;}//1500
    if(var[0]<90 && var[1]<90 && var[2]>100){bleu=bleu+1;Serial.print("bleu:");Serial.println(bleu);return 4;}//1750
    if(90>var[0] && 90>var[1] && 90>var[2]){noir=noir+1;Serial.print("noir:");Serial.println(noir);return 5;}//2000
    else{return 0;}
  }
int triage(int y){
  Serial.println("on commece le triage");
  if(y==0){
    return false;
  }
else{
  servo1.attach(12);
  switch(y){
    case 1:
    servo1.write(1200);
    break;
    case 2:
    servo1.write(1400);
    break;
    case 3:
    servo1.write(1600);
    break;
    case 4:
    servo1.write(1800);
    break;
    case 5:
    servo1.write(1900);
    break;
    
  }
  delay(100);
  servo1.detach();
  return true;
}
Serial.print("le triage est fini");
}

void arret(bool condition){
  servo2.attach(9);
  delay(100);
   if(condition == true){
    Serial.println("déblocage");
    servo2.write(0);
   }
   if(condition == false){
    Serial.println("blocage");
    servo2.write(180);
   }
   servo2.detach();
}
  
void loop(){
  y=color();
  condition = triage(y);
  arret(condition);
  Serial.print("couleur est:");Serial.println(y);
  delay(500);
  
}
