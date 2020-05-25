#include "lampeUV.h"

void AllumerLampe(int numeroPlante, Board * arduino){
int pinToWrite;
switch(numeroPlante){
case 1:
    pinToWrite=PIN_UV1;
    break;
case 2:
    pinToWrite=PIN_UV2;
    break;
case 3:
    pinToWrite=PIN_UV3;
    break;
default:
    throw EXCEPTION_NB_PLANTE;
    }
    arduino->digitalWrite(pinToWrite,ON);
}

void EteindreLampe(int numeroPlante, Board * arduino){
int pinToWrite;
switch(numeroPlante){
case 1:
    pinToWrite=PIN_UV1;
    break;
case 2:
    pinToWrite=PIN_UV2;
    break;
case 3:
    pinToWrite=PIN_UV3;
    break;
default:
    throw EXCEPTION_NB_PLANTE;
    }
    arduino->digitalWrite(pinToWrite,OFF);
}

