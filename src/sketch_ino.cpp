#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_TEMP,INPUT);
  pinMode(PIN_LED1,OUTPUT);
  pinMode(PIN_LUMINOSITE,INPUT);
  pinMode(PIN_LED2,OUTPUT);
  pinMode(PIN_BOUTON,INPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val;
  int lum;
  int bouton;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    val=analogRead(1);
    lum=analogRead(2);
    bouton=analogRead(4);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);
    sprintf(buf,"Bouton en pos %d",bouton);
    Serial.println(buf);
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"%d",val);
      bus.write(1,buf,100);
    }
    cpt++;
    sleep(1);
  }
  bouton=analogRead(4);
  if (bouton==ON){digitalWrite(3,LOW);}
  else {digitalWrite(3,HIGH);}
// on eteint et on allume la LED
  if(bascule){
    digitalWrite(0,HIGH);
  }
  else{
    digitalWrite(0,LOW);
  }
  bascule=1-bascule;

}


