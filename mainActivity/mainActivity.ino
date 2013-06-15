#include "Lighting.h"
//main code for intelli-fish

//not sure how to expose these from the cpp library
//so il default them to here for now
int FULLPOWER = 1023;
int HALFPOWER = 3098;
int QUARTPOWER = 9345;
int NIGHTPOWER = 7395;

int LDR_PIN = A7;
int LIGHT_VALUE = 300;//this should be between 1000 and 0, closer to 0 eqauls less light.
int PIR_PIN = 2;

//these leds are status for each strip of lights
int SBLUE_PIN = 11;
int SWHITE1_PIN = 12;
int SWHITE2_PIN = 13;
boolean DAYTIME = true;

Lighting light = Lighting(SWHITE1_PIN,SWHITE2_PIN,SBLUE_PIN);

void setup()
{
  pinMode(LDR_PIN,INPUT);
  pinMode(PIR_PIN,INPUT);

  Serial.begin(9600);

  //intailise lighting class
  light.init();
}
void loop()
{
  delay(5000);//delay so not to blur the switching

  switch(random(0,3))
  {
    case(0):
    light.LightingOnMode(FULLPOWER);
    break;
    case(1):
    light.LightingOnMode(HALFPOWER);
    break;
    case(2):
    light.LightingOnMode(QUARTPOWER);
    break;
    case(3):
    light.LightingOnMode(NIGHTPOWER);
    break;    
  } 

}


//Check the time of day
boolean checkDayLight()
{
  Serial.println(analogRead(LDR_PIN));
  if(analogRead(LDR_PIN) > LIGHT_VALUE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean checkPIR()
{
  if(digitalRead(PIR_PIN) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}



