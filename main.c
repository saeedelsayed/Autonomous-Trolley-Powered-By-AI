#include "port.h"


int main()
{
  
  *((uint32*)0x40023800) |= (1 << 0);
  *((uint32*)0x40023830) |= (1 << 0);
  
  
  for(uint8 i = PIN0_ID; i <= PIN15_ID; i++){
      ConfigurationPin pin = {PORTA_ID, i, INPUT_MODE, OUTPUT_PUSH_PULL, PULL_UP, LOGIC_LOW, NO_ALTERNATE};
  
      PORT_configurePin(&pin);
  }
    
  while(1){
    
  }
  
  return 0;
}
