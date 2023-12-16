/******************************************************************************
*
* Module: GPS module
*
* File Name: gps_commands.h
*
* Description: header file for the GPS module commands
*
* Author: Abdelrahman Saeed
*
*******************************************************************************/


#ifndef GPS_COMMANDS_H_
#define GPS_COMMANDS_H_

#include "std_types.h"

/* disable VTG message command */
uint8* DISABLE_VTG_MESSAGE = "$PUBX,40,VTG,0,0,0,0,0,0*5E\r\n";

/* disable RMC message command */
uint8* DISABLE_RMC_MESSAGE = "$PUBX,40,RMC,0,0,0,0,0,0*47\r\n";

/* disable GGA message command */
uint8* DISABLE_GGA_MESSAGE = "$PUBX,40,GGA,0,0,0,0,0,0*5A\r\n";

/* disable GSA message command */
uint8* DISABLE_GSA_MESSAGE = "$PUBX,40,GSA,0,0,0,0,0,0*4E\r\n";

/* disable GSV message command */
uint8* DISABLE_GSV_MESSAGE = "$PUBX,40,GSV,0,0,0,0,0,0*59\r\n";

/* disable GLL message command */
uint8* DISABLE_GLL_MESSAGE = "$PUBX,40,GLL,0,0,0,0,0,0*5C\r\n";

/* enable GLL message command */
uint8* ENABLE_GLL_MESSAGE = "$PUBX,40,GLL,1,1,1,1,1,1*5C\r\n";

#endif  /* GPS_COMMANDS_H_ */