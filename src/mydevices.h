#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include "core_simulation.h"

static int luminosite_environnement=200;
static double distance_arrosoir=0.0;
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
    //Valeur de luminosité captée
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
    //temps entre 2 affichages de l'état de la LED
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

class AnalogSensorRadar : public Device{
protected :
     //temps entre 2 affichages de l'état de la valeur
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
    //Vitesse à laquelle l'arrosoir se deplace sur le rail (vitesse<0 => recule, vitesse >0 => avance)
    int vitesse;
    //temps entre 2 affichages de l'état de la vitesse
    int temps;
public:
    //constructeur
    AnalogActuatorServo(int t);
    //thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};
#endif
