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
void static applyCalibration(Qmc5883l_DataType *data);
void static setCalibrationScales(float32 x_scale, float32 y_scale, float32 z_scale);
void static setCalibrationOffsets(float32 x_offset, float32 y_offset, float32 z_offset);
void static setCalibration(sint16 x_min, sint16 x_max, sint16 y_min, sint16 y_max, sint16 z_min, sint16 z_max);

float32 static Offset[3] = {0};
float32 static Scale[3] = {1, 1, 1};



static I2C_config_t *compassInOutModule = NULL_PTR;

Qmc5883l_RawDataType RawData = {0, 0, 0, 0, 0, 0};

/**************************************************************************************************************************************
* @fn: QMC5883l_Init
* @brief: Initializes the QMC5883L magnetometer sensor.
*
* Description:
*   This function initializes the QMC5883L magnetometer sensor by configuring its settings through the I2C interface.
*   It first initializes the I2C module using the specified reference (compassInOutModule). Then, it writes specific values to the QMC5883L
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
  QMC5883l_WriteReg(QMC5833l_SET_RESET_REG, 0x01);
  QMC5883l_WriteReg(QMC5883l_CONFIG_REG_1, 0x1D);
  setCalibration(QMC5883l_XMIN, QMC5883l_XMAX, QMC5883l_YMIN, QMC5883l_YMAX, QMC5883l_ZMIN, QMC5883l_ZMAX);
}

void QMC5883l_SetInOutModule(I2C_config_t *I2C_PTR)
{
  compassInOutModule = I2C_PTR;
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
  I2C_Master_start(compassInOutModule);
  
  /* Compass address with write operation */
  I2C_writeAddress(compassInOutModule, QMC5883L_ADDRESS << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(compassInOutModule);
  
  /* register address */
  I2C_writeData(compassInOutModule, reg);
  
  /* data written to the register */
  I2C_writeData(compassInOutModule, data);
  
  /* stop condition */
  I2C_Master_stop(compassInOutModule);
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

void QMC5833l_ReadReg(uint8 reg, uint8 *data)
{
  /* start condition */
  I2C_Master_start(compassInOutModule);
  
  /* Compass address with write operation */
  I2C_writeAddress(compassInOutModule, QMC5883L_ADDRESS << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(compassInOutModule);
  
  /* location to be read from */
  I2C_writeData(compassInOutModule, reg);
  
  /* repeated start condition */
  I2C_Master_start(compassInOutModule);
  
  /* Compass address with read operation */
  I2C_writeAddress(compassInOutModule, (QMC5883L_ADDRESS << 1) | 1);
  /* disable ack bit */
  I2C_disableACK(compassInOutModule);
  
  /* clear address flag */
  I2C_clearAddressFlag(compassInOutModule);
  
  /* stop condition */
  I2C_Master_stop(compassInOutModule);
  
  /* read data */
  I2C_read(compassInOutModule, data);
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
  uint8 status = 0;
  
  while (GET_BIT(status, 0) == 0)
  {
    QMC5833l_ReadReg(QMC5883l_STATUS_REG, &status);
  }
  /* enable ack bit */
  I2C_enableACK(compassInOutModule);
  
  /* start condition */
  I2C_Master_start(compassInOutModule);
  
  /* Compass address with write operation */
  I2C_writeAddress(compassInOutModule, QMC5883L_ADDRESS << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(compassInOutModule);
  
  /* location to be read from */
  I2C_writeData(compassInOutModule, 0x00);
  
  /* repeated start condition */
  I2C_Master_start(compassInOutModule);
  
  /* Compass address with read operation */
  I2C_writeAddress(compassInOutModule, (QMC5883L_ADDRESS << 1) | 0x01);
  
  /* clear address flag */
  I2C_clearAddressFlag(compassInOutModule);
  
  /* read data from the data registers */
  I2C_read(compassInOutModule, &(RawData.x_lsb));
  I2C_read(compassInOutModule, &(RawData.x_msb));
  I2C_read(compassInOutModule, &(RawData.y_lsb));
  I2C_read(compassInOutModule, &(RawData.y_msb));
  I2C_read(compassInOutModule, &(RawData.z_lsb));
  
  /* disable ack bit */
  I2C_disableACK(compassInOutModule);
  
  /* stop condition */
  I2C_Master_stop(compassInOutModule);
  
  /* read last data register */
  I2C_read(compassInOutModule, &(RawData.z_msb));
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
  data->x = (RawData.x_msb << 8) | RawData.x_lsb;
  data->y = (RawData.y_msb << 8) | RawData.y_lsb;
  data->z = (RawData.z_msb << 8) | RawData.z_lsb;
  
  applyCalibration(data);
  
  data->heading = atan2(data->y, data->x) * (180 / 3.14159265);
  
  if (data->heading < 0)
  {
    data->heading += 360;
  }
  if((data->heading>337.5 )&&(data->heading<=22.5 )){
     data->direction = QMC5883l_N;
  }
  else if((data->heading>22.5 )&&(data->heading<=67.5 )){
    data->direction = QMC5883l_NE;
  }
  else if((data->heading>67.5 )&&(data->heading<=112.5 )){
    data->direction = QMC5883l_E;
  }
  else if((data->heading>112.5 )&&(data->heading<=157.5 )){
    data->direction = QMC5883l_ES;
  }
  else if((data->heading>157.5 )&&(data->heading<=202.5 )){
    data->direction = QMC5883l_S;
  }
  else if((data->heading>202.5 )&&(data->heading<=247.5 )){
    data->direction = QMC5883l_SW;
  }
  else if((data->heading>247.5 )&&(data->heading<=292.5 )){
    data->direction = QMC5883l_W;
  }
  else {
    data->direction = QMC5883l_WN;
  }
}

void static setCalibration(sint16 x_min, sint16 x_max, sint16 y_min, sint16 y_max, sint16 z_min, sint16 z_max)
{
  setCalibrationOffsets(((x_min + x_max) / 2.0), ((y_min + y_max) / 2.0), ((z_min + z_max) / 2.0));
  
  float32 x_avg_delta = (x_max - x_min) / 2;
  float32 y_avg_delta = (y_max - y_min) / 2;
  float32 z_avg_delta = (z_max - z_min) / 2;
  
  float32 avg_delta = (x_avg_delta + y_avg_delta + z_avg_delta) / 3;
  
  setCalibrationScales(avg_delta / x_avg_delta, avg_delta / y_avg_delta, avg_delta / z_avg_delta);
}

void static setCalibrationOffsets(float32 x_offset, float32 y_offset, float32 z_offset)
{
  Offset[0] = x_offset;
  Offset[1] = y_offset;
  Offset[2] = z_offset;
}

void static setCalibrationScales(float32 x_scale, float32 y_scale, float32 z_scale)
{
  Scale[0] = x_scale;
  Scale[1] = y_scale;
  Scale[2] = z_scale;
}

void static applyCalibration(Qmc5883l_DataType *data)
{
  data->x = (sint16)((data->x - Offset[0]) * Scale[0]);
  data->y = (sint16)((data->y - Offset[1]) * Scale[1]);
  data->z = (sint16)((data->z - Offset[2]) * Scale[2]);
}

