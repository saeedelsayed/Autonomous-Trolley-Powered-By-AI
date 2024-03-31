#ifndef INC_I2C_CFG_H_
#define INC_I2C_CFG_H_


/*
SCL Frequency = CPU Clock frequency / (16 + 2*TWBR*4^TWPS)
For Example:
    CPU Clock frequency = 8 MHz
    TWBR = 2
    TWPS = 0
    SCL = 400 Kbps
--> TWBR Range: 0..255
--> TWPS Range: 0..3
*/
#define I2C_TWBR_VALUE 1
#define I2C_TWPS_VALUE 0
#endif /* INC_I2C_CFG_H_ */
