#include "Lighting.h"
#include "Sensors.h"
//main code for intelli-fish

//C:\arduino-1.0.3\hardware\tools\avr\bin>avrdude.exe -C C:\arduino-1.0.3\hardware
//\tools\avr\etc\avrdude.conf -c avrispmkII -P usb -p ATmega328P  -U flash:w:\User
//s\Lee\Desktop\mainActivity.hex -F
//not sure how to expose these from the cpp library
//so il default them to here for now

static int FULLPOWER = 1023;
static int HALFPOWER = 3098;
static int QUARTPOWER = 9345;
static int NIGHTPOWER = 7395;

unsigned long HALFPOWER_TIMER = 60000; // 10 mins
unsigned long QUARTPOWER_TIMER = 120000; //15 mins
unsigned long CURRENT_TIME;

int red_led = 4;
int yellow_led = 3;
int green_led = 2;

int LIGHT_VALUE = 600;//this should be between 1000 and 0, closer to 0 eqauls less light.


//these leds are status for each strip of lights
int SBLUE_PIN = 9;
int SWHITE1_PIN = 11;
int SWHITE2_PIN = 10;
boolean DAYTIME = true;

Lighting light = Lighting(SWHITE1_PIN,SWHITE2_PIN,SBLUE_PIN);//lighting class
Sensors sensor;


void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Communication Started.....");
  //intailise lighting class
  light.init();
  pinMode(green_led, OUTPUT);//power led
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  digitalWrite(green_led,HIGH);
  //initialise sensors
  sensor.SetPins(A1,A0);//PIR,LDR

  sensor.init();

  CURRENT_TIME = millis();//set the timer so we have something to use
  Serial.println("Set up complete running routine...");
  showInitDone();
  digitalWrite(green_led,HIGH);
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
    Serial.println(">>>>>>>>>>>>>> PIR SENSOR TRIGGERED <<<<<<<<<<<<<<<");
    digitalWrite(red_led,HIGH);
    timerOne(true); 
    timerTwo(true);//reset the timers
    delay(250);
    digitalWrite(red_led,LOW);
  }

  if(!DAYTIME)
  {
    if(random(1,67000) == 33500)
    {
      light.Storm();
    }
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
  if(DAYTIME)
  {
    digitalWrite(yellow_led, LOW);
  }
  else
  {
    digitalWrite(yellow_led, HIGH);
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

void showInitDone()
{
  for(int a = 0 ;a < 5; a++)
  {
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);

    digitalWrite(red_led,HIGH);
    delay(250);
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, HIGH);
    delay(250);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, HIGH);
    delay(250);
  }
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(yellow_led, LOW);
}











