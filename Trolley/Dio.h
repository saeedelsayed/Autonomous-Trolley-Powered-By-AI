#ifndef DIO_H_
#define DIO_H_

#include "port.h"
#include "port_registers.h"
#include "std_types.h"

void Dio_writePin(ConfigurationPin* configurationPin, uint8 data);
uint8 Dio_readPin(ConfigurationPin* configurationPin);

#endif /* DIO_H_ */