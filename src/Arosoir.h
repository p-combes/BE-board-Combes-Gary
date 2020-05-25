#ifndef ARROSOIR_H_INCLUDED
#define ARROSOIR_H_INCLUDED
#include "core_simulation.h"
#include "mydevices.h"
enum EtatArrosoir {Arrete, EnDeplacement, EnArrosage};
//classe représentant l'arrosoir, contenant les méthodes permettant l'arrosage
class Arrosoir{
protected :
    //Definit l'etat actuel de l'arrosoir (arrete, en deplacement ou en arrosage) => on ne peut pas arroser et se deplacer en meme temps
    EtatArrosoir state;
    //Indique si l'arrosoir est arrive à la destination voulue ou non
    bool estArrive;
    //Indique si l'arrosoir a fini l'arrosage
    bool finArrosage;
public:
    //Constructeur
    Arrosoir();
    //methodes pour l'arrosage
    void deplacerArrosoir(double positionPlante, Board* arduino);
    void inclinerArrosoir(int arrosage, Board* arduino);
    void arroser(int numeroPlante, int humiditeVoulue, Board* arduino);
    //Methode retournant true si on est en arrosage, false sinon
    bool detecterEnArrosage(Board* arduino);
};


#endif // ARROSOIR_H_INCLUDED
