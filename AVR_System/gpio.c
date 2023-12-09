/******************************************************************************
*
* Module: GPIO module
*
* File Name: gpio.c
*
* Description: source file for the GPIO module
*
* Author: Abdelrahman Saeed
*
*******************************************************************************/

#include "gpio_registers.h"
#include "gpio.h"

/*
* description : the function is used to configure the required pin in the required
*               port as input or output as specified in the pinMode parameter. It is
*               also responsible for reporting success or failure of the operation.
*
* parameters  : portId represents port number, pinId represents pin number,
*               pinMode represents input or ouput mode of the pin, pinInitialState
*               represents initial state of the output pin, pinPullUpActivation
*               represents activation of the pull up option.
*
* return value : the function returns success or failure of the configuration.
*/
uint8 GPIO_pinConfiguration(uint8 portId, uint8 pinId, uint8 pinMode,
uint8 pinInitialState, uint8 pinPullUpActivation) {

	/* pointer to hold the start address of the port registers */
	uint8 *startAddrees_ptr = NULL_PTR;
	#if (GPIO_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if (portId >= TOTAL_NUMBER_OF_PORTS || pinId >= TOTAL_NUMBER_OF_PINS
	|| (pinMode != INPUT_PIN && pinMode != OUTPUT_PIN)
	|| (pinPullUpActivation != PULL_UP_DEACTIVATION
	&& pinPullUpActivation != PULL_UP_ACTIVATION)) {
		/* return fail of the configuration */
		return FAIL;
	}
	#endif

	/* select the start address of the required port */
	switch (portId) {
		case PORTA_ID:
		/* start address of PORT A */
		startAddrees_ptr = PORTA_START_ADDRESS;
		break;
		case PORTB_ID:
		/* start address of PORT B */
		startAddrees_ptr = PORTB_START_ADDRESS;
		break;
		case PORTC_ID:
		/* start address of PORT C */
		startAddrees_ptr = PORTC_START_ADDRESS;
		break;
		case PORTD_ID:
		/* start address of PORT D */
		startAddrees_ptr = PORTD_START_ADDRESS;
		break;
	}

	/* set the required mode of the pin through data direction register */
	(*(startAddrees_ptr + DATA_DIRECTION_REGISTER_OFFSET)) =
	((*(startAddrees_ptr + DATA_DIRECTION_REGISTER_OFFSET))
	& (~(1 << pinId))) | (pinMode << pinId);

	if (pinMode == OUTPUT_PIN) {
		/* if the pin is output, initialize the pin with the initial value
		* through data output register
		*/
		(*(startAddrees_ptr + DATA_OUTPUT_REGISTER_OFFSET)) =
		((*(startAddrees_ptr + DATA_OUTPUT_REGISTER_OFFSET))
		& (~(1 << pinId))) | (pinInitialState << pinId);
		} else {
		/*
		* if the pin is input, enable or disable the pull up of the pin
		* through the data output register
		*/
		(*(startAddrees_ptr + DATA_OUTPUT_REGISTER_OFFSET)) =
		((*(startAddrees_ptr + DATA_OUTPUT_REGISTER_OFFSET))
		& (~(1 << pinId))) | (pinPullUpActivation << pinId);
	}

	/* return success of the configuration */
	return SUCCESS;
}

/*
* description : the function is used to write the required pin in the required
*               port with the specified value in the pinValue parameter. It is
*               also responsible for reporting success or failure of the operation.
*
* parameters  : portId represents port number, pinId represents pin number,
*               pinValue represents the value to be written.
*
* return value : the function returns success or failure of the operation.
*/
uint8 GPIO_writePin(uint8 portId, uint8 pinId, uint8 pinValue) {
	/* pointer to hold the start address of the port registers */
	uint8 *startAddrees_ptr = NULL_PTR;
	#if (GPIO_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if (portId >= TOTAL_NUMBER_OF_PORTS || pinId >= TOTAL_NUMBER_OF_PINS) {
		/* return fail of the operation */
		return FAIL;
	}
	#endif

	/* select the start address of the required port */
	switch (portId) {
		case PORTA_ID:
		/* start address of PORT A */
		startAddrees_ptr = PORTA_START_ADDRESS;
		break;
		case PORTB_ID:
		/* start address of PORT B */
		startAddrees_ptr = PORTB_START_ADDRESS;
		break;
		case PORTC_ID:
		/* start address of PORT C */
		startAddrees_ptr = PORTC_START_ADDRESS;
		break;
		case PORTD_ID:
		/* start address of PORT D */
		startAddrees_ptr = PORTD_START_ADDRESS;
		break;
	}

	/* write the required value in the pin through data output register */
	(*(startAddrees_ptr + DATA_OUTPUT_REGISTER_OFFSET)) = ((*(startAddrees_ptr
	+ DATA_OUTPUT_REGISTER_OFFSET)) & (~(1 << pinId)))
	| (pinValue << pinId);

	/* return success of the operation */
	return SUCCESS;
}

/*
* description : the function is used to read the required pin in the required
*               port and put the value in the pinValue_ptr. It is also responsible
*               for reporting success or failure of the operation.
*
* parameters  : portId represents port number, pinId represents pin number,
*               pinValue_ptr represents the location in which the value should be
*               written.
*
* return value : the function returns success or failure of the operation.
*/
uint8 GPIO_readPin(uint8 portId, uint8 pinId, uint8 *pinValue_ptr) {
	/* pointer to hold the start address of the port registers */
	uint8 *startAddrees_ptr = NULL_PTR;
	#if (GPIO_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if (portId >= TOTAL_NUMBER_OF_PORTS || pinId >= TOTAL_NUMBER_OF_PINS
	|| pinValue_ptr == NULL_PTR) {
		/* return fail of the operation */
		return FAIL;
	}
	#endif

	/* select the start address of the required port */
	switch (portId) {
		case PORTA_ID:
		/* start address of PORT A */
		startAddrees_ptr = PORTA_START_ADDRESS;
		break;
		case PORTB_ID:
		/* start address of PORT B */
		startAddrees_ptr = PORTB_START_ADDRESS;
		break;
		case PORTC_ID:
		/* start address of PORT C */
		startAddrees_ptr = PORTC_START_ADDRESS;
		break;
		case PORTD_ID:
		/* start address of PORT D */
		startAddrees_ptr = PORTD_START_ADDRESS;
		break;
	}

	/* checking the value of the pin */
	if (((*(startAddrees_ptr + DATA_INPUT_REGISTER_OFFSET)) & (1 << pinId))) {
		*pinValue_ptr = LOGIC_HIGH;
		} else {
		*pinValue_ptr = LOGIC_LOW;
	}

	/* return success of the operation */
	return SUCCESS;
}
