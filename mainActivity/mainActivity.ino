#include "Lighting.h"
#include "Sensors.h"
//main code for intelli-fish

//not sure how to expose these from the cpp library
//so il default them to here for now

static int FULLPOWER = 1023;
static int HALFPOWER = 3098;
static int QUARTPOWER = 9345;
static int NIGHTPOWER = 7395;

unsigned long HALFPOWER_TIMER = 10 * 1000;
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
  sensor.SetPins(A1,A2);//PIR,LDR

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
    Serial.println("DAY TIME");
    
    //its daytime so we need to manage half power etc

    if(timerOne(false))
    {
      //go down to half power
      Serial.println("going to half");
      light.LightingOnMode(HALFPOWER);
    }else
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
  }



  delay(1000);
}

//checks the light level in the room and set DAYTIME flags
void checkLight()
{
  if(sensor.getStatus(sensor.LDR))//if its night
  {  
    //it is worth waiting X secs to "double check that it is definitly night time and not just a false reading"
    if(DAYTIME)
    {
      delay(5000);
      if(sensor.getStatus(sensor.LDR))
      {
        DAYTIME = false;
      }
    }
  }
  else
  {
    delay(2000);
    if(! sensor.getStatus(sensor.LDR))
    {
      DAYTIME = true;
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






