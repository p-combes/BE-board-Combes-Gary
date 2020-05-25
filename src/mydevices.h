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
#define PROBA_PLUIE 70

//Varaiables globales pour la simulation de l'environnement
//static int cpt=0;
static int heure=0;
static int luminosite_environnement=200;
static int humidite_air=70 ;//mesure en % de l'humidit� dans l'air
static int temperature_environnement = 25;

static double distance_arrosoir=0.0;
static double angle_arrosoir=0.0;
static map<int,int> Plantation; //Map associant a chaque plante l'humidite presente à son pied (humidité en mV)
static map<int,int> Luminosite; //Map associant a chaque plante la luminosite percue


void JourneePrintemps (int avancee);


class Sensor : public Device {
protected:
    //temps entre 2 affichages
    int temps;
public :
    Sensor(int t);

};

class Actuator : public Device {
protected :
    int temps;
public:
    Actuator(int t);

};
class AnalogSensor : public Sensor{
protected :

    //fait osciller la valeur du capteur de 1
    int alea;
public:
    //constructeur
    AnalogSensor(int t);
};

// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public AnalogSensor {
private:
  // valeur de temperature mesuree
  int val;


public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};



// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Actuator {
private:
  // etat de la LED
  int state;


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




class AnalogSensorLuminosity : public AnalogSensor{
protected :
    //Valeur de luminosit� capt�e
    int val;
    //Plante associee au capteur de luminosite
    int numeroPlante;
     //Variable statique indiquant le nombre de capteurs cree
    static int cpt;

public:
    //constructeur
    AnalogSensorLuminosity(int t,int plante);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class DigitalActuatorUVLamp : public Actuator{
protected :
    //Etat de la LED
    int state;
    //plante associee a la lampe à UV
    int numeroPlante;
public:
    //constructeur
    DigitalActuatorUVLamp(int t,int plante);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class ExternalDigitalSensorbutton: public Sensor{
protected :
    //Etat du bouton
    int state;

public:
    //constructeur
    ExternalDigitalSensorbutton(int t);
     // thread representant le capteur et permettant de fonctionner independamment de la board
     virtual void run();
};




class AnalogSensorHumiditySoil : public AnalogSensor{
protected :
    //Valeur d'humidite capt�e en V
    int val;
      //Numero associant le senseur à une plante
    int numeroPlante;
    //Variable statique indiquant le nombre de capteur cree
    static int cpt;
public:
    //constructeur
    AnalogSensorHumiditySoil(int t,int plante);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};


class AnalogSensorHumidityAir : public AnalogSensor{
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

class AnalogSensorRadar : public AnalogSensor{
protected :
    //distance entre le radar et l'arrosoir => ou se situe l'arrosoir dans la rangee
    double distance;

public:
    //constructeur
    AnalogSensorRadar(int t);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogActuatorServo : public Actuator{
protected:
    //Vitesse � laquelle l'arrosoir se deplace sur le rail (vitesse<0 => recule, vitesse >0 => avance)
    int vitesse;

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
public :
    //constructeur
    AnalogActuatorServoInclinaison(int t):AnalogActuatorServo(t){}
    //thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

class AnalogSensorAngular : public AnalogSensor{
protected:
    //valeur angle captee au niveau de l'arrosoir
    double angle;
public:
    //constructeur
    AnalogSensorAngular(int t);
    //thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};
#endif
