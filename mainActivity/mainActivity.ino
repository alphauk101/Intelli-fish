#include "Lighting.h"
#include "Sensors.h"
//main code for intelli-fish

//not sure how to expose these from the cpp library
//so il default them to here for now

static int FULL_POWER = 1023;
static int HALF_POWER = 3098;
static int QUART_POWER = 9345;
static int NIGHT_POWER = 7395;

unsigned long HALFPOWER_TIMER = 10 * 1000;
unsigned long CURRENT_TIME;

//static int PIR = 20;
//static int LDR = 21;

int LDR_PIN = A7;
int LIGHT_VALUE = 300;//this should be between 1000 and 0, closer to 0 eqauls less light.
int PIR_PIN = 2;

//these leds are status for each strip of lights
int SBLUE_PIN = 11;
int SWHITE1_PIN = 12;
int SWHITE2_PIN = 13;
boolean DAYTIME = true;

Lighting light = Lighting(SWHITE1_PIN,SWHITE2_PIN,SBLUE_PIN);//lighting class
Sensors sensor;


void setup()
{
  pinMode(LDR_PIN,INPUT);
  pinMode(PIR_PIN,INPUT);

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
    light.LightingOnMode(FULL_POWER);
  }
  else
  {
    //its night time s do to night time the lighting class will manage the duplicate requests
    Serial.println("NIGHT TIME");
    light.LightingOnMode(NIGHT_POWER);
  }

  if(sensor.getStatus(sensor.PIR))
  {
    //the PIR has seen something so reset the timers
    Serial.println("SEEN SEEN");
  }

  if(timerOne(false))
  {
    Serial.println("Timer up");
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
    }else
    {
      return false;
    }
  }
  
  //If a true is returned then the timer is up
}





