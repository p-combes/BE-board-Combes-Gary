#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY);
  DigitalActuatorLED led1(DELAY);
  I2CActuatorScreen screen_1;
  I2CActuatorScreen screen_2;
  I2CActuatorScreen screen_3;
  AnalogSensorLuminosity lumino(DELAY);
  IntelligentDigitalActuatorLED led2(DELAY);
  ExternalDigitalSensorbutton bouton(DELAY);
  AnalogSensorRadar radar(DELAY);
  AnalogActuatorServoRail servoRail(DELAY);
  AnalogActuatorServoInclinaison servoIncl(DELAY);
  AnalogSensorHumidityAir humAir(DELAY);
  AnalogSensorHumiditySoil humSol_1(DELAY,1);
  AnalogSensorHumiditySoil humSol_2(DELAY,2);
  AnalogSensorHumiditySoil humSol_3(DELAY,3);


  // branchement des capteurs actionneurs
  esp8266.pin(PIN_TEMP,temperature);
  esp8266.pin(PIN_LED1,led1);
  esp8266.pin(PIN_LUMINOSITE,lumino);
  esp8266.pin(PIN_LED2,led2);
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


  // allumage de la carte
  esp8266.run();
  return 0;
}


