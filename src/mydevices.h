#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "core_simulation.h"



#define PIN_TEMP 5
#define PIN_LED_1 6
#define PIN_LUM 7
#define PIN_LED_2 8
#define PIN_BOUTON 9
#define PIN_HUM_AIR 10
#define PIN_HUM_SOIL 11

#define I2C_SCREEN 1
#define I2C_LCD 2

static int luminosite_environnement=200;
static int humidite_sol=100; //mesure en mV de l'humidité dans le sol
static int humidite_air=70 ;//mesure en % de l'humidité dans l'air

enum etatSante {EXCELLENT, BON, DESSECHEE, NOYEE,MORTE};
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
    //Valeur d'humidite captée en V
    int val;

public:
    //constructeur
    AnalogSensorHumiditySoil(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogSensorHumidityAir : public AnalogSensorHumidity{
protected :
    //Valeur d'humidite captée en %
    int val;

public:
    //constructeur
    AnalogSensorHumidityAir(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

//écran LCD positionne sous chaque plante
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
#endif
