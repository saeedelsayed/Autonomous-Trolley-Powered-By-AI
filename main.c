#include "services.h"

uint8 data[100] = "Abdelrahman\r\n";

Qmc5883l_DataType compassData;

int main()
{
  /* enable clock for STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /*enable clock for PORT B */
  *((uint32*)0x40023830) |= (1 << 1);
  
  /*enable clock for PORT A */
  *((uint32*)0x40023830) |= (1 << 0);
  
  SERVICES_systemInit();
  
  GPS_updateLatitudeAndLongitude();
  
  Bluetooth_sendString(data);
  
  Bluetooth_receiveString(data);
  
  QMC5883l_GetAngel(&compassData);
  
  
  while(1){   

  }
  
  return 0;
  
}
