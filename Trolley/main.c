#include "services.h"

float32 distanceBetweenUserAndTrolley = 0.0;
sint8 angleBetweenUserAndTrolley = 0;

int main()
{
  /* enable clock for STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /*enable clock for PORT B */
  *((uint32*)0x40023830) |= (1 << 1);
  
  /*enable clock for PORT A */
  *((uint32*)0x40023830) |= (1 << 0);
  
    
  SERVICES_systemInit();
  
  
   /*this is any code to test the effect of the .gitignore file */
  *((uint32*)0x40023830) |= (1 << 5);
  
  while(1){  
    SERVICES_updateTrolleyData();
    SERVICES_updateUserData();
    distanceBetweenUserAndTrolley = SERVICES_getDistance();
    angleBetweenUserAndTrolley = SERVICES_getDifferenceInAngle();
    if(angleBetweenUserAndTrolley == -1){
      SERVICES_sendCommandToAvrSlave(MOVE_FORWARD, 100);
    } 
  }
  
  return 0;
  
}
