#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include<map>
#include "core_simulation.h"
#include "mydevices.h"

class Environnement {
public :
    int temperature;
    int humidite_air;
    int luminosite;

    Environnement(int temp, int hum_air, int luminosite);


    void gestionEnvironnement (map <int,int> Plantation);

};


static Environnement printemps(20,50,10000);

#endif
