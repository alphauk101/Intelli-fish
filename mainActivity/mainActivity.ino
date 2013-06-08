//main code for intelli-fish
int LDR_PIN = A7;
int LIGHT_VALUE = 300;//this should be between 1000 and 0, closer to 0 eqauls less light.
int PIR_PIN = 2;

//these leds are status for each strip of lights
int SBLUE_PIN = 11;
int SWHITE1_PIN = 12;
int SWHITE2_PIN = 13;
boolean DAYTIME = true;


void setup()
{
  pinMode(LDR_PIN,INPUT);
  pinMode(PIR_PIN,INPUT);
  pinMode(SBLUE_PIN, OUTPUT);
  pinMode(SWHITE1_PIN, OUTPUT);
  pinMode(SWHITE2_PIN, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  
  //check PIR if someones there then put the lights on maximum
  if(checkPIR())
  {
    fadeLight(SWHITE2_PIN,true);
  }
  
  if(! checkDayLight())//if its night time
  {
    //check if it is ALREADY night time 
    if(DAYTIME == true)//we thought it was day
    {
      //so it was daytime now its night time so change light
      fadeLight(SWHITE1_PIN,false);//fade down main light
      fadeLight(SBLUE_PIN, true);//fade moonlight up
      
      DAYTIME = false;
    }
  }
  else
  {
    //its daytime
     //check if it is ALREADY night time 
    if(DAYTIME == false)//we thought it was day
    {
      //so it was daytime now its night time so change light
      fadeLight(SWHITE1_PIN,true);//fade down main light
      fadeLight(SBLUE_PIN, false);//fade moonlight up
      DAYTIME = true;
    }
  }
  
}

//we pass a pin number and a bool true for up vice versa
void fadeLight(int light, boolean fadeup)
{
  if(fadeup)
  {
    //fade light up
    for(int a = 0; a <= 255; a++)
    {
      analogWrite(light,a);
      delay(5);
    }
  
  }
  else
  {
    //fade down
    for(int a = 255; a >= 0; a--)
    {
      analogWrite(light,a);
      delay(5);
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

