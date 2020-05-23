#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "application_plante.h"

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
  pinMode(PIN_HUM_SOIL_1,INPUT);
  pinMode(PIN_SERVO_INCLINAISON,OUTPUT);
  pinMode(PIN_RADAR,INPUT);
  pinMode(PIN_SERVO_ARROSOIR,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){

    JourneePrintemps();
    CaracteristiquePlante Cactus (60,0,200,30,20,10000);
    cout<<"diagnostic"<<runDiagnosis(1,Cactus,this)<<endl;
   sleep(5);

/*
  char buf[100];
  int val;
  int lum;
  int air;
  int sol;
  int bouton;
  int dist;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  //Deplacement arrosoir jusqu'a position plante 1
  if (analogRead(PIN_RADAR)<DISTANCE_PLANTE_1){
     digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_DEPLACEMENT);
      digitalWrite(PIN_SERVO_INCLINAISON,0);
  }
  else{
     digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_ARRET);
      digitalWrite(PIN_SERVO_INCLINAISON,1);
  }
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature


    val=measureTemperature(this);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);


    lum=measureLuminosity(this);
     sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);

    air = measureAirHumidity(this);
    sprintf(buf,"humidite air %d",air);
    Serial.println(buf);

    sol = measureSoilHumidity(1,this);
    sprintf(buf,"humidite sol %d",sol);
    Serial.println(buf);

    bouton=analogRead(PIN_BOUTON);
    sprintf(buf,"Bouton en pos %d",bouton);
    Serial.println(buf);

    //lecture distance
     //Serial.println("Lecture de la distance");
    dist=analogRead(PIN_RADAR);
    sprintf(buf,"Distance de l'arrosoir %d",dist);
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


*/
}


