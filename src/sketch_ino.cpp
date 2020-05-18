#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);

// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_TEMP,INPUT);
  pinMode(PIN_LED_1,OUTPUT);
  pinMode(PIN_LUM,INPUT);
  pinMode(PIN_LED_2,OUTPUT);
  pinMode(PIN_BOUTON,INPUT);
  pinMode(PIN_HUM_AIR,INPUT);
  pinMode(PIN_HUM_SOIL,INPUT);


}

// la boucle de controle arduino
void Board::loop(){

  char buf[100];
  int val;
  int lum;
  int air;
  int sol;
  int bouton;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature

    val=analogRead(PIN_TEMP);
    lum=analogRead(PIN_LUM);
    air =analogRead(PIN_HUM_AIR);
    sol=analogRead(PIN_HUM_SOIL);
    bouton=analogRead(PIN_BOUTON);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);
    sprintf(buf,"humidite air %d",air);
    Serial.println(buf);
    sprintf(buf,"humidite sol %d",sol);
    Serial.println(buf);
    sprintf(buf,"Bouton en pos %d",bouton);
    Serial.println(buf);

   // if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
    //  sprintf(buf,"%d",val);
     // bus.write(I2C_SCREEN,buf,100);
      bus.write(I2C_LCD,buf,100);
   // }
       cpt++;
    sleep(1);
  }
   bouton=analogRead(PIN_BOUTON);
  if (bouton==ON){digitalWrite(PIN_LED_2,LOW);}
  else {digitalWrite(PIN_LED_2,HIGH);}
// on eteint et on allume la LED
  if(bascule){
    digitalWrite(PIN_LED_1,HIGH);
  }
  else{
    digitalWrite(PIN_LED_1,LOW);
  }
  bascule=1-bascule;



}


