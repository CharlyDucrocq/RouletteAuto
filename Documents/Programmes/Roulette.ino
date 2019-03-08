#include <PinChangeInt.h>

//capteur aiment
int capt1 = A1;
int capt2 = A2;
int capt3 = A3;
int capt4 = A4;

//Moteur
int ENA= 9;
int IN1 = 4;
int IN2 = 5;

//cateur boule
int captBoule = A0; ///capte en LOW


//const
int vMax = 250;
int vMin = 100;

int tRef = 0;
int nRef = 1;
int t = 0;
bool verifBoule = true;


void actCapt1(){      // enregistre numero du capteur et chrono quand celui ci est activer
  nRef = 1;
  tRef = millis();
}
void actCapt2(){      // enregistre numero du capteur et chrono quand celui ci est activer
  nRef = 2;
  tRef = millis();
}
void actCapt3(){      // enregistre numero du capteur et chrono quand celui ci est activer
  nRef = 3;
  tRef = millis();
}
void actCapt4(){      // enregistre numero du capteur et chrono quand celui ci est activer
  nRef = 4;
  tRef = millis();
}
void verifCaptBoule(){      // enregistre chrono et valide l'activation du capteur
  verifBoule = false;
  t = millis();
}

void tournerRoue(int PWM){ 
  analogWrite(ENA,PWM);
}

void pousseBille(){      // ejecte la bille de la roue
  // a faire
}

void lanceBille(){      // lance la bille sur la roulette
  // a faire
}

void debut(){                 // demarre la roue a la vitesse max, lance la bille (non fait) et diminue jusu'a la vitesse min
  tournerRoue(250);
  delay(1000);
  lanceBille();
  delay(1000);
  for(int i=vMax;i>vMin;i=i-10){
    analogWrite(ENA,i);
    delay(500);
  }
}

int detect(){                                         // retourne le temps entre le dernier capteur d'aiment (enregister dans nRef) et le capteur de la boule
  PCintPort::attachInterrupt(capt1,actCapt1,RISING);
  PCintPort::attachInterrupt(capt2,actCapt2,RISING);
  PCintPort::attachInterrupt(capt3,actCapt3,FALLING);
  PCintPort::attachInterrupt(capt4,actCapt4,RISING);
  verifBoule = true;
  analogWrite(ENA,vMin);
  Serial.println("Etape attente de capteur atteinte");
  PCintPort::attachInterrupt(captBoule, verifCaptBoule, FALLING);
  while(verifBoule){
    delay(10);
  }
  PCintPort::detachInterrupt(capt1);
  PCintPort::detachInterrupt(capt2);
  PCintPort::detachInterrupt(capt3);
  PCintPort::detachInterrupt(capt4);
  PCintPort::detachInterrupt(captBoule);
  t=t-tRef;
  Serial.println("t : " + String(t));
  return t;//traitement(t);
}

int traitement(int temps[],int nTemps,int med){            // retourne la valeur dans laquelle la bille est tombé
  int somme=0;
  bool verifMoy = true;
  int moy;
  //printTab(temps);
  for(int i=0;i<nTemps;i++){                               // verifie si il n'y a pas de valeur aberante
    if(abs(temps[i] - med) > 100 ){
      temps[i]=3000; 
    }
  }
  int nBonTemps = nTemps;
  for(int i=0;i<nTemps;i++){
    if(temps[i]!=3000){
      somme+=temps[i];
    }
    else{
      nBonTemps-=1;
    }
  }
  moy = somme/nBonTemps;
  Serial.println("Moyenne : "+String(moy));
}

int roulette(){ // -------------- FONCTION PRINCIPAL -------------------
  debut();
  int nVerif = 10;
  int myResult[nVerif];
  for(int n=0;n<nVerif;n++){
    myResult[n]=detect();
  }
  printTab(myResult);
  tournerRoue(0);
  return traitement(myResult,nVerif, medianeTab(myResult,nVerif));
}

////////////////////////////////////////////////////////////////////////////
/// ---------- Fonctions traitement de tableau ---------------------------//
////////////////////////////////////////////////////////////////////////////
                                                                          //
int minTab(int tab[],int nTab){                                           //
  int mini=4000;                                                          //
  int iRef=0;                                                             //
  for(int i=0;i<nTab;i++){                                                //
    if(mini>tab[i]){                                                      //
      mini = tab[i];                                                      //
      iRef =i;                                                            //
    }                                                                     //
  }                                                                       //
  return iRef;                                                            //
}                                                                         //
                                                                          //
                                                                          //
int medianeTab(int tabRef[],int nTab){                                    //
  int tab[nTab];                                                          //
  for(int j=0;j<nTab;j++){                                                //
    tab[j]=tabRef[j];                                                     //
  }                                                                       //
  int sTab[nTab];                                                         //
  for(int i=0;i<nTab;i++){                                                //
    int mini = minTab(tab,nTab);                                          //
    sTab[i]=tab[mini];                                                    //
    tab[mini]=5000;                                                       //
  }                                                                       //
  int m = nTab/2;                                                         //
  m =sTab[m];                                                             //
  return m;                                                               //
}                                                                         //
                                                                          //
void printTab(int tab[]){ // print un tableau d'entier                    //
  Serial.println("TAB :");                                                //
  for(int i=0;i<10;i++){                                                  //
    Serial.println(tab[i]);                                               //
  }                                                                       //
                                                                          //
///////////////////////////////////////////////////////////////////////////

                                                                          
                                                                          
void setup() {
  // put your setup code here, to run once:  
  pinMode(ENA,OUTPUT);  
  pinMode(IN1,OUTPUT);  
  pinMode(IN2,OUTPUT);  
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  
  pinMode(capt1,INPUT);
  pinMode(capt2,INPUT);
  pinMode(capt3,INPUT);
  pinMode(capt4,INPUT);

  // TEST
  pinMode(11,OUTPUT);
  //
  
  pinMode(captBoule,INPUT_PULLUP);
  
  
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  roulette();
 // delay(1000);
  while(true){}
 
}
}
