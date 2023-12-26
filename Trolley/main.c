#include "services.h"
#include "Dio.h"

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
  
    
  //SERVICES_systemInit();
  
  /* testing */
  ConfigurationPin pin = {PORTA_ID, PIN5_ID, OUTPUT_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_LOW, NO_ALTERNATE};
  PORT_configurePin(&pin);
  ConfigurationPin pin2 = {PORTA_ID, PIN6_ID, INPUT_MODE, OUTPUT_PUSH_PULL, PULL_DOWN, LOGIC_LOW, NO_ALTERNATE};
  PORT_configurePin(&pin2);
  /* testing */
  
  while(1){  
    /*
    SERVICES_updateTrolleyData();
    SERVICES_updateUserData();
    distanceBetweenUserAndTrolley = SERVICES_getDistance();
    angleBetweenUserAndTrolley = SERVICES_getDifferenceInAngle();
    if(angleBetweenUserAndTrolley == -1){
      SERVICES_sendCommandToAvrSlave(MOVE_FORWARD, 100);
    } 
    */
    
    /* testing 
    Dio_writePin(&pin, LOGIC_HIGH);
    for(uint32 i = 0; i < 1000000; i++);
    Dio_writePin(&pin, LOGIC_LOW);
    for(uint32 i = 0; i < 1000000; i++);
    /* testing */
    
    if(Dio_readPin(&pin2))
    {
        Dio_writePin(&pin, LOGIC_HIGH);
    }
    
  }
  
  return 0;
  
}
