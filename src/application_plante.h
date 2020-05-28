#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include <climits>
#include<map>
#include "core_simulation.h"
#include "mydevices.h"
#include "Arosoir.h"
#include "lampeUV.h"


#define EXCEPTION_NAME_PLANT 10
#define EXCEPTION_DIAG 6
#define MARGE_HUM_SOL 20
#define MARGE_HUM_AIR 15
#define MARGE_TEMP 5
#define MARGE_LUM 1000
#define HUMIDITE_SOL_MAX 10000//au dela de cette valeur les plantes sont noyes, il a trop plu


//enum précisant les actions faisable à l'issue du diagnostic
enum action {NE_RIEN_FAIRE,ALLUMER_LAMPE,ARROSER,ALLUMER_ARROSER,ETEINDRE,ETEINDRE_ARROSER,MORTE};

//Classe ParametrePlante, regroupe les paramètres actuels de la plante
class ParametrePlante {
public :
    int numero;
    int humidite_sol;
    int humidite_air;
    int temperature;
    int luminosite;
    char* name;
    ParametrePlante(char* nom,int num,int hum_sol,int hum_air,int temp, int lum);
    ParametrePlante(int hum_sol,int hum_air,int temp, int lum);
};
//Classe CaracteristiquePlante, hérite de paramètre plante, sert à créer des fiches types avec les seuils à ne pas dépasser
class CaracteristiquePlante : public ParametrePlante {
public :
    int max_temp; // temperature au delà de laquelle la plante meure
    int min_temp; //temperature au deça de laquelle la plante meure
    int priority; //Gestion de la priorite d'arrosage de la plante
    //Constructeur pour une plante avec priorité maximum
    CaracteristiquePlante(int prio);
    CaracteristiquePlante (char* nom,int num,int maximum, int minimum,int hum_sol,int hum_air,int temp, int lum);
    //Surcharge de l'operateur =
    CaracteristiquePlante & operator =(const CaracteristiquePlante & plantes);
    //Definition de la priorité
    void SetPriority(Board* arduino);
};
//Surcharge des operateurs de comparaison pour evaluer quelle plante a le plus besoin d'etre arrosee
bool operator == (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2);
bool operator < (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2);
bool operator <= (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2);
bool operator != (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2);

//Fonction de mesure des paramètres environnementaux et du système
int measureSoilHumidity (int numeroPlante, Board* arduino);
int measureAirHumidity(Board* arduino);
int measureLuminosity(Board* arduino);
int measureTemperature(Board* arduino);
int measureAngle(Board * arduino);
int measureDistance(Board* arduino);

//Fonction d'affichage
void displayParameters (ParametrePlante plante);
//Fonction permettant de poser un diagnostic sur une plante, évalue les actions à affectuer
int runDiagnosis (CaracteristiquePlante modele, Board* arduino);
void takeDecision(int diagnostique, CaracteristiquePlante plantes,Arrosoir arros, Board* arduino,set<CaracteristiquePlante> &Decisions, int screen);//Met en relation l'action a mener avec les actuators a actionner
void applyDecision(set<CaracteristiquePlante> Decisions,Arrosoir arros,CaracteristiquePlante plante1,CaracteristiquePlante plante2, Board* arduino); //Gere la coordination des differentes actions a mener
