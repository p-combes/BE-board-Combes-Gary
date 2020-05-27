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
    int diagCactus;
    int diagTulipe;
    char buf[100];
    int planteADiagnostiquer = 1;
    int ecranCorrespondant;
    Arrosoir arros;
    switch (planteADiagnostiquer){
        case 1:
            ecranCorrespondant = I2C_SCREEN_1;
            break;
        case 2:
            ecranCorrespondant = I2C_SCREEN_2;
            break;
        case 3 :
            ecranCorrespondant = I2C_SCREEN_3;
            break;
    }
    //Definition des caracteristiques propres a chaque plante
    try{
        CaracteristiquePlante Cactus ("cactus",1,60,0,100,30,20,10000);
        CaracteristiquePlante Tulipe("tulipe",2,40,-4,300,30,30,6000);
        //Diagnostic de chaque plante => Quelle action mener?
        diagCactus = runDiagnosis(Cactus,this);
        diagTulipe = runDiagnosis(Tulipe,this);
        //On définit les priorites de chaque plante : une haute prio indique un fort manque en eau
        Cactus.SetPriority(this);
        Tulipe.SetPriority(this);
        //On met a jour la queue des decisions prises
        takeDecision(diagCactus,Cactus,arros,this,Decisions, ecranCorrespondant);
        takeDecision(diagTulipe,Tulipe,arros,this,Decisions, ecranCorrespondant);
        //Affichage de l'etat de l'arrosoir (mesure avec radar et servo angulaire)
        Serial.println("***************PARAMETRES DE L ARROSOIR ***************");
        sprintf(buf,"distance de l'arrosoir %d",measureDistance(this));
        Serial.println(buf);
        sprintf(buf,"angle de l'arrosoir %d",measureAngle(this));
        Serial.println(buf);
        //Gestion de la coordination des decisions
        applyDecision(Decisions,arros,Cactus,Tulipe,this);
    }

    catch (int exeption){
    switch (exeption){
    case EXCEPTION_NAME_PLANT:
        cerr<<"Nom de plante non existant"<<endl;
        break;
    case EXCEPTION_NB_PLANTE:
        cerr<<"Numero de la plante superieur a la capacite du potager"<<endl;
        break;
    case EXCEPTION_DIAG:
        cerr<<"Diagnostique inconnu"<<endl;
        break;
    default:
        cerr<<"Autre exception"<<endl;
    }
    }

   sleep(DELAY);
}


