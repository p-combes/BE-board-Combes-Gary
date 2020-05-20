#include "Arosoir.h"

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

//Methode liee a l'arrosage => On incline de 45° l'arrosoir pour arroser, sinon on ne l'incline pas. Le int arrosage définit si on vzeut arroser ou non
///inclinerArrosoir(ARROSAGE,this) => Arrosage (inclinaison de 45°)
///inclinerArrosoir(PAS_ARROSAGE,this)=> Pas arrosage (inclinaison de 0°)
void Arrosoir::inclinerArrosoir(int arrosage,Board* arduino){
    //Arrosage possible uniquement si l'on est pas en deplacement
    if (state != EnDeplacement){
        //Si on veut arroser et qu'on a pas atteint l'angle voulu => on continue a avancer
        if ((arduino->analogRead(PIN_ANGULAR)<ANGLE_MAX)&&(arrosage==ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_AVANT);
        }
        //Si on veut arroser et qu'on est déjà incliné => arret du servo
        else if ((arduino->analogRead(PIN_ANGULAR)>=ANGLE_MAX)&&(arrosage==ARROSAGE)){
            arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
        }
        //Si on veut arreter l'arrosage et que l'angle n'est pas egal à 0=> on recule
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
        else if ((arduino->analogRead(PIN_ANGULAR))>1) {  //si l'angle n'est pas à 0, on est en arrosage ou en train d'arreter
                state=EnArrosage;
        }

    }
    //Si on est en deplacement = pas d'arrosage
    else{
        arduino->digitalWrite(PIN_SERVO_INCLINAISON,VITESSE_INCLINAISON_OFF);
    }
}

