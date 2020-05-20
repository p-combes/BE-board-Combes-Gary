#include "application_plante.h"

using namespace std;

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
