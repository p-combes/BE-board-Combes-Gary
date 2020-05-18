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

  AnalogSensorHumidityAir humAir(DELAY);
  AnalogSensorHumiditySoil humSol(DELAY);
  LCDScreen lcd(I2C_LCD);

  // branchement des capteurs actionneurs
  esp8266.pin(PIN_TEMP,temperature);
  esp8266.pin(PIN_LED1,led1);
  esp8266.pin(PIN_LUMINOSITE,lumino);
  esp8266.pin(PIN_LED2,led2);
  esp8266.pin(PIN_BOUTON,bouton);
  esp8266.pin(PIN_HUM_AIR,humAir);
  esp8266.pin(PIN_HUM_SOIL,humSol);

  esp8266.i2c(I2C_SCREEN,screen);
  esp8266.i2c(I2C_LCD,lcd);
  esp8266.pin(PIN_RADAR,radar);
  esp8266.pin(PIN_SERVO_ARROSOIR,servo);
  // allumage de la carte
  esp8266.run();
  return 0;
}


