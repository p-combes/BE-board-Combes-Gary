#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "Arosoir.h"
#include "application_plante.h"
#include "lampeUV.cpp"

 set <CaracteristiquePlante> Decisions; //Liste contenant les actions à faire pour l'arrosoir
// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);

// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_TEMP,INPUT);
  pinMode(PIN_UV1,OUTPUT);
  pinMode(PIN_UV2,OUTPUT);
  pinMode(PIN_UV3,OUTPUT);
  pinMode(PIN_LUMINOSITE_1,INPUT);
  pinMode(PIN_LUMINOSITE_2,INPUT);
  pinMode(PIN_LUMINOSITE_3,INPUT);
  pinMode(PIN_BOUTON,INPUT);
  pinMode(PIN_HUM_AIR,INPUT);
  pinMode(PIN_HUM_SOIL_1,INPUT);
  pinMode(PIN_HUM_SOIL_2,INPUT);
  pinMode(PIN_HUM_SOIL_3,INPUT);
  pinMode(PIN_SERVO_INCLINAISON,OUTPUT);
  pinMode(PIN_RADAR,INPUT);
  pinMode(PIN_SERVO_ARROSOIR,OUTPUT);
  pinMode(PIN_ANGULAR,INPUT);
}

// la boucle de controle arduino
void Board::loop(){
    int diag;
    char buf[100];
    int planteADiagnostiquer = 1;
    int ecranCorrespondant;
    Arrosoir arros;
    switch (planteADiagnostiquer){
        case 1:
            ecranCorrespondant = I2C_SCREEN_1;
        case 2:
            ecranCorrespondant = I2C_SCREEN_2;
        case 3 :
            ecranCorrespondant = I2C_SCREEN_3;
    }
    CaracteristiquePlante Cactus (1,60,0,100,30,20,10000);
    CaracteristiquePlante Tulipe(2,40,-4,200,40,30,1000);
    diag = runDiagnosis(Cactus,this);
    Cactus.SetPriority(this);
    takeDecision(diag,Cactus,arros,this,Decisions);
    sprintf(buf,"distance de l'arrosoir %d",measureDistance(this));
    Serial.println(buf);
    sprintf(buf,"angle de l'arrosoir %d",measureAngle(this));
    Serial.println(buf);
    //Gestion des decisions
    applyDecision(Decisions,arros,Cactus,Tulipe,this);

   sleep(5);

/*
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

    air =analogRead(PIN_HUM_AIR);
    sol=analogRead(PIN_HUM_SOIL);
    bouton=analogRead(PIN_BOUTON);
    angle=analogRead(PIN_ANGULAR);
    val=analogRead(PIN_TEMP);
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


*/
}


