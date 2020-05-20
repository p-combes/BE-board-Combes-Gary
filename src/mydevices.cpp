
#include "mydevices.h"

using namespace std;

//Declaration compteur d'instance pour humidity sol
int AnalogSensorHumiditySoil::cpt=0;

//class Sensor
Sensor::Sensor(int t):Device(),temps(t){}
//class Actuator
Actuator::Actuator(int t):Device(),temps(t){}
//class AnalogSensor
AnalogSensor::AnalogSensor(int t):Sensor(t){
    alea=1;
}
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):AnalogSensor(d),val(t){
}

void AnalogSensorTemperature::run(){
  while(1){
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
AnalogSensorLuminosity::AnalogSensorLuminosity(int t):AnalogSensor(t),val(luminosite_environnement){
}

void AnalogSensorLuminosity::run(){
  while(1){
    val=printemps.luminosite;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Actuator(t),state(LOW){
}

void IntelligentDigitalActuatorLED::run(){
    bool estPasse_low = false;
    bool estPasse_high=false;
while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW){
        estPasse_high=false;
        if (estPasse_low==false){
                luminosite_environnement -=50;
                estPasse_low=true;
        }
        cout << "((((eteint_LED2))))\n";

    }
    else{
        estPasse_low=false;
        if(estPasse_high==false){
           luminosite_environnement += 50;
           estPasse_high=true;
        }
        cout << "((((allume_LED2))))\n";
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
    cpt++;
}

void AnalogSensorHumiditySoil::run(){
  while(1){
        //Initialisation de la plantation si première instanciation
    if (cpt==1){
            Plantation[1]=100;
            Plantation[2]=150;
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
    val=printemps.humidite_air;

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
       /* switch (etatSante)
        {
        case EXCELLENT :
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en parfaite sante\n\n";
            cout<<"******************"<<endl;
            break;
        case BON :
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en bonne sante\n\n";
            cout<<"******************"<<endl;
            break;
        case DESSECHEE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en dessechee\n\n";
            cout<<"******************"<<endl;
            break;
        case NOYEE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en train de se noyer\n\n";
            break;
        case MORTE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est malheureusement morte\n\n";
            cout<<"******************"<<endl;
            break;
        default:
                break;
        }*/
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
 time_t date_debut; //date de changement de vitesse
 time_t date_fin; //date de changement de vitesse
    while(1){
        if(ptrmem!=NULL){
            vitesse_old=vitesse;
            vitesse=*ptrmem;
        }
        if ((distance_arrosoir < TAILLE_POTAGER)){ //tant qu'on est pas au bout du potager, on continue a avancer
            if ((vitesse_old==0)&&(vitesse!=vitesse_old)){//Detecte le demarrage de l'arrosoir
                time(&date_debut);
            }
            time(&date_fin);
            if (difftime(date_fin,date_debut)>0.2){ //Actualisation de la distance de l'arrosoir toutes les 0.2 secondes
                distance_arrosoir+=difftime(date_fin,date_debut)*(double)vitesse*0.01;
                time(&date_debut);
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
    while(1){
        if(ptrmem!=NULL){
            vitesse_old=vitesse;
            vitesse=*ptrmem;
        }
        if ((angle< ANGLE_MAX)){ //tant qu'on est pas a l'angle max, on peut continuer a incliner l'arrosoir
            if ((vitesse_old==0)&&(vitesse!=vitesse_old)){//Detecte le demarrage de l'inclinaison
                time(&date_debut);
            }
            time(&date_fin);
            if (difftime(date_fin,date_debut)>0.2){ //Actualisation de l'angle
                angle+=difftime(date_fin,date_debut)*(double)vitesse*5;
                time(&date_debut);
            }
        }

         //Lien entre angle et humidité du sol au pied de la plante
        if ((distance_arrosoir>(DISTANCE_PLANTE_1-5))&&(distance_arrosoir<(DISTANCE_PLANTE_1+5))){
             Plantation[1]+=(10*angle)/45;
        }
        if ((distance_arrosoir>(DISTANCE_PLANTE_2-5))&&(distance_arrosoir<(DISTANCE_PLANTE_2+5))){
             Plantation[2]+=(10*angle)/45;
        }
        if ((distance_arrosoir>(DISTANCE_PLANTE_3-5))&&(distance_arrosoir<(DISTANCE_PLANTE_3+5))){
             Plantation[3]+=(10*angle)/45;
        }
         sleep(temps);
    }
}

