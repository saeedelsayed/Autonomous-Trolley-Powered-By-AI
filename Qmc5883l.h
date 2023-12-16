/**************************************************************************************************************************************/
/****************************************************    Author     : Abram Gad    ****************************************************/
/****************************************************    Date       : 12/12/2023   ****************************************************/
/****************************************************    version    : V01          ****************************************************/
/**************************************************************************************************************************************/


#ifndef QMC5883L_H_ 
#define QMC5883L_H_

/*******************************************************************/

#define QMC5883L_ADDRESS 0x0D
#define QMC5883l_XMIN -1308
#define QMC5883l_XMAX 1658
#define QMC5883l_YMIN -1566
#define QMC5883l_YMAX 1320
#define QMC5883l_ZMIN -1123
#define QMC5883l_ZMAX 1455




typedef enum{
  QMC5883l_N,
  QMC5883l_NE,
  QMC5883l_E,
  QMC5883l_ES,
  QMC5883l_S,
  QMC5883l_SW,
  QMC5883l_W,
  QMC5883l_WN,

}QMC5883l_DirectionType;

typedef enum
{
    QMC5883l_OUT_REG_X_LSB,
    QMC5883l_OUT_REG_X_MSB,
    QMC5883l_OUT_REG_Y_LSB,
    QMC5883l_OUT_REG_Y_MSB,
    QMC5883l_OUT_REG_Z_LSB,
    QMC5883l_OUT_REG_Z_MSB,
    QMC5883l_STATUS_REG,
    QMC5883l_TEMP_LSB,
    QMC5883l_TEMP_MSB,
    QMC5883l_CONFIG_REG_1,
    QMC5883l_CONFIG_REG_2,
    QMC5833l_SET_RESET_REG
} QMC5883l_RegType;

typedef struct 
{
    uint8 x_lsb;
    uint8 x_msb;
    uint8 y_lsb;
    uint8 y_msb;
    uint8 z_lsb;
    uint8 z_msb;
}Qmc5883l_RawDataType;

typedef struct 
{
    sint16 x;
    sint16 y;
    sint16 z;
    float32 heading;
    uint8 direction;
}Qmc5883l_DataType;




void QMC5883l_Init(void);
void QMC5833l_ReadReg(uint8 reg, uint8 *data);
void QMC5883l_GetAngel(Qmc5883l_DataType *data);
void QMC5883l_SetInOutModule(I2C_config_t *I2C_PTR);
#endif