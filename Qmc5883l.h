/**************************************************************************************************************************************/
/****************************************************    Author     : Abram Gad    ****************************************************/
/****************************************************    Date       : 12/12/2023   ****************************************************/
/****************************************************    version    : V01          ****************************************************/
/**************************************************************************************************************************************/


#ifndef QMC5883L_H_ 
#define QMC5883L_H_

/*******************************************************************/
 /**
        OPTIONS:
        -> I2C1
        -> I2C2
        -> I2C3


**/
#define QMC5883l_I2cPort I2C1
/*******************************************************************/
#define QMC5883L_ADDRESS 0x0D
#define QMC5883l_XMIN 100
#define QMC5883l_XMAX 100
#define QMC5883l_YMIN 100
#define QMC5883l_YMAX 100
#define QMC5883l_ZMIN 100
#define QMC5883l_ZMAX 100

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
}Qmc5883l_DataType;




void QMC5883l_Init(void);
void QMC5833l_ReadReg(uint8 reg, uint8 *data);
void QMC5883l_GetAngel(Qmc5883l_DataType *data);
void QMC5883l_SetInOutModule(I2C_config_t *I2C_PTR);
#endif