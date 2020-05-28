#include "application_plante.h"

using namespace std;

//Classe ParametrePlante
//Constructeurs
ParametrePlante::ParametrePlante(char* nom, int num,int hum_sol,int hum_air,int temp, int lum){

    if (num>MAX_PLANTE) throw EXCEPTION_NB_PLANTE;
    numero = num;
    humidite_air=hum_air;
    humidite_sol =hum_sol;
    temperature=temp;
    luminosite=lum;
    name=nom;

}

ParametrePlante::ParametrePlante(int hum_sol,int hum_air,int temp, int lum){

    humidite_air=hum_air;
    humidite_sol =hum_sol;
    temperature=temp;
    luminosite=lum;

}

//Classe CaracteristiquePlante
//Constructeurs
CaracteristiquePlante::CaracteristiquePlante(char* nom,int num,int maximum,int minimum,int hum_sol,int hum_air,int temp, int lum):ParametrePlante(nom,num,hum_sol,hum_air,temp,lum){
    max_temp = maximum;
    min_temp = minimum;
    priority=0;
}
CaracteristiquePlante::CaracteristiquePlante(int prio):ParametrePlante("",0,0,0,0,0){
    max_temp = 0;
    min_temp=0;
    priority=prio;
}
//Surcharge de =
CaracteristiquePlante& CaracteristiquePlante::operator =(const CaracteristiquePlante & plantes){
    this->humidite_sol=plantes.humidite_sol;
    this->humidite_air=plantes.humidite_air;
    this->luminosite=plantes.luminosite;
    this->max_temp=plantes.max_temp;
    this->min_temp=plantes.min_temp;
    this->numero=plantes.numero;
    this->temperature=plantes.temperature;
    this->priority=plantes.priority;
    return (*this);
}
//Surcharge des operateurs de comparaison
bool operator == (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2){
    return(plantes1.numero==plantes2.numero); //le numero est propre a la plante
}
//Inferieur signifie un etat de sante moins bon, donc une priorite d'arroser plus grande
bool operator < (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2){
    return((plantes1.priority<plantes2.priority)&&(plantes1.numero!=plantes2.numero));
}

bool operator <= (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2){
    return((plantes1.priority<plantes2.priority)||(plantes1.numero==plantes2.numero));
}

bool operator != (const CaracteristiquePlante  &plantes1, const CaracteristiquePlante  &plantes2){
    return !(plantes1.numero==plantes2.numero);
}
//Definition de la priorité
void CaracteristiquePlante::SetPriority(Board* arduino){
    if (measureSoilHumidity(numero,arduino)>humidite_sol){ //Si on a une humidite sup a l'humidite voule, pas besoin d'arroser
        priority=0;
    }
    else{
        priority=humidite_sol-measureSoilHumidity(numero,arduino); //Plus la difference entre l'humidite reelle et l'humidite voulue est grande, plus on a besoin d'arroser
    }
}
int measureSoilHumidity (int numeroPlante, Board* arduino){

    int humidity;
    int pinToRead;
    switch (numeroPlante) {
        case 1:
            pinToRead=PIN_HUM_SOIL_1;
            break;
        case 2:
            pinToRead=PIN_HUM_SOIL_2;
            break;
        case 3:
            pinToRead=PIN_HUM_SOIL_3;
        default :
            throw EXCEPTION_NB_PLANTE;
    }
    humidity = arduino->analogRead(pinToRead);
    return humidity;
}

int measureAirHumidity(Board* arduino){

    return arduino->analogRead(PIN_HUM_AIR);
}

int measureLuminosity(int numeroPlante, Board* arduino){

    int luminosity;
    int pinToRead;
    switch (numeroPlante) {
        case 1:
            pinToRead=PIN_LUMINOSITE_1;
            break;
        case 2:
            pinToRead=PIN_LUMINOSITE_2;
            break;
        case 3:
            pinToRead=PIN_LUMINOSITE_3;
        default :
            throw EXCEPTION_NB_PLANTE;
    }
    luminosity = arduino->analogRead(pinToRead);
    return luminosity;
}

int measureTemperature(Board* arduino){
    return arduino->analogRead(PIN_TEMP);
}

int measureAngle(Board* arduino){
    return arduino->analogRead(PIN_ANGULAR);
}

int measureDistance(Board* arduino){
    return arduino->analogRead(PIN_RADAR);
}

void displayParameters(ParametrePlante plante, Board * arduino){
    char buf[100];
    sprintf(buf,"***************PARAMETRES DE %s ***************",plante.name);
    arduino->Serial.println(buf);
    sprintf(buf,"temperature %d",plante.temperature,plante.name);
    arduino->Serial.println(buf);
    sprintf(buf,"luminosite %d",plante.luminosite);
    arduino->Serial.println(buf);
    sprintf(buf,"humidite dans l'air %d",plante.humidite_air);
    arduino->Serial.println(buf);
    sprintf(buf,"humidite dans le sol %d",plante.humidite_sol);
    arduino->Serial.println(buf);
    if (plante.humidite_air>100-1 && plante.humidite_air <100+2) {
       sprintf(buf,"Il pleut ! ");
    arduino->Serial.println(buf);

    }
}

int runDiagnosis(CaracteristiquePlante modele, Board* arduino){

    int hum_air=measureAirHumidity(arduino);

    int hum_sol=measureSoilHumidity(modele.numero,arduino);

    int temp = measureTemperature(arduino);

    int lum = measureLuminosity(modele.numero,arduino);

    action act= NE_RIEN_FAIRE;

    ParametrePlante parametre (modele.name,modele.numero,hum_sol,hum_air,temp,lum);
    displayParameters(parametre,arduino);


    if (parametre.temperature>modele.max_temp || parametre.temperature<modele.min_temp || parametre.humidite_sol>HUMIDITE_SOL_MAX) //La plante est morte
    {
        act=MORTE;
    }
    else {
        if (hum_sol < modele.humidite_sol-MARGE_HUM_SOL) {
            if (hum_air <modele.humidite_air-MARGE_HUM_AIR){
                act = NE_RIEN_FAIRE; //le sol n'est pas assez humide mais il va pleuvoir donc on attend
                if (lum<modele.luminosite -MARGE_LUM) {
                        act = ALLUMER_LAMPE; //il n'y a pas assez de luminosite
                } else if (lum>modele.luminosite+MARGE_LUM) {
                        act = ETEINDRE; //Trop de luminosite
                }
            }
            else{
                act=ARROSER; //le sol n'est pas assez humide et il ne pleut pas
                if (lum<modele.luminosite -MARGE_LUM) {
                        act = ALLUMER_ARROSER;
                } else if (lum>modele.luminosite+MARGE_LUM) {
                        act = ETEINDRE_ARROSER;
                }
            }
        } else { //Pas besoin d'arroser
        if (lum<modele.luminosite -MARGE_LUM) {
                        act = ALLUMER_LAMPE;
                } else if (lum>modele.luminosite+MARGE_LUM) {
                        act = ETEINDRE;
                }
        }
    }
    return act;
}
void takeDecision(int diagnostique, CaracteristiquePlante plantes, Arrosoir arros,Board* arduino,set<CaracteristiquePlante> &Decisions,int screen){
char buf[100];
 switch (diagnostique){
    case NE_RIEN_FAIRE :
        if (arros.detecterEnArrosage(arduino)==true){
        }
        else{
            Decisions.erase(plantes);
        }
        break;

    case ALLUMER_LAMPE :
         if (arros.detecterEnArrosage(arduino)==true){ //Si on est tjrs en train d'arroser => On regarde tjrs au ralenti
        }
        else{ //Sinon, on peut revenir a la normale et erase la decision
            Decisions.erase(plantes);
        }
        AllumerLampe(plantes.numero,arduino);
        break;
    case ARROSER :
        Decisions.insert(plantes);
        break;
    case ALLUMER_ARROSER :
        Decisions.insert(plantes);
        AllumerLampe(plantes.numero,arduino);
        break;
    case ETEINDRE_ARROSER :
        Decisions.insert(plantes);
        EteindreLampe(plantes.numero,arduino);
        break;
    case MORTE:
         if (arros.detecterEnArrosage(arduino)==true){
        }
        else{
            Decisions.erase(plantes);
        }
        sprintf(buf,"%s est morte",plantes.name);
        arduino->bus.write(screen,buf,100);
        break;
    case ETEINDRE:
         if (arros.detecterEnArrosage(arduino)==true){
        }
        else{
            Decisions.erase(plantes);
        }
        EteindreLampe(plantes.numero,arduino);
        break;
    default :
        throw EXCEPTION_DIAG;
    }
}

void applyDecision(set<CaracteristiquePlante> Decisions,Arrosoir arros,CaracteristiquePlante plante1,CaracteristiquePlante plante2, Board* arduino){
if (Decisions.empty()){ //Si la liste des decisions est vide => on ne bouge pas de là ooù l'on est
        JourneeTest(NORMALE);
        arduino->digitalWrite(PIN_SERVO_ARROSOIR,VITESSE_ARROSOIR_ARRET);
        arros.inclinerArrosoir(PAS_ARROSAGE,arduino);
        cout<<"Je n'arrose personne"<<endl;
    }
else{
//Sinon recherche dans la liste des decisions a prendre, la plante la plus prioritaire
CaracteristiquePlante MaxPriority(INT_MAX);
set <CaracteristiquePlante>::iterator it;
    for(it=Decisions.begin();it!=Decisions.end();it++){
    if ((*it)<MaxPriority){
        MaxPriority=(*it);
    }
    }
    //On applique alors l'arrosage a la plante la plus prioritaire
    if (MaxPriority==plante1){
            JourneeTest(RALENTIE);
            arros.arroser(plante1.numero,plante1.humidite_sol+150,arduino); //On arrose plus que la limite
            cout<<"Je choisis d'arroser "<<plante1.name<<endl;
        }
    else if (MaxPriority==plante2){
            JourneeTest(RALENTIE);
            arros.arroser(plante2.numero,plante2.humidite_sol+150,arduino);
            cout<<"Je choisis d'arroser "<<plante2.name<<endl;
        }
    else{ //si ça ne correspond pas a une plante, on leve une exception
        throw EXCEPTION_NAME_PLANT;
    }
}
}

