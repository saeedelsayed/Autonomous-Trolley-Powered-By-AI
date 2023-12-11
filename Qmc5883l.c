/**************************************************************************************************************************************/
/****************************************************    Author     : Abram Gad    ****************************************************/
/****************************************************    Date       : 12/12/2023   ****************************************************/
/****************************************************    version    : V01          ****************************************************/
/**************************************************************************************************************************************/

#include "i2c_driver.h"
#include "i2c_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "Qmc5883l.h"
#include <math.h>

void static QMC5883l_WriteReg(QMC5883l_RegType reg, uint8 data);
void static QMC5883l_ReadData(void);

#define QMC5883L_ADDRESS 0x0D

I2C_config_t I2C_Ref = {QMC5883l_I2cPort, I2C_MODE_I2C};
Qmc5883l_RawDataType * Data;
/**************************************************************************************************************************************
* @fn: QMC5883l_Init
* @brief: Initializes the QMC5883L magnetometer sensor.
*
* Description:
*   This function initializes the QMC5883L magnetometer sensor by configuring its settings through the I2C interface.
*   It first initializes the I2C module using the specified reference (I2C_Ref). Then, it writes specific values to the QMC5883L
*   registers to set the reset bit and configure the sensor with the desired settings.
*
* Parameters:
*   None
*
* Returns:
*   None
*
*************************************************************************************************************************************/
  void QMC5883l_Init(void)
  {
    
      I2C_init(&I2C_Ref);
      QMC5883l_WriteReg(QMC5833l_SET_RESET_REG, 0x01);    
      QMC5883l_WriteReg(QMC5883l_CONFIG_REG_1, 0x1D);
    
  }

/**************************************************************************************************************************************
 * @fn: QMC5883l_WriteReg
 * @brief: Writes a value to the specified register of the QMC5883L magnetometer sensor.
 *
 * Description:
 *   This function writes a value to the specified register of the QMC5883L magnetometer sensor through the I2C interface.
 *   It starts by generating a start condition on the I2C bus, writes the compass address with a write operation, clears the
 *   address flag, writes the register address, writes the data to the register, and finally generates a stop condition.
 *
 * Parameters:
 *   - reg: Register address to write to.
 *   - data: Data to be written to the specified register.
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void static QMC5883l_WriteReg(QMC5883l_RegType reg, uint8 data)
    {
      /* start condition */
      I2C_Master_start(&I2C_Ref);
      
      /* Compass address with write operation */
      I2C_writeAddress(&I2C_Ref, QMC5883L_ADDRESS << 1);
      
      /* clear address flag */
      I2C_clearAddressFlag(&I2C_Ref);
      
      /* register address */
      I2C_writeData(&I2C_Ref, reg);
      
      /* data written to the register */
      I2C_writeData(&I2C_Ref, data);
      
      /* stop condition */
      I2C_Master_stop(&I2C_Ref);
    }

/**************************************************************************************************************************************
 * @fn: QMC5833l_ReadReg
 * @brief: Reads a value from the specified register of the QMC5883L magnetometer sensor.
 *
 * Description:
 *   This function reads a value from the specified register of the QMC5883L magnetometer sensor through the I2C interface.
 *   It starts by generating a start condition on the I2C bus, writes the compass address with a write operation, clears the
 *   address flag, writes the register address to specify the location to be read from, generates a repeated start condition,
 *   writes the compass address with a read operation, disables the acknowledge bit, clears the address flag, generates a stop
 *   condition, and finally reads the data from the specified register.
 *
 * Parameters:
 *   - reg: Register address to read from.
 *   - data: Pointer to a variable where the read data will be stored.
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void QMC5833l_ReadReg(uint8 reg,uint8 *data)
    {
      /* start condition */
      I2C_Master_start(&I2C_Ref);
      
      /* Compass address with write operation */
      I2C_writeAddress(&I2C_Ref, QMC5883L_ADDRESS << 1);
      
      /* clear address flag */
      I2C_clearAddressFlag(&I2C_Ref);
      
      /* location to be read from */
      I2C_writeData(&I2C_Ref, reg);
      
      /* repeated start condition */
      I2C_Master_start(&I2C_Ref);
      
      /* Compass address with read operation */
      I2C_writeAddress(&I2C_Ref, (QMC5883L_ADDRESS << 1) | 1);
      /* disable ack bit */
      I2C_disableACK(&I2C_Ref);
      
      /* clear address flag */
      I2C_clearAddressFlag(&I2C_Ref);

      /* stop condition */
      I2C_Master_stop(&I2C_Ref);
      
      /* read data */
      I2C_readData(&I2C_Ref, data);
      
    }
/**************************************************************************************************************************************
 * @fn: QMC5883l_ReadData
 * @brief: Reads magnetometer data from the QMC5883L sensor.
 *
 * Description:
 *   This function reads magnetometer data from the QMC5883L sensor through the I2C interface. It first reads the status register
 *   to check if new data is available. Once new data is ready, it enables the ACK bit, generates a start condition, writes the
 *   compass address with a write operation, clears the address flag, writes the location to be read from, generates a repeated
 *   start condition, writes the compass address with a read operation, clears the address flag, reads data from the data registers,
 *   disables the ACK bit, generates a stop condition, and finally reads the last data register.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/
    void static QMC5883l_ReadData(void)
    {
      uint8 status;
    
      QMC5833l_ReadReg(QMC5883l_STATUS_REG, &status);
      while (GET_BIT(status, 0) == 0)
        ;
        /* enable ack bit */
          I2C_enableACK(&I2C_Ref);
          
          /* start condition */
          I2C_Master_start(&I2C_Ref);
          
          /* Compass address with write operation */
          I2C_writeAddress(&I2C_Ref, 0x0D << 1);
          
          /* clear address flag */
          I2C_clearAddressFlag(&I2C_Ref);
          
          /* location to be read from */
          I2C_writeData(&I2C_Ref, 0x00);
          
          /* repeated start condition */
          I2C_Master_start(&I2C_Ref);
          
          /* Compass address with read operation */
          I2C_writeAddress(&I2C_Ref, (0x0D << 1) | 0x01);
          
          /* clear address flag */
          I2C_clearAddressFlag(&I2C_Ref);
          
          /* read data from the data registers */
          I2C_read(&I2C_Ref, &(Data->x_lsb));
          I2C_read(&I2C_Ref, &(Data->x_msb));
          I2C_read(&I2C_Ref, &(Data->y_lsb));
          I2C_read(&I2C_Ref, &(Data->y_msb));
          I2C_read(&I2C_Ref, &(Data->z_lsb));
          
          /* disable ack bit */
          I2C_disableACK(&I2C_Ref);
          
          /* stop condition */
          I2C_Master_stop(&I2C_Ref);
    
          /* read last data register */
          I2C_read(&I2C_Ref, &(Data->z_msb)); 
    }
/**************************************************************************************************************************************
 * @fn: QMC5883l_GetAngel
 * @brief: Calculates the heading angle from the magnetometer data.
 *
 * Description:
 *   This function reads magnetometer data using QMC5883l_ReadData() and calculates the heading angle using the arctangent function.
 *   It converts the raw data to 16-bit signed integers and calculates the heading angle in degrees. The heading angle is then adjusted
 *   to ensure it falls within the range [0, 360) degrees.
 *
 * Parameters:
 *   - data: Pointer to a Qmc5883l_DataType structure where the calculated heading and raw magnetometer data will be stored.
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

  void QMC5883l_GetAngel(Qmc5883l_DataType *data)
  {
    QMC5883l_ReadData();
    data->x = (Data->x_msb << 8) | Data->x_lsb;
    data->y = (Data->y_msb << 8) | Data->y_lsb;
    data->z = (Data->z_msb << 8) | Data->z_lsb;
    data->heading = atan2(data->y, data->x)*(180/3.14159265);
    if (data->heading < 0) {
      data->heading += 360;
    }
    
  }



