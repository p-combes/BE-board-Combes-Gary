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

#define EXCEPTION_NB_PLANTE

int measureSoilHumidity (int numeroPlante, Board* arduino);
int measureAirHumidity(Board* arduino);
//int measureLuminosity();
//int measure Temperature();
