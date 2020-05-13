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
  pinMode(PIN_RADAR,INPUT);
  pinMode(PIN_SERVO_ARROSOIR,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val;
  int lum;
  int bouton;
  int dist;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture capteur de temperature
    //Serial.println("Lecture de la temperature");
    val=analogRead(PIN_TEMP);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    //Lecture capteur de luminosite
    //Serial.println("Lecture de la luminosite");
    lum=analogRead(PIN_LUMINOSITE);
     sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);
    //lecture bouton
    //Serial.println("Lecture du bouton");
    bouton=analogRead(PIN_BOUTON);
    sprintf(buf,"Bouton en pos %d",bouton);
    Serial.println(buf);
    //lecture distance
     //Serial.println("Lecture de la distance");
    dist=analogRead(PIN_RADAR);
    sprintf(buf,"Distance de l'arrosoir %d",dist);
    Serial.println(buf);
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
        Serial.println("Envoi a l'ecran");
        sprintf(buf,"%d",val);
        bus.write(1,buf,100);
    }
    cpt++;
    sleep(1);
  }
  //Serial.println("Ecriture vitesse arrosoir");
  digitalWrite(PIN_SERVO_ARROSOIR,10);
  //Serial.println("Ecriture LED2 selon bouton");
  bouton=analogRead(PIN_BOUTON);
  if (bouton==ON){digitalWrite(PIN_LED2,LOW);}
  else {digitalWrite(PIN_LED2,HIGH);}
  //Serial.println("Basculement etat de la LED");
// on eteint et on allume la LED
  if(bascule){
    digitalWrite(PIN_LED1,HIGH);
  }
  else{
    digitalWrite(PIN_LED1,LOW);
  }
  bascule=1-bascule;

}


