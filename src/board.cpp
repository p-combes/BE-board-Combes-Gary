#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY);
  I2CActuatorScreen screen_1;
  I2CActuatorScreen screen_2;
  I2CActuatorScreen screen_3;
  ExternalDigitalSensorbutton bouton(DELAY);
  AnalogSensorRadar radar(DELAY);
  AnalogActuatorServoRail servoRail(DELAY);
  AnalogActuatorServoInclinaison servoIncl(DELAY);
  AnalogSensorHumidityAir humAir(DELAY);
  //Capteurs d'humidité
  AnalogSensorHumiditySoil humSol_1(DELAY,1);
  AnalogSensorHumiditySoil humSol_2(DELAY,2);
  AnalogSensorHumiditySoil humSol_3(DELAY,3);
  //Capteurs de luminosité
  AnalogSensorLuminosity lumino1(DELAY,1);
  AnalogSensorLuminosity lumino2(DELAY,2);
  AnalogSensorLuminosity lumino3(DELAY,3);
  //Lampes à UV
  DigitalActuatorUVLamp UV1 (DELAY,1);
  DigitalActuatorUVLamp UV2(DELAY,2);
  DigitalActuatorUVLamp UV3 (DELAY,3);

  AnalogSensorAngular angleMeasure(DELAY);


  // branchement des capteurs actionneurs
  esp8266.pin(PIN_TEMP,temperature);
  esp8266.pin(PIN_UV1,UV1);
  esp8266.pin(PIN_UV2,UV2);
  esp8266.pin(PIN_UV3,UV3);
  esp8266.pin(PIN_LUMINOSITE_1,lumino1);
  esp8266.pin(PIN_LUMINOSITE_2,lumino2);
  esp8266.pin(PIN_LUMINOSITE_3,lumino3);
  esp8266.pin(PIN_BOUTON,bouton);
  esp8266.pin(PIN_HUM_AIR,humAir);
  esp8266.pin(PIN_HUM_SOIL_1,humSol_1);
  esp8266.pin(PIN_HUM_SOIL_2,humSol_2);
  esp8266.pin(PIN_HUM_SOIL_3,humSol_3);
  esp8266.pin(PIN_SERVO_INCLINAISON, servoIncl);
  esp8266.i2c(I2C_SCREEN_1,screen_1);
  esp8266.i2c(I2C_SCREEN_2,screen_2);
  esp8266.i2c(I2C_SCREEN_3,screen_3);
  esp8266.pin(PIN_RADAR,radar);
  esp8266.pin(PIN_SERVO_ARROSOIR,servoRail);
  esp8266.pin(PIN_ANGULAR,angleMeasure);
  // allumage de la carte
  esp8266.run();
  return 0;
}


