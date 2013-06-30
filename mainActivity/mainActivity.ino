#include "Lighting.h"
#include "Sensors.h"
//main code for intelli-fish

//not sure how to expose these from the cpp library
//so il default them to here for now

static int FULLPOWER = 1023;
static int HALFPOWER = 3098;
static int QUARTPOWER = 9345;
static int NIGHTPOWER = 7395;

unsigned long HALFPOWER_TIMER = 60000;
unsigned long QUARTPOWER_TIMER = 120000;
unsigned long CURRENT_TIME;


int LIGHT_VALUE = 300;//this should be between 1000 and 0, closer to 0 eqauls less light.


//these leds are status for each strip of lights
int SBLUE_PIN = 11;
int SWHITE1_PIN = 12;
int SWHITE2_PIN = 13;
boolean DAYTIME = true;

Lighting light = Lighting(SWHITE1_PIN,SWHITE2_PIN,SBLUE_PIN);//lighting class
Sensors sensor;


void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Communication Started.....");
  //intailise lighting class
  light.init();

  //intailise sensors
  sensor.SetPins(A0,A2);//PIR,LDR

  sensor.init();

  CURRENT_TIME = millis();//set the timer so we have something to use
  Serial.println("Set up complete running routine...");
}
void loop()
{
  //ok first thing check what day time
  checkLight();


  if(DAYTIME)
  {
    //Serial.println("DAY TIME");

    //its daytime so we need to manage half power etc

    if(timerOne(false))
    {
      Serial.println("Half Power timer triggered");
      //we can assume that timer one has ALWAYS triggered if timer two has triggered
      if(timerTwo(false))//check the quater power trigger
      {
        Serial.println("Quarter Power timer triggered");
        light.LightingOnMode(QUARTPOWER);
      }
      else
      {
        //go down to half power
        light.LightingOnMode(HALFPOWER);
      }
    }
    else
    {
      Serial.println("going to full power");
      light.LightingOnMode(FULLPOWER);
    }
  }
  else
  {
    //its night time s do to night time the lighting class will manage the duplicate requests
    Serial.println("NIGHT TIME");
    light.LightingOnMode(NIGHTPOWER);
  }

  if(sensor.getStatus(sensor.PIR))
  {
    //the PIR has seen something so reset the timers
    Serial.println(">>>>>>>>>>>>>>>> PIR SENSOR TRIGGERED <<<<<<<<<<<<<<<");
    timerOne(true); 
    timerTwo(true);//reset the timers
  }


  delay(1000);
}

//checks the light level in the room and set DAYTIME flags
void checkLight()
{
  if(sensor.getStatus(sensor.LDR))//if its day
  { 
    if(! DAYTIME)
    { 
      delay(3000);
      if(sensor.getStatus(sensor.LDR))
      {
        DAYTIME = true;
      }
    }
  }
  else //its night
  {
    if(DAYTIME)
    {
      delay(3000);
      if(! sensor.getStatus(sensor.LDR))//returns night again!
      {
        DAYTIME = false;
      }
    }

  }

}


//if a true is passed then timer is reset is a false is passed then we are just updating
boolean timerOne(boolean reset)
{
  //if a true is passed then timer is reset is a false is passed then we are just updating


  if(reset)
  {
    //reset the timer
    CURRENT_TIME = millis();

  }
  else
  {
    //Serial.print((millis() - CURRENT_TIME) / 1000);
    //Serial.println(" Seconds passed");
    //if time up then return true else return false
    if((millis() - CURRENT_TIME) > HALFPOWER_TIMER)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  //If a true is returned then the timer is up
}

//if a true is passed then timer is reset is a false is passed then we are just updating
boolean timerTwo(boolean reset)
{
  //if a true is passed then timer is reset is a false is passed then we are just updating

  if(reset)
  {
    //reset the timer
    CURRENT_TIME = millis();
  }
  else
  {
    //if time up then return true else return false
    if((millis() - CURRENT_TIME) > QUARTPOWER_TIMER)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  //If a true is returned then the timer is up
}










