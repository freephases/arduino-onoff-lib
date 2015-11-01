/*

Turn things on and off now or at set interval or set on and off intervals (PWM)

Pete darling 

Oct 2012

*/
#ifndef OnOff_h
#define OnOff_h

#include "Arduino.h"


class OnOff
{
  public:
    OnOff(int pin);
 //   void doSetup();
    void on();    
    void onByVoltage(int voltage); 
    void onByVoltagePercent(int percent); 
    void onByVolts(int voltage); 
    void onByVolts(float voltage); 
    void off();    
    boolean getIsOn();
    void toggle();
    void toggleAtInterval(int intervalMillis);
    void toggleAtIntervals(int onIntervalMillis, int offIntervalMillis);
    int getLastVoltage();
  private:
     boolean _isOn;
     int _pin;
     unsigned long _previousMillis;
     int lastVoltage;
};


#endif
