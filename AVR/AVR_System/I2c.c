
#include "std_types.h"
#include "Macros.h"
#include "I2c_private.h"
#include "I2c_cfg.h"
#include "I2c.h"

/**************************************************************************************************************************************
 * @fn: I2c_Slave_Init
 * @brief: Initializes the I2C module for slave mode.
 *
 * Description:
 *   This function is designed to initialize the I2C module for slave mode. It configures the address register with the provided 7-bit
 *   address and enables the TWI (Two-Wire Interface) module for slave mode.
 *
 * Parameters:
 *   - address: 7-bit address of the slave device.
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_Slave_Init(uint8 address)
    {
        /* Address Register */
        TWAR = (address << 1);
        /* TWI Enable Bit */
        SET_BIT(TWCR, TWCR_TWEN);
    }

/**************************************************************************************************************************************
 * @fn: I2c_Master_Init
 * @brief: Initializes the I2C module for master mode.
 *
 * Description:
 *   This function is designed to initialize the I2C module for master mode. It configures the address register with the provided 7-bit
 *   address, sets the bit rate with the TWBR register and prescaler with the TWSR register, and enables the TWI (Two-Wire Interface)
 *   module for master mode.
 *
 * Parameters:
 *   - address: 7-bit address of the master device.
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_Master_Init(uint8 address)
    {
        /* Address Register */
        TWAR = (address << 1);
        /* Bit Rate Select */
        TWBR = I2C_TWBR_VALUE;
        TWSR &= 0xFC;
        TWSR |= (I2C_TWPS_VALUE & 0x03);
        /* TWI Enable Bit */
        SET_BIT(TWCR, TWCR_TWEN);
    }

/**************************************************************************************************************************************
 * @fn: I2c_Master_SendStop
 * @brief: Sends the STOP condition on the I2C bus as a master.
 *
 * Description:
 *   This function is designed to send the STOP condition on the I2C bus as a master. It clears the TWI Interrupt Flag, sets the TWI
 *   module to send the STOP condition, and immediately sends the STOP condition without waiting for acknowledgment.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_Master_SendStop(void)
    {
        /* Clear TWI Interrupt Flag; And Send STOP Condition */
        TWCR |= (1 << TWCR_TWINT) | (1 << TWCR_TWSTO);
    }

/**************************************************************************************************************************************
 * @fn: I2c_Master_SendStart
 * @brief: Sends the START condition on the I2C bus as a master.
 *
 * Description:
 *   This function is designed to send the START condition on the I2C bus as a master. It clears the TWI Interrupt Flag, sets the TWI
 *   module to send the START condition, and waits until the start condition is transmitted. The function then retrieves the current
 *   I2C status using the I2C_GET_STATUS macro.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   I2c_StatusType: Current status of the I2C module after sending the START condition.
 *
 * ************************************************************************************************************************************/

    I2c_StatusType I2c_Master_SendStart(void)
    {
        /* Clear TWI Interrupt Flag; And Send START Condition */
        TWCR |= (1 << TWCR_TWINT) | (1 << TWCR_TWSTA);
        /* Wait till start condition is transmitted */
        while (GET_BIT(TWCR, TWCR_TWINT) == 0)
            ;
        /* Getting I2C Status */
        return I2C_GET_STATUS();
    }

/**************************************************************************************************************************************
 * @fn: I2c_Master_SendSlaveAddress
 * @brief: Sends the slave address on the I2C bus as a master.
 *
 * Description:
 *   This function is designed to send the slave address on the I2C bus as a master. It combines the 7-bit slave address and the request type
 *   to form the 8-bit address byte. The address byte is then loaded into the TWDR (TWI Data Register), the TWI Interrupt Flag is cleared,
 *   and the TWI module is enabled. The function waits until the TWI interrupt is complete and retrieves the current I2C status using the I2C_GET_STATUS macro.
 *
 * Parameters:
 *   - address: 7-bit slave address.
 *   - request: Type of request (I2C_REQUEST_READ or I2C_REQUEST_WRITE).
 *
 * Returns:
 *   I2c_StatusType: Current status of the I2C module after sending the slave address.
 *
 * ************************************************************************************************************************************/

    I2c_StatusType I2c_Master_SendSlaveAddress(uint8 address, I2c_RequestType request)
    {
        TWDR = ((address << 1) | request);
        /* Clear TWI Interrupt Flag and Clear Start */
        TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
        /* Wait till complete TWDR byte transmitted */
        while (GET_BIT(TWCR, TWCR_TWINT) == 0)
            ;
        /* Getting I2C Status */
        return I2C_GET_STATUS();
    }

/**************************************************************************************************************************************
 * @fn: I2c_WriteData
 * @brief: Writes data to the I2C bus.
 *
 * Description:
 *   This function is designed to write data to the I2C bus. It sets the TWDR (TWI Data Register) with the provided data,
 *   clears the TWI Interrupt Flag, waits until the TWI interrupt is complete, and retrieves the current I2C status using the I2C_GET_STATUS macro.
 *
 * Parameters:
 *   - data: Data to be transmitted on the I2C bus.
 *
 * Returns:
 *   I2c_StatusType: Current status of the I2C module after data writing.
 *
 * ************************************************************************************************************************************/

    I2c_StatusType I2c_WriteData(uint8 data)
    {
        TWDR = data;
        /* Clear TWI Interrupt Flag */
        SET_BIT(TWCR, TWCR_TWINT);
        /* Wait till complete TWDR byte transmitted */
        while (GET_BIT(TWCR, TWCR_TWINT) == 0)
            ;
        /* Getting I2C Status */
        return I2C_GET_STATUS();
    }

/**************************************************************************************************************************************
 * @fn: I2c_ReadData
 * @brief: Reads data from the I2C bus.
 *
 * Description:
 *   This function is designed to read data from the I2C bus. It clears the TWI Interrupt Flag, waits until the TWI interrupt is complete,
 *   reads the data from the TWDR (TWI Data Register), and retrieves the current I2C status using the I2C_GET_STATUS macro.
 *
 * Parameters:
 *   - data: Pointer to a variable where the received data will be stored.
 *
 * Returns:
 *   I2c_StatusType: Current status of the I2C module after data reading.
 *
 * ************************************************************************************************************************************/

    I2c_StatusType I2c_ReadData(uint8 *data)
    {
        /* Clear TWI Interrupt Flag */
        SET_BIT(TWCR, TWCR_TWINT);
        /* Wait till complete TWDR byte transmitted */
        while (GET_BIT(TWCR, TWCR_TWINT) == 0)
            ;
        /* Reading Data */
        *data = TWDR;
        /* Getting I2C Status */
        return I2C_GET_STATUS();
    }

/**************************************************************************************************************************************
 * @fn: I2c_GetFlag
 * @brief: Gets the value of the I2C Interrupt Flag.
 *
 * Description:
 *   This function is designed to retrieve the value of the I2C Interrupt Flag by using the GET_BIT macro on the TWCR register.
 *   The flag indicates the status of the I2C operation, showing whether an interrupt condition is pending or has been cleared.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   uint8: Value of the I2C Interrupt Flag (1 if set, 0 if cleared).
 *
 * ************************************************************************************************************************************/

    uint8 I2c_GetFlag(void)
    {
        return GET_BIT(TWCR, TWCR_TWINT);
    }

/**************************************************************************************************************************************
 * @fn: I2c_ClearFlag
 * @brief: Clears the I2C Interrupt Flag.
 *
 * Description:
 *   This function is designed to clear the I2C Interrupt Flag by setting the TWINT (TWCR Interrupt Flag) bit in the TWCR register.
 *   Clearing the flag indicates that the interrupt condition has been serviced or that the microcontroller is ready for the next I2C operation.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_ClearFlag(void)
    {
        SET_BIT(TWCR, TWCR_TWINT);
    }

/**************************************************************************************************************************************
 * @fn: I2c_GetStatus
 * @brief: Gets the current status of the I2C module.
 *
 * Description:
 *   This function is designed to retrieve the current status of the I2C module using the I2C_GET_STATUS macro.
 *   The status provides information about the ongoing state of the I2C communication, such as whether it is in the start condition,
 *   whether a specific address has been acknowledged, or if data has been sent or received successfully.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   I2c_StatusType: Current status of the I2C module.
 *
 * ************************************************************************************************************************************/

    I2c_StatusType I2c_GetStatus(void)
    {
        return I2C_GET_STATUS();
    }

/**************************************************************************************************************************************
 * @fn: I2c_EnableAck
 * @brief: Enables the I2C Acknowledge (ACK) bit.
 *
 * Description:
 *   This function is designed to enable the I2C Acknowledge (ACK) bit by setting the TWEA (TWCR Enable Acknowledge) bit in the TWCR register.
 *   Enabling ACK indicates that the I2C device will acknowledge the reception of data, allowing further data reception.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_EnableAck(void)
    {
        SET_BIT(TWCR, TWCR_TWEA);
    }

/**************************************************************************************************************************************
 * @fn: I2c_DisableAck
 * @brief: Disables the I2C Acknowledge (ACK) bit.
 *
 * Description:
 *   This function is designed to disable the I2C Acknowledge (ACK) bit by clearing the TWEA (TWCR Enable Acknowledge) bit in the TWCR register.
 *   Disabling ACK indicates that the I2C device will not acknowledge the reception of data, preventing further data reception.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_DisableAck(void)
    {
        CLR_BIT(TWCR, TWCR_TWEA);
    }

/**************************************************************************************************************************************
 * @fn: I2c_EnableGeneralCall
 * @brief: Enables the I2C general call recognition.
 *
 * Description:
 *   This function is designed to enable the I2C general call recognition by setting the TWGCE (TWAR General Call Enable) bit in the TWAR register.
 *   General call recognition allows the device to respond to a general call address sent by any master on the bus.
 *   Enabling general call recognition means that the device can respond to a broadcast message addressed to all devices on the bus.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_EnableGeneralCall(void)
    {
        SET_BIT(TWAR, TWAR_TWGCE);
    }

/**************************************************************************************************************************************
 * @fn: I2c_DisableGeneralCall
 * @brief: Disables the I2C general call recognition.
 *
 * Description:
 *   This function is designed to disable the I2C general call recognition by clearing the TWGCE (TWAR General Call Enable) bit in the TWAR register.
 *   General call recognition allows the device to respond to a general call address sent by any master on the bus.
 *   Disabling general call recognition ensures that the device only responds to its specific address.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 *
 * ************************************************************************************************************************************/

    void I2c_DisableGeneralCall(void)
    {
        CLR_BIT(TWAR, TWAR_TWGCE);
    }

/**************************************************************************************************************************************
 * @fn: I2c_Master_Transmit
 * @brief: Transmits data as a master on the I2C bus.
 *
 * Description:
 *   This function is designed to operate as a master in the I2C communication protocol and transmit a specified number of bytes to a slave device.
 *   It sends the start condition, checks if the start condition is sent successfully, sends the slave address, and checks if the slave address is acknowledged.
 *   If the slave address is acknowledged, it enters a loop to send data bytes one by one and checks for acknowledgment after each byte.
 *   After sending all data, it sends the stop condition and returns the success/error state.
 *
 * Parameters:
 *   - slave_address: The 7-bit address of the slave device.
 *   - dataBuffer: Pointer to the buffer containing the data to be transmitted.
 *   - length: Number of bytes to be transmitted.
 *
 * Returns:
 *   I2c_ErrorStateType: Error state after the transmission.
 *
 * ************************************************************************************************************************************/

    I2c_ErrorStateType I2c_Master_Transmit(uint8 slave_address, uint8 dataBuffer[], uint8 length)
    {
        uint8 i;
        I2c_StatusType status;
        /* Send Start Condition*/
        status = I2c_Master_SendStart();
        /* Check if start condition is sent successfully */
        if (status != I2C_STATUS_MASTER_START_SENT)
        {
            return I2C_ERROR_START_NOT_SENT;
        }
        /* Send Slave Address */
        status = I2c_Master_SendSlaveAddress(slave_address, I2C_REQUEST_WRITE);
        /* Check if slave address is sent successfully and Slave Respons */
        if (status != I2C_STATUS_MASTER_SA_W_ACK)
        {
            // Send Stop Condition
            I2c_Master_SendStop();
            return I2C_ERROR_SLA_NACK;
        }
        /* Send Data */
        for (i = 0; i < length; i++)
        {
            /* Write Data to TWDR Register */
            status = I2c_WriteData(dataBuffer[i]);
            /* Check if data is sent successfully and Slave Respons */
            if (status != I2C_STATUS_MASTER_DATA_SENT_ACK)
            {
                I2c_Master_SendStop();
                return I2C_ERROR_DATA_NACK;
            }
        }
        /* Send Stop Condition */
        I2c_Master_SendStop();
        return I2C_NO_ERROR;
    }

/**************************************************************************************************************************************
 * @fn: I2c_Slave_Receive
 * @brief: Receives data as a slave on the I2C bus.
 *
 * Description:
 *   This function is designed to operate as a slave in the I2C communication protocol and receive a specified number of bytes from the master device.
 *   It enables Acknowledge, clears the TWI Interrupt Flag, waits for the flag, and retrieves the I2C status.
 *   The function checks if the address is correct, then enters a loop to read data from the I2C bus and store it in the provided buffer.
 *   After receiving all data, it disables Acknowledge and returns the success/error state.
 *
 * Parameters:
 *   - dataBuffer: Pointer to the buffer where received data will be stored.
 *   - length: Number of bytes to be received.
 *
 * Returns:
 *   I2c_ErrorStateType: Error state after the reception.
 *
 * ************************************************************************************************************************************/

    I2c_ErrorStateType I2c_Slave_Receive(uint8 dataBuffer[], uint8 length)
    {
        uint8 i;
        uint8 temp_data;
        I2c_StatusType status = 0;
        // Enable Acknowledge
        I2c_EnableAck();

        /* Clear TWI Interrupt Flag */
        SET_BIT(TWCR, TWCR_TWINT);

        /*Wait for flag to be set, indicating an interrupt has occurred */
        while (GET_BIT(TWCR, TWCR_TWINT) == 0)
            ;

        /* Getting I2C Status */
        status = I2C_GET_STATUS();
        /* Check if Address is corect*/
        if (status != I2C_STATUS_SLAVE_SA_W_RECEIVED)
        {
            return I2C_ERROR_WRITE_REQUEST_NOT_RECEIVED;
        }
        /* Loop to receive the specified number of bytes */
        for (i = 0; i < length; i++)
        {
            /*  Read data from the I2C bus */
            status = I2c_ReadData(&temp_data);
            /* Check if data received successfully with ACK */
            if (status != I2C_STATUS_SLAVE_SA_DATA_RECEIVED_ACK)
            {
                return I2C_ERROR_DATA_NOT_RECEIVED;
            }
            else
            {
                /* Store the received data in the buffer */
                dataBuffer[i] = temp_data;
            }
        }
        /* Disable Acknowledge after receiving all data */
        I2c_DisableAck();
        return I2C_NO_ERROR;
    }
/**************************************************************************************************************************************
 * @fn: I2c_Master_Receive
 * @brief: Receives data as a master on the I2C bus.
 *
 * Description:
 *   This function is designed to operate as a master in the I2C communication protocol and receive a specified number of bytes from a slave device.
 *   It sends the start condition, checks if the start condition is sent successfully, sends the slave address for read operation, and checks if the
 *   slave address is acknowledged. If the slave address is acknowledged, it enables Acknowledge, enters a loop to read data from the I2C bus,
 *   stores the data in the provided buffer, and disables Acknowledge after receiving all data. Finally, it sends the stop condition and returns
 *   the success/error state.
 *
 * Parameters:
 *   - slave_address: The 7-bit address of the slave device.
 *   - dataBuffer: Pointer to the buffer where received data will be stored.
 *   - length: Number of bytes to be received.
 *
 * Returns:
 *   I2c_ErrorStateType: Error state after the reception.
 *
 * ************************************************************************************************************************************/
    I2c_ErrorStateType I2c_Master_Receive(uint8 slave_address, uint8 dataBuffer[], uint8 length)
    {
        uint8 i;
        uint8 temp_data;
        I2c_StatusType status;
        /* Send Start Condition*/
        status = I2c_Master_SendStart();
        /* Check if start condition is sent successfully */
        if (status != I2C_STATUS_MASTER_START_SENT)
        {
            return I2C_ERROR_START_NOT_SENT;
        }
        /* Send Slave Address */
        status = I2c_Master_SendSlaveAddress(slave_address, I2C_REQUEST_READ);
        /* Check if slave address is sent successfully and Slave Respons */
        if (status != I2C_STATUS_MASTER_SA_R_ACK)
        {
            // Send Stop Condition
            I2c_Master_SendStop();
            return I2C_ERROR_SLA_NACK;
        }
        // Enable Acknowledge
        I2c_EnableAck();
        for (i = 0; i < length; i++)
        {
            /*  Read data from the I2C bus */
            status = I2c_ReadData(&temp_data);
            /* Check if data received successfully with ACK */
            if (status != I2C_STATUS_MASTER_DATA_RECEIVED_ACK)
            {
                I2c_DisableAck();
                I2c_Master_SendStop();
                return I2C_ERROR_DATA_NOT_RECEIVED;
            }
            else
            {
                /* Store the received data in the buffer */
                dataBuffer[i] = temp_data;
            }
        }
        /* Disable Acknowledge after receiving all data */
        I2c_DisableAck();
        I2c_Master_SendStop();
        return I2C_NO_ERROR;
    }



