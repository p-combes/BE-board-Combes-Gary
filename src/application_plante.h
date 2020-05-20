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

#define EXCEPTION_NB_PLANTE 5
#define MARGE_HUM_SOL 20
#define MARGE_HUM_AIR 15
#define MARGE_TEMP 5
#define MARGE_LUM 1000
#define HUMIDITE_SOL_MAX 200 //au dela de cette valeur les plantes sont noyes, il a trop plu
enum action {NE_RIEN_FAIRE,ALLUMER_LAMPE,ARROSER,ALLUMER_ARROSER,ETEINDRE,ETEINDRE_ARROSER};
class ParametrePlante {
public :
    int numero;
    int humidite_sol;
    int humidite_air;
    int temperature;
    int luminosite;

    ParametrePlante(int num,int hum_sol,int hum_air,int temp, int lum);
    ParametrePlante(int hum_sol,int hum_air,int temp, int lum);
};

class CaracteristiquePlante : public ParametrePlante {
public :
    int max_temp; // temperature au delà de laquelle la plante meure
    int min_temp; //temperature au deça de laquelle la plante meure
    CaracteristiquePlante (int maximum, int minimum,int hum_sol,int hum_air,int temp, int lum);
};
int measureSoilHumidity (int numeroPlante, Board* arduino);
int measureAirHumidity(Board* arduino);
int measureLuminosity(Board* arduino);
int measureTemperature(Board* arduino);

int runDiagnosis (int numeroPlante, ParametrePlante modele, Board* arduino);
