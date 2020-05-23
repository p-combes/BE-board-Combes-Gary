#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "Arosoir.cpp"
static bool premierPassage=false;
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
  pinMode(PIN_HUM_AIR,INPUT);
  pinMode(PIN_HUM_SOIL,INPUT);
  pinMode(PIN_SERVO_INCLINAISON,OUTPUT);
  pinMode(PIN_RADAR,INPUT);
  pinMode(PIN_SERVO_ARROSOIR,OUTPUT);
  pinMode(PIN_ANGULAR,INPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  Arrosoir arros;
  int val;
  int lum;
  int air;
  int sol;
  int bouton;
  double dist;
  double angle;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  arros.arroser(1,220,this);
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature

    val=analogRead(PIN_TEMP);
    air =analogRead(PIN_HUM_AIR);
    sol=analogRead(PIN_HUM_SOIL);
    bouton=analogRead(PIN_BOUTON);
    angle=analogRead(PIN_ANGULAR);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    //Lecture capteur de luminosite
    //Serial.println("Lecture de la luminosite");
    lum=analogRead(PIN_LUMINOSITE);
     sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);
    sprintf(buf,"humidite air %d",air);
    Serial.println(buf);
    sprintf(buf,"humidite sol %d",sol);
    Serial.println(buf);
    sprintf(buf,"Bouton en pos %d",bouton);
    Serial.println(buf);
    dist=analogRead(PIN_RADAR);
    sprintf(buf,"Distance de l'arrosoir %f",dist);
    Serial.println(buf);
    sprintf(buf,"angle de l'arrosoir %f",angle);
    Serial.println(buf);
   // if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
     sprintf(buf,"Temperature screen %d",val);
      bus.write(I2C_SCREEN,buf,100);
    sprintf(buf,"Etat de stante de la plante : %s","Excellente");
      bus.write(I2C_LCD,buf,100);
   // }
       cpt++;
    sleep(1);
  }
  //Serial.println("Ecriture vitesse arrosoir");

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


