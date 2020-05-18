
#include "mydevices.h"

using namespace std;
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}

//class AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int t):Device(),val(luminosite_environnement),temps(t){
    alea=1;
}

void AnalogSensorLuminosity::run(){
  while(1){
    val=luminosite_environnement;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void IntelligentDigitalActuatorLED::run(){
    bool estPasse_low = false;
    bool estPasse_high=false;
while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW){
        estPasse_high=false;
        if (estPasse_low==false){
                luminosite_environnement -=50;
                estPasse_low=true;
        }
        cout << "((((eteint_LED2))))\n";

    }
    else{
        estPasse_low=false;
        if(estPasse_high==false){
           luminosite_environnement += 50;
           estPasse_high=true;
        }
        cout << "((((allume_LED2))))\n";
    }
    sleep(temps);
    }
}
//Classe ExternalDigitalSensorbutton

ExternalDigitalSensorbutton::ExternalDigitalSensorbutton(int t):state(OFF),temps(t){
}

void ExternalDigitalSensorbutton::run(){
    while(1){
        if(ifstream("on.txt")){
            state=ON;
        }
        else{
            state=OFF;
        }
        if(ptrmem!=NULL)
        *ptrmem=state;
        sleep(temps);
    }
}

//class AnalogSensorHumidity
AnalogSensorHumidity::AnalogSensorHumidity(int t):Device(),temps(t){
    alea=1;
}

//class AnalogSensorHumiditySoil
AnalogSensorHumiditySoil::AnalogSensorHumiditySoil(int t):AnalogSensorHumidity(t),val(luminosite_environnement){
    alea=1;
}
void AnalogSensorHumiditySoil::run(){
  while(1){
    val=humidite_sol;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//class AnalogSensorHumidityAir

AnalogSensorHumidityAir::AnalogSensorHumidityAir(int t):AnalogSensorHumidity(t),val(luminosite_environnement){
    alea=1;
}
void AnalogSensorHumidityAir::run(){
  while(1){
    val=humidite_air;

    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

// classe I2CActuatorLCD
LCDScreen::LCDScreen (int num):Device(),numeroPlante(num){
  }

void LCDScreen::run(){

  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);

        switch (etatSante)
        {
        case EXCELLENT :
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en parfaite sante\n\n";
            cout<<"******************"<<endl;
            break;
        case BON :
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en bonne sante\n\n";
            cout<<"******************"<<endl;
            break;
        case DESSECHEE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en dessechee\n\n";
            cout<<"******************"<<endl;
            break;
        case NOYEE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est en train de se noyer\n\n";
            break;
        case MORTE:
            cout<<"*******LCD************"<<endl;
            cout << "La plante numero"<<numeroPlante<<" est malheureusement morte\n\n";
            cout<<"******************"<<endl;
            break;
        default:
                break;
        }
    }
    sleep(1);
    }
}
