#include "application_plante.h"

using namespace std;


ParametrePlante::ParametrePlante(int num,int hum_sol,int hum_air,int temp, int lum){

    if (num>MAX_PLANTE) throw EXCEPTION_NB_PLANTE;
    numero = num;
    humidite_air=hum_air;
    humidite_sol =hum_sol;
    temperature=temp;
    luminosite=lum;

}

ParametrePlante::ParametrePlante(int hum_sol,int hum_air,int temp, int lum){

    humidite_air=hum_air;
    humidite_sol =hum_sol;
    temperature=temp;
    luminosite=lum;

}

CaracteristiquePlante::CaracteristiquePlante(int maximum,int minimum,int hum_sol,int hum_air,int temp, int lum):ParametrePlante(hum_sol,hum_air,temp,lum){
    max_temp = maximum;
    min_temp = minimum;

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

int measureLuminosity(Board* arduino){
    return arduino->analogRead(PIN_LUMINOSITE);
}

int measureTemperature(Board* arduino){
    return arduino->analogRead(PIN_TEMP);
}

void displayParameters(ParametrePlante plante, Board * arduino){
    char buf[100];
    sprintf(buf,"temperature %d",plante.temperature);
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

int runDiagnosis(int numeroPlante, CaracteristiquePlante modele, Board* arduino){

    int hum_air=measureAirHumidity(arduino);

    int hum_sol=measureSoilHumidity(numeroPlante,arduino);

    int temp = measureTemperature(arduino);

    int lum = measureLuminosity(arduino);

    action act= NE_RIEN_FAIRE;

    ParametrePlante parametre (numeroPlante,hum_sol,hum_air,temp,lum);
    displayParameters(parametre,arduino);


    if (parametre.temperature>modele.max_temp || parametre.temperature<modele.min_temp || parametre.humidite_sol>HUMIDITE_SOL_MAX) //La plante est morte
    {
        cout<<"La plante est morte"<<endl;
    }
    else {
        if (hum_sol < modele.humidite_sol-MARGE_HUM_SOL) {
            if (hum_air <modele.humidite_air-MARGE_HUM_AIR){
                act = NE_RIEN_FAIRE; //le sol n'est pas assez humide mais il va pleuvoir donc on attend
                if (lum<modele.luminosite -MARGE_LUM) {
                        act = ALLUMER_LAMPE; //il n'y a pas assez de luminosite
                } else if (lum>modele.luminosite+MARGE_LUM) {
                        act = ETEINDRE;
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
        } else {
        if (lum<modele.luminosite -MARGE_LUM) {
                        act = ALLUMER_LAMPE;
                } else if (lum>modele.luminosite+MARGE_LUM) {
                        act = ETEINDRE;
                }
        }
    }
    return act;
}
