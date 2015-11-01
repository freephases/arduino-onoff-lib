/*

Turn things on and off now or at set interval or set on and off intervals (PWM)

Pete darling 

Oct 2012

*/

#include "Arduino.h"
#include "OnOff.h"

OnOff::OnOff(int pin)
{
  _pin = pin;
  _isOn = false;
  _previousMillis = 0;
  lastVoltage = 0;
	
  pinMode(_pin, OUTPUT); 
  digitalWrite(_pin, LOW);
}

/*void OnOff::doSetup(){
  
}*/

void OnOff::on() {
  
   if (!getIsOn()) {
     digitalWrite(_pin, HIGH);
     _isOn = true;
   }
 
}

void OnOff::off() {
  if (getIsOn()) {
    _isOn = false;
    digitalWrite(_pin, LOW);
  }
}

/**
* Call analogWrite for PWM 
* @param int voltage 0-255 (0=0v, 255=5or3.3v)
*/
void OnOff::onByVoltage(int voltage) 
{
  _isOn = (voltage>0);
   analogWrite(_pin, voltage);
}

void OnOff::onByVolts(int voltage)
{
   int voltageMapped = map(voltage, 0, 5, 0, 1023);
  _isOn = (voltageMapped>0);
   analogWrite(_pin, voltageMapped);
}

void OnOff::onByVolts(float voltage)
{
   int voltageMapped = int((5.0/1023)*voltage);
  _isOn = (voltageMapped>0);
   analogWrite(_pin, voltageMapped);
}

void OnOff::onByVoltagePercent(int percent)
{
   int voltageMapped = map(percent, 0, 100, 0, 1023);
  _isOn = (voltageMapped>0);
   analogWrite(_pin, voltageMapped);
}

boolean OnOff::getIsOn()
{
 return _isOn;
}

/**
* If off turn on otherwise turn off
*/
void OnOff::toggle() 
{
  if(_isOn) off();
  else on();
}

//calls toggle if interval is up otherwise continues
// flash 

void OnOff::toggleAtInterval(int intervalMillis)
{
   unsigned long currentMillis = millis();

   if(currentMillis - _previousMillis > intervalMillis) {
       toggle();
   	_previousMillis = currentMillis; 	
   }
}

//calls toggle if first interval is up otherwise continues or
//  calls toggle if second interval is up otherwise continues
// varied flash

void OnOff::toggleAtIntervals(int onIntervalMillis, int offIntervalMillis)
{
   unsigned long currentMillis = millis();

   int interval = 0;
   if (_isOn) {
     interval = onIntervalMillis;
   }
   else {
     interval = offIntervalMillis;
   }

   if(currentMillis - _previousMillis > interval) {
       toggle();
   	_previousMillis = currentMillis; 	
   }
}

int OnOff::getLastVoltage()
{
	return lastVoltage;
}
