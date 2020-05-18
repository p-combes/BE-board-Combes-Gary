#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include<map>
#include "core_simulation.h"

//Varaiables globales pour la simulation de l'environnement
static int luminosite_environnement=200;
static int humidite_air=70 ;//mesure en % de l'humidit� dans l'air
enum etatSante {EXCELLENT, BON, DESSECHEE, NOYEE,MORTE};
static double distance_arrosoir=0.0;
static map<int,int> Plantation; //Map associant a chaque plante l'humidite presente à son pied (humidité en mV)
// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de temperature mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;

public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d,int  t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;

public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];

public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

class AnalogSensorLuminosity : public Device{
protected :
    //Valeur de luminosit� capt�e
    int val;
    //temps entre 2 affichages de la luminosite
    int temps;
    //fait osciller la valeur du capteur de 1
    int alea;
public:
    //constructeur
    AnalogSensorLuminosity(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class IntelligentDigitalActuatorLED : public Device{
protected :
    //Etat de la LED
    int state;
    //temps entre 2 affichages de l'�tat de la LED
    int temps;
public:
    //constructeur
    IntelligentDigitalActuatorLED(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class ExternalDigitalSensorbutton: public Device{
protected :
    //Etat du bouton
    int state;
    //temps de maj du bouton
    int temps;
public:
    //constructeur
    ExternalDigitalSensorbutton(int t);
     // thread representant le capteur et permettant de fonctionner independamment de la board
     virtual void run();
};


class AnalogSensorHumidity : public Device{
protected :
    //temps entre 2 affichages de la luminosite
    int temps;
    //fait osciller la valeur du capteur de 1
    int alea;
public:
    //constructeur
    AnalogSensorHumidity(int t);
};

class AnalogSensorHumiditySoil : public AnalogSensorHumidity{
protected :
    //Valeur d'humidite capt�e en V
    int val;
      //Numero associant le senseur à une plante
    int numeroPlante;

public:
    //constructeur
    AnalogSensorHumiditySoil(int t,int plante);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogSensorHumidityAir : public AnalogSensorHumidity{
protected :
    //Valeur d'humidite capt�e en %
    int val;

public:
    //constructeur
    AnalogSensorHumidityAir(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

//�cran LCD positionne sous chaque plante
class LCDScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  int etatSante;
    int numeroPlante;
    char buf[I2C_BUFFER_SIZE];
public:
  // constructeur
  LCDScreen (int num);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

class AnalogSensorRadar : public Device{
protected :
     //temps entre 2 affichages de l'�tat de la valeur
    int temps;
    //distance entre le radar et l'arrosoir => ou se situe l'arrosoir dans la rangee
    double distance;
    //fait osciller la valeur du capteur de 1
    int alea;
public:
    //constructeur
    AnalogSensorRadar(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogActuatorServo : public Device{
protected:
    //Vitesse � laquelle l'arrosoir se deplace sur le rail (vitesse<0 => recule, vitesse >0 => avance)
    int vitesse;
    //temps entre 2 affichages de l'�tat de la vitesse
    int temps;
public:
    //constructeur
    AnalogActuatorServo(int t);
    //thread representant le capteur et permettant de fonctionner independamment de la board
};

class AnalogActuatorServoRail : public AnalogActuatorServo{
public:
    //constructeur
    AnalogActuatorServoRail(int t):AnalogActuatorServo(t){}
    //thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogActuatorServoInclinaison : public AnalogActuatorServo{
protected :
    //angle d'inclinaison
    double angle;
public :
    //constructeur
    AnalogActuatorServoInclinaison(int t):AnalogActuatorServo(t),angle(0.0){}
    //thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};
#endif
