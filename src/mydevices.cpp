
#include "mydevices.h"

using namespace std;

void JourneePrintemps(int avancee){

        int probabilite;
        cout<<"Il est :"<<heure<<" h"<<endl;
        if (heure>7 && heure<21){//c'est la journée
            luminosite_environnement = 20000;
            temperature_environnement = 16;

        }
        else{ //c'est la nuit
            luminosite_environnement = 30;
            temperature_environnement= 10;
        }
        if (avancee==NORMALE){
            probabilite = rand() % 100; // il faudra initialiser la seed pour avoir une meilleure proba
            if (probabilite>PROBA_PLUIE){ //il pleut
                humidite_air=100;
                Plantation[1]+=1;
                Plantation[2]+=1;
                Plantation[3]+=1;
            }else{
                humidite_air = 70;
                for(int i=1;i<4;i++){
                    if ((Plantation[i]-=10)<=0){
                        Plantation[i]=0;
                    }
                    else{
                        Plantation[i]-=10;
                    }
                }
            }
            heure=heure+1;
            if (heure>23) {heure =0;}
    }
}

void JourneeTest(int avancee){

        cout<<"Il est :"<<heure<<" h"<<endl;
        if ((heure>7 && heure<12)||(heure>15 && heure<21)){//c'est la journée
            luminosite_environnement = 20000;
            temperature_environnement = 16;

        }
        else if ((heure<=15)&&(heure>=12)){
            luminosite_environnement=8000;
            temperature_environnement=16;
        }
        else{ //c'est la nuit
            luminosite_environnement = 30;
            temperature_environnement= 10;
        }
        if (avancee==NORMALE){
            if ((heure>21)&&(heure<23)){
                humidite_air=100;
                Plantation[1]+=10;
                Plantation[2]+=10;
                Plantation[3]+=10;
            }
            else{
                humidite_air = 70;
                for(int i=1;i<4;i++){
                    if ((Plantation[i]-=10)<=0){
                        Plantation[i]=0;
                    }
                    else{
                        Plantation[i]-=10;
                    }
                }
            }
            heure=heure+1;
            if (heure>23) {heure =0;}
    }
}

//Declaration compteur d'instance pour humidity sol
int AnalogSensorHumiditySoil::cpt=0;
//Declaration compteur d'instance pour luminosity sol
int AnalogSensorLuminosity::cpt=0;
//class Sensor
Sensor::Sensor(int t):Device(),temps(t){}
//class Actuator
Actuator::Actuator(int t):Device(),temps(t){}
//class AnalogSensor
AnalogSensor::AnalogSensor(int t):Sensor(t){
    alea=1;
}
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d):AnalogSensor(d){
}

void AnalogSensorTemperature::run(){
  while(1){
    val=temperature_environnement;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Actuator(t),state(LOW){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}



//class AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int t,int plante):AnalogSensor(t),val(luminosite_environnement),numeroPlante(plante){
}

void AnalogSensorLuminosity::run(){
  while(1){
    //Initialisation de la plantation si première instanciation
    if (cpt==1){
            Luminosite[1]=luminosite_environnement;
            Luminosite[2]=luminosite_environnement;
            Luminosite[3]=luminosite_environnement;
            cpt=2; //Empeche une autre initialisation
    }
    val=Luminosite[numeroPlante];
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class DigitalActuatorUVLamp
DigitalActuatorUVLamp::DigitalActuatorUVLamp(int t,int plante):Actuator(t),state(LOW),numeroPlante(plante){
}

void DigitalActuatorUVLamp::run(){
while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW){
        Luminosite[numeroPlante] = luminosite_environnement;
    }
    else{
        Luminosite[numeroPlante] = luminosite_environnement + 50;
        cout<<"Lampe "<<numeroPlante<<" allumee"<<endl;
    }
    sleep(temps);
    }
}

//Classe ExternalDigitalSensorbutton

ExternalDigitalSensorbutton::ExternalDigitalSensorbutton(int t): Sensor(t),state(OFF){
}

void ExternalDigitalSensorbutton::run(){
    while(1){
        if(ifstream("on.txt")){
            state=ON;
        }
        else{
            state=OFF;
        }
        if(ptrmem!=NULL)
        *ptrmem=state;
        sleep(temps);
    }
}
//Classe AnalogSensorRadar
AnalogSensorRadar::AnalogSensorRadar(int t):AnalogSensor(t),distance(distance_arrosoir){
}



//class AnalogSensorHumiditySoil
AnalogSensorHumiditySoil::AnalogSensorHumiditySoil(int t,int plante):AnalogSensor(t),val(luminosite_environnement){
    alea=1;
    numeroPlante=plante;
    cpt=1;
}

void AnalogSensorHumiditySoil::run(){
  while(1){
        //Initialisation de la plantation si première instanciation

    if (cpt==1){
            Plantation[1]=110;
            Plantation[2]=400;
            Plantation[3]=200;
            cpt=2; //Empeche une autre initialisation
    }

    val=Plantation[numeroPlante];
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class AnalogSensorHumidityAir

AnalogSensorHumidityAir::AnalogSensorHumidityAir(int t):AnalogSensor(t),val(humidite_air){
    alea=1;
}
void AnalogSensorHumidityAir::run(){
  while(1){
    val=humidite_air;

    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

// classe I2CActuatorLCD
LCDScreen::LCDScreen (int num):Device(),numeroPlante(num){
  }

void LCDScreen::run(){

  while(1){

    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
    cout << "---screen LCD :"<< buf << endl;
    }
    sleep(1);
    }
}

void AnalogSensorRadar::run(){
    while(1){
    distance=distance_arrosoir;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=distance+alea;
    sleep(temps);
  }
}


AnalogActuatorServo::AnalogActuatorServo(int t): Actuator(t),vitesse(0){
}

//classe AnalogActuatorServoRail

void AnalogActuatorServoRail::run(){
 int vitesse_old; //permet de dï¿½tecter un changement dans la vitesse
 int vitesse_abs; //permet de gerer les vitesses negatives
 time_t date_debut; //date de changement de vitesse
 time_t date_fin; //date de changement de vitesse
    while(1){
        if(ptrmem!=NULL){
            vitesse_old=vitesse;
            vitesse=*ptrmem;
        }
        switch(vitesse){
    case VITESSE_ARROSOIR_RECULE_LENT: //Gestion vitesses negatives (on ne peut pas ecrire de chiffre<0 sur les PIN
        vitesse=-20;
        break;
    case VITESSE_ARROSOIR_RECULE_RAPIDE:
        vitesse=-40;
        break;
        }
        vitesse_abs=abs(vitesse);//Gestion si vitesse negative
        if ((distance_arrosoir < TAILLE_POTAGER)){ //tant qu'on est pas au bout du potager, on continue a avancer
            if ((vitesse_old==0)&&(vitesse_abs!=vitesse_old)){//Detecte le demarrage de l'arrosoir
                time(&date_debut);
            }
            time(&date_fin);
            //Si on est a l'arret, il ne faut plus actualiser distance arrosoir et remettre les dates de fin et debut a 0
            if ((vitesse_old==0)&&(vitesse_abs==vitesse_old)){
                distance_arrosoir=distance_arrosoir;
                date_debut=0;
                date_fin=0;
            }
            else{ //Si on est pas a l'arret, on actualise la distance toute les 0.2 secondes
                if (difftime(date_fin,date_debut)>0.2){ //Actualisation de la distance de l'arrosoir toutes les 0.2 secondes
                    if (vitesse>0)
                        distance_arrosoir+=difftime(date_fin,date_debut)*(double)vitesse_abs*0.01; //cas vitesse >0
                    else
                        distance_arrosoir-=difftime(date_fin,date_debut)*(double)vitesse_abs*0.01; //cas vitesse <0

                    time(&date_debut);
                }
            }
        }
         sleep(temps);
    }
}

//Classe AnalogActuatorServoInclinaison
void AnalogActuatorServoInclinaison::run(){
 int vitesse_old; //permet de dï¿½tecter un changement dans la vitesse
 time_t date_debut; //date de changement de vitesse
 time_t date_fin; //date de changement de vitesse
 int vitesse_abs; //Si vitesse <0
    while(1){
        if(ptrmem!=NULL){
            vitesse_old=vitesse;
            vitesse=*ptrmem;
        }
        if (vitesse==VITESSE_INCLINAISON_ARRIERE){vitesse=-1;} //Gestion vitesse<0
        vitesse_abs=abs(vitesse);//Gestion si vitesse negative
        if ((angle_arrosoir< ANGLE_MAX)||((angle_arrosoir>=ANGLE_MAX)&&(vitesse<0))){ //tant qu'on est pas a l'angle max, on peut continuer a incliner l'arrosoir
            if ((vitesse_old==0)&&(vitesse_abs!=vitesse_old)){//Detecte le demarrage de l'inclinaison
                time(&date_debut);
            }
            time(&date_fin);
             //Si on est a l'arret, il ne faut plus actualiser angle arrosoir et remettre les dates de fin et debut a 0
            if ((vitesse_old==0)&&(vitesse_abs==vitesse_old)){
                angle_arrosoir=angle_arrosoir;
                date_debut=0;
                date_fin=0;
            }
            else{
                if (difftime(date_fin,date_debut)>0.2){ //Actualisation de l'angle si on est pas a l'arret
                    if (vitesse>0)
                        angle_arrosoir+=difftime(date_fin,date_debut)*(double)vitesse_abs*5;
                    else
                        angle_arrosoir-=difftime(date_fin,date_debut)*(double)vitesse_abs*5;
                    time(&date_debut);
                }
            }
        }
        //Empeche l'angle d'etre <0
        if (angle_arrosoir<0.0){angle_arrosoir=0.0;}

         //Lien entre angle et humidité du sol au pied de la plante
        if ((distance_arrosoir>(DISTANCE_PLANTE_1-5))&&(distance_arrosoir<(DISTANCE_PLANTE_1+5))){
             Plantation[1]+=(10*angle_arrosoir)/45;
        }
        if ((distance_arrosoir>(DISTANCE_PLANTE_2-5))&&(distance_arrosoir<(DISTANCE_PLANTE_2+5))){
             Plantation[2]+=(10*angle_arrosoir)/45;
        }
        if ((distance_arrosoir>(DISTANCE_PLANTE_3-5))&&(distance_arrosoir<(DISTANCE_PLANTE_3+5))){
             Plantation[3]+=(10*angle_arrosoir)/45;
        }
         sleep(temps);
    }
}

//classe AnalogSensorAngular
AnalogSensorAngular::AnalogSensorAngular(int t):AnalogSensor(t),angle(angle_arrosoir){
}

void AnalogSensorAngular::run(){
    while(1){
    angle=angle_arrosoir;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=angle+alea;
    sleep(temps);
  }
}
