#include "Arosoir.h"

//Constructeur
Arrosoir::Arrosoir():state(Arrete),estArrive(false),finArrosage(false){
}

//Methodes liees au deplacement
void Arrosoir::deplacerArrosoir(double positionPlante, Board* arduino){
    //deplacement possible si l'on est pas en train d'arroser
    if (state != EnArrosage){
            //Si on est loin de la plante => on avance ou recule rapidement
          if (arduino->analogRead(PIN_RADAR)<positionPlante-5){
             arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_AVANCE_RAPIDE);
              state=EnDeplacement; //Mise a jour de l'etat de l'arrosoir
          }
          else if(arduino->analogRead(PIN_RADAR)>positionPlante+5){
             arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_RECULE_RAPIDE);
              state=EnDeplacement; //Mise a jour de l'etat de l'arrosoir
          }
          //Si on s'approche de la plante, on va plus lentement
          else if((arduino->analogRead(PIN_RADAR)<positionPlante-2)&&(arduino->analogRead(PIN_RADAR)>=positionPlante-5)){
            arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_AVANCE_LENT);
             state=EnDeplacement; //Mise a jour de l'etat de l'arrosoir
          }
          else if((arduino->analogRead(PIN_RADAR)>positionPlante+2)&&(arduino->analogRead(PIN_RADAR)<=positionPlante+5)){
            arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_RECULE_LENT);
             state=EnDeplacement; //Mise a jour de l'etat de l'arrosoir
          }
          //si on est � c�t� de la plante => arr�t
          else if((arduino->analogRead(PIN_RADAR)<=positionPlante+2)||(arduino->analogRead(PIN_RADAR)>=positionPlante-2)){
            arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_ARRET);
            state=Arrete; //Mise a jour de l'etat de l'arrosoir
          }
    }
}

//Methode liee a l'arrosage => On incline de 45� l'arrosoir pour arroser, sinon on ne l'incline pas. Le int arrosage d�finit si on vzeut arroser ou non
///inclinerArrosoir(ARROSAGE,this) => Arrosage (inclinaison de 45�)
///inclinerArrosoir(PAS_ARROSAGE,this)=> Pas arrosage (inclinaison de 0�)
void Arrosoir::inclinerArrosoir(int arrosage,Board* arduino){
    //Arrosage possible uniquement si l'on est pas en deplacement
    if (state != EnDeplacement){
        //Si on veut arroser et qu'on a pas atteint l'angle voulu => on continue a avancer
        if ((arduino->analogRead(PIN_ANGULAR)<ANGLE_MAX)&&(arrosage==ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_AVANT);
        }
        //Si on veut arroser et qu'on est d�j� inclin� => arret du servo
        else if ((arduino->analogRead(PIN_ANGULAR)>=ANGLE_MAX)&&(arrosage==ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
        }
        //Si on veut arreter l'arrosage et que l'angle n'est pas egal � 0=> on recule
         else if (((arduino->analogRead(PIN_ANGULAR))>1)&&(arrosage==PAS_ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_ARRIERE);
        }
        //Enfin, si on veut arreter l'arrosage et qu'on est deja a 0=> on arrete le servo
        else if (((arduino->analogRead(PIN_ANGULAR))<=1)&&(arrosage==PAS_ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
        }
        //Mise a jour de l'etat de l'arrosoir
        if (((arduino->analogRead(PIN_ANGULAR))<=1)&&(state==EnArrosage)&&(arrosage==PAS_ARROSAGE)){ //si on a fini l'arrosage => l'arrosoir passe en arret
                state=Arrete;
        }
        else if ((arduino->analogRead(PIN_ANGULAR))>1) {  //si l'angle n'est pas � 0, on est en arrosage ou en train d'arreter
                state=EnArrosage;
        }

    }
    //Si on est en deplacement = pas d'arrosage
    else{
        arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
    }
}
//Methhode d'arrosage complet (deplacement + inclinaison)
void Arrosoir::arroser(int numeroPlante, int humiditeVoulue, Board* arduino){
double distVoulue; //distance souhaitee
char buf[100];
int pinToRead;
switch (numeroPlante){ //association numeroPlante//Distance souhaitee
case 1:
    distVoulue=DISTANCE_PLANTE_1;
    pinToRead=PIN_HUM_SOIL_1;
    break;
case 2:
    distVoulue=DISTANCE_PLANTE_2;
    pinToRead=PIN_HUM_SOIL_2;
    break;
case 3:
    distVoulue=DISTANCE_PLANTE_3;
    pinToRead=PIN_HUM_SOIL_3;
    break;
default:
   throw EXCEPTION_NB_PLANTE;
}
//Mise a jour des valeurs booleennes
if (abs((int)(distVoulue-(arduino->analogRead(PIN_RADAR))))<=2){ //Mise a jour de est arrive
    estArrive=true;
}
if (humiditeVoulue<=(arduino->analogRead(pinToRead))){
    finArrosage=true;
}
if (estArrive==false){
    deplacerArrosoir(distVoulue,arduino); //si on est pas en face de la plante, on deplace l'arrosoir
    inclinerArrosoir(PAS_ARROSAGE,arduino);
}
else{
    if (finArrosage==false){
        inclinerArrosoir(ARROSAGE,arduino); //si on est en face, si on a pas fini d'arroser (Humidite<HumiditeVoulue), on arrose
    }
    else{
        inclinerArrosoir(PAS_ARROSAGE,arduino); //sinon on arrete
    }
}
}

