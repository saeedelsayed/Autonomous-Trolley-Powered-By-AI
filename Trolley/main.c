#include "services.h"

float32 distanceBetweenUserAndTrolley = 0.0;
uint8 direction = 0;
uint16 angleOrSpeed = 0;

int main()
{
  /* enable clock for STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /*enable clock for PORT B */
  *((uint32*)0x40023830) |= (1 << 1);
  
  /*enable clock for PORT A */
  *((uint32*)0x40023830) |= (1 << 0);
  
    
  SERVICES_systemInit();
  
  uint8 returnValue;
  
    
  while(1){
    SERVICES_updateTrolleyData();
    SERVICES_updateUserData();
    distanceBetweenUserAndTrolley = SERVICES_getDistance();
    SERVICES_decideDirection(&angleOrSpeed, &direction);
    returnValue = SERVICES_sendCommandToAvrSlave(direction, angleOrSpeed);
    
    if(returnValue == FAIL){
      continue;
    }
    
  }
  
  return 0;
  
}
