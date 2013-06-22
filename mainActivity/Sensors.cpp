/*Sensor to control behaves of the attached sensors*/
#include "Sensors.h"
#include <arduino.h>

static int NIGHT_LEVEL = 800;

//int PIR = 20;
//int LDR = 21;
int PIR;
int LDR;

static int PIR_PIN, LDR_PIN;
/*sets the pins ready for init*/
void Sensors::SetPins(int mPIR, int mLDR)
{
  PIR_PIN = mPIR;
  LDR_PIN = mLDR;
  Serial.print("PIR pin: ");
  Serial.println(PIR_PIN);
  Serial.print("LDR pin: ");
  Serial.println(LDR_PIN);
}

void Sensors::init(void)
{
  //set the pins to input mode
  pinMode(PIR_PIN,INPUT);
  pinMode(LDR_PIN,INPUT);
  
  LDR = 2014;
  PIR = 1321;
}

bool Sensors::getStatus(int sensor)
{

  if(sensor == LDR)
  {
    //Serial.print("LDR Reads...");
    //Serial.println(analogRead(LDR_PIN));
    //check the pir status
    //here we need to check that the light levels are above 
    //what we would consider night if not switch to night mode
    if(analogRead(LDR_PIN) >= NIGHT_LEVEL)
    {
      return true;
    }
    else
    {
      return false;
    }
  }else if(sensor == PIR)
  {
    //check the ldr status
    if(analogRead(PIR_PIN) > 500)
    {
      return true;
    }else
    {
      return false;
    }
  }
}

