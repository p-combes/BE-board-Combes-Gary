#include "environnement.h"
#include "cstdlib"




Environnement::Environnement(int temp, int hum_air, int lum){
    temperature = temp;
    humidite_air = hum_air;
    luminosite = lum;
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
