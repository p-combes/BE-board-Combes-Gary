#include "Arrosoir.h"

//Constructeur
Arrosoir::Arrosoir():state(Arrete){
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
          //si on est à côté de la plante => arrêt
          else if((arduino->analogRead(PIN_RADAR)<=positionPlante+2)||(arduino->analogRead(PIN_RADAR)>=positionPlante-2)){
            arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_ARRET);
            state=Arrete; //Mise a jour de l'etat de l'arrosoir
          }
    }
}

//Methode liee a l'arrosage
void Arrosoir::inclinerArrosoir(double angle,Board* arduino, AnalogActuatorServoInclinaison* servo){
    //Arrosage possible uniquement si l'on est pas en deplacement
    if (state != EnDeplacement){
            //Si on a pas atteint l'inclinaison souhaitee, on continue a avancer
        if ((servo->angle)<angle){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_ON);
        }
        //Sinon on arrete le deplacement
    else{
        arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
    }
    //Mise a jour de l'etat de l'arrosoir
    if (((servo->angle)==0)&&(state==EnArrosage)){ //si on a fini l'arrosage => l'arrosoir passe en arret
            state=Arrete;
    }
    else if ((servo->angle)!=0) {  //si l'angle n'est pas à 0, on est en arrosage
            state=EnArrosage;
    }

    }
}

