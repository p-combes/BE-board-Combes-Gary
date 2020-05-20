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
public:
    //Constructeur
    Arrosoir();
    //methodes pour l'arrosage
    void deplacerArrosoir(double positionPlante, Board* arduino);
    void inclinerArrosoir(int arrosage, Board* arduino);
};


#endif // ARROSOIR_H_INCLUDED
