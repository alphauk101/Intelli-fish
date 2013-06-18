/*Sensor to control behaves of the attached sensors*/
#include "Sensors.h"
#include <arduino.h>

#define NIGHT_LEVEL = 100

static int _pir = 20;
static int _ldt = 21;

static int PIR_PIN, LDR_PIN;
/*sets the pins ready for init*/
void Sensors::SetPins(int mPIR, int mLDR)
{
  PIR_PIN = mPIR;
  LDR_PIN = mLDR;
}

void Sensors::init(void)
{
  //set the pins to input mode
  pinMode(PIR_PIN,INPUT);
  pinMode(LDR_PIN,INPUT);
}

bool Sensors::getStatus(int sensor)
{
  if(sensor == _pir)
  {
    //check the pir status
    //here we need to check that the light levels are above 
    //what we would consider night if not switch to night mode
    if(analogRead(PIR_PIN) <= NIGHT_LEVEL)
    {
      
    }
  }else if(sensor == _ldr)
  {
    //check the ldr status
  }
}
