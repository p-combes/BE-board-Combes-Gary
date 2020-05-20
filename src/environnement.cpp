#include "environnement.h"
#include "cstdlib"




Environnement::Environnement(int temp, int hum_air, int lum){
    temperature = temp;
    humidite_air = hum_air;
    luminosite = lum;
}

void JourneePrintemps(int hour, Environnement* medioambiente,map<int,int> Plantation){
    int probabilite;
    if (hour>7 && hour<21){//c'est la journée
        medioambiente->luminosite = 90000;
        medioambiente->temperature = 16;

    }
    else{
        medioambiente->luminosite = 30;
        medioambiente->temperature= 10;
    }
    cout<<"Luminosite : "<<medioambiente->luminosite<<endl;
    cout<<"Temperature : "<<medioambiente->temperature<<endl;
    probabilite = rand() % 100;
    if (probabilite>70){ //il pleut
        medioambiente->humidite_air=100;
        Plantation[1]+=50;
        Plantation[2]+=50;
        Plantation[3]+=50;
        cout<<"Il pleut"<<endl;
    }else{
        Plantation[1]-=10;
        Plantation[2]-=10;
        Plantation[3]-=10;
    }
    hour=hour+1;
    if (hour>23) {hour =0;}
}

/*void Environnement::gestionEnvironnement(map<int,int> Plantation){
    if (humidite_air == 100){
        Plantation[1]+=50;
        Plantation[2]+=50;
        Plantation[3]+=50;
    }else{
        Plantation[1]-=10;
        Plantation[2]-=10;
        Plantation[3]-=10;
    }
}
*/
