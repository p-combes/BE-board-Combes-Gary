
#include "mydevices.h"

using namespace std;
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
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
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
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
AnalogSensorLuminosity::AnalogSensorLuminosity(int t):Device(),val(luminosite_environnement),temps(t){
    alea=1;
}

void AnalogSensorLuminosity::run(){
  while(1){
    val=luminosite_environnement;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Device(),state(LOW),temps(t){
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

ExternalDigitalSensorbutton::ExternalDigitalSensorbutton(int t):state(OFF),temps(t){
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
AnalogSensorRadar::AnalogSensorRadar(int t):temps(t),distance(distance_arrosoir){
    alea=1;
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

//classe AnalogActuatorServo
AnalogActuatorServo::AnalogActuatorServo(int t):vitesse(0),temps(t){
}

void AnalogActuatorServo::run(){
 int vitesse_old; //permet de détecter un changement dans la vitesse
 time_t date_debut; //date de changement de vitesse
 time_t date_fin; //date de changement de vitesse
    while(1){
        if(ptrmem!=NULL){
            vitesse_old=vitesse;
            vitesse=*ptrmem;
        }
        if (distance_arrosoir < TAILLE_POTAGER){ //tant qu'on est pas au bout du potager, on continue a avancer
            if ((vitesse_old==0)&&(vitesse!=vitesse_old)){//Detecte le demarrage de l'arrosoir
                time(&date_debut);
            }
            time(&date_fin);
            if (date_debut<date_fin){ //Actualisation de la distance de l'arrosoir toutes les 0.2 secondes
                distance_arrosoir+=difftime(date_debut,date_fin)*vitesse;
                time(&date_debut);
            }
        }
         sleep(temps);
    }
}
