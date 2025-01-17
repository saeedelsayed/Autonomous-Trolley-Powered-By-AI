/*******************************************************************************
 *
 * Module: I2C module
 *
 * File Name: i2c_registers.h
 *
 * Description: registers defintion for the I2C module
 *
 * Author: Saeed Elsayed & Ahmed Radwan
 *
 *******************************************************************************/

#ifndef I2C_REGISTERS_H_
#define I2C_REGISTERS_H_

/*******************************************************************************************/
/***********************************I2C Registers*******************************************/
/*******************************************************************************************/

/* Definition of the start address of the I2C */
#define I2C1 0x40005400
#define I2C2 0x40005800
#define I2C3 0x40005C00

/* definition of the offset of the registers from start address */
#define I2Cx_CR1_OFFSET     (0x00)
#define I2Cx_CR2_OFFSET     (0x04)
#define I2Cx_DR_OFFSET      (0x10)
#define I2Cx_SR1_OFFSET     (0x14)
#define I2Cx_SR2_OFFSET     (0x18)
#define I2Cx_CCR_OFFSET     (0x1C)
#define I2Cx_TRISE_OFFSET   (0x20)

/*******************************************************************************************/
/***********************************I2C Registers bits**************************************/
/*******************************************************************************************/

/* definition of the bits of the control register 1 */
typedef enum
{
    I2C_CR1_PE = 0,
    I2C_CR1_SMBUS,
    I2C_CR1_SMBTYPE = 3,
    I2C_CR1_ENARP,
    I2C_CR1_ENPEC,
    I2C_CR1_ENGC,
    I2C_CR1_NOSTRETCH,
    I2C_CR1_START,
    I2C_CR1_STOP,
    I2C_CR1_ACK,
    I2C_CR1_POS,
    I2C_CR1_PEC,
    I2C_CR1_ALERT,
    I2C_CR1_SWRST = 15
} I2C_CR1_BITS;

/* definition of the bits of the control register 2 */
typedef enum
{
    I2C_CR2_FREQ = 0,
    I2C_CR2_ITERREN = 8,
    I2C_CR2_ITEVTEN,
    I2C_CR2_ITBUFEN,
    I2C_CR2_DMAEN,
    I2C_CR2_LAST
} I2C_CR2_BITS;

/* definition of the bits of the status register 1 */
typedef enum
{
    I2C_SR1_SB = 0,
    I2C_SR1_ADDR,
    I2C_SR1_BTF,
    I2C_SR1_ADD10,
    I2C_SR1_STOPF,
    I2C_SR1_RXNE = 6,
    I2C_SR1_TXE,
    I2C_SR1_BERR,
    I2C_SR1_ARLO,
    I2C_SR1_AF,
    I2C_SR1_OVR,
    I2C_SR1_PECERR,
    I2C_SR1_TIMEOUT = 14,
    I2C_SR1_SMBALERT
} I2C_SR1_BITS;

/* definition of the bits of the status register 2 */
typedef enum
{
    I2C_SR2_MSL = 0,
    I2C_SR2_BUSY,
    I2C_SR2_TRA,
    I2C_SR2_GENCALL = 4,
    I2C_SR2_SMBDEFAULT,
    I2C_SR2_SMBHOST,
    I2C_SR2_DUALF,
    I2C_SR2_PEC
} I2C_SR2_BITS;

/* definition of the bits of the clock control register */
typedef enum
{
    I2C_CCR_CCR = 0,
    I2C_CCR_DUTY = 14,
    I2C_CCR_FS
} I2C_CCR_BITS;

/* definition of the bits of the rise time register */
typedef enum
{
    I2C_TRISE_TRISE = 0
} I2C_TRISE_BITS;


#endif /* I2C_REGISTERS_H_ */