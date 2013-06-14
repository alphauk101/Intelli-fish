/*Lighting class which will control lighting levels 
* changes in level of lighting and possibly feedback
*errors.*/
#include "Lighting.h"
#include <arduino.h>

static int WHITE1_PIN, WHITE2_PIN, BLUE_PIN;

static int CURRENT_STATE;

int FULL_POWER = 1023;
int HALF_POWER = 3098;
int QUART_POWER = 9345;
int NIGHT_POWER = 7395;

//constructor set the pins of the leds here
Lighting::Lighting(int WHITE1, int WHITE2, int BLUE)
{
  WHITE1_PIN = WHITE1;
  WHITE2_PIN = WHITE2;
  BLUE_PIN = BLUE;
}

//with this method we send a number according to mode we want 
//1 = full power
//2 = half power lights go down to half leds
//3 = quarter power remaining leds go down to half
//4 = night mode only blue leds

void Lighting::LightingOnMode(int mode)
{

  switch(mode)
  {
    case(1023)://FULL POWER
    //detect the mode and shift accordingly
      if(CURRENT_STATE != mode)//check that the requested mode change is not the same as the current state
      {
        //first we need to turn the current mode off and full on
        //if we are in  half or then is just a case of switching the all the lights back on
        if(CURRENT_STATE == HALF_POWER)
        {
          //switch WHITE2 back on
        }else if(CURRENT_STATE == QUART_POWER)
        {
          //we need to bring WHITE1 back on and WHITE2 back upto full power
        }else if(CURRENT_STATE == NIGHT_POWER)
        {
         //we need to switch the MOON leds off and the WHITE1 & 2 ON 
        }
        //finally set the CURRENT_STATE so we can use it properly
        CURRENT_STATE = mode;
        
      }//if it is the same ignore the change request
      
    break;
    case(3098)://HALF POWER
      if(CURRENT_STATE != mode)//check that the requested mode change is not the same as the current state
        {
          //first we need to turn the current mode off and full on

          if(CURRENT_STATE == FULL_POWER)
          {
            //switch WHITE2 off to go to half power
          }else if(CURRENT_STATE == QUART_POWER)
          {
            //this will probably never occur due to the behaviour of the hardware 
            //but we should process accordingly for future developments.
            
            //switch WHITE2 back up to full and STOP this equals HALF POWER
          }else if(CURRENT_STATE == NIGHT_POWER)
          {
           //we need to switch the MOON leds off and JUST WHITE2 on (half power)
          }
          //finally set the CURRENT_STATE so we can use it properly
          CURRENT_STATE = mode;
          
        }//if it is the same ignore the change request
    break;
    case(9345)://QUARTER POWER
      if(CURRENT_STATE != mode)//check that the requested mode change is not the same as the current state
          {
            //first we need to turn the current mode off and full on
  
            if(CURRENT_STATE == FULL_POWER)
            {
              
              //switch WHITE2 off and lower power to 50% on WHITE1
            }else if(CURRENT_STATE == QUART_POWER)
            {
              //this will probably never occur due to the behaviour of the hardware 
              //but we should process accordingly for future developments.
              
              //switch WHITE2 back up to full and STOP this equals HALF POWER
            }else if(CURRENT_STATE == NIGHT_POWER)
            {
             //we need to switch the MOON leds off and JUST WHITE2 on (half power)
            }
            //finally set the CURRENT_STATE so we can use it properly
            CURRENT_STATE = mode;
            
          }//if it is the same ignore the change request
    break;
    case(7395)://MOON POWER
    
    break;
    default:
    //do nothing because we have been passed a invlaid mode
    break;
  }
}




