#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  DigitalActuatorLED led1(DELAY);
  I2CActuatorScreen screen;
  AnalogSensorLuminosity lumino(DELAY);
  IntelligentDigitalActuatorLED led2(DELAY);
  ExternalDigitalSensorbutton bouton(DELAY);
  AnalogSensorRadar radar(DELAY);
  AnalogActuatorServo servo(DELAY);

  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  esp8266.pin(2,lumino);
  esp8266.pin(3,led2);
  esp8266.pin(4,bouton);
  esp8266.pin(5,radar);
  esp8266.pin(8,servo);
  // allumage de la carte
  esp8266.run();
  return 0;
}


