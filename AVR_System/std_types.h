/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for AVR
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Data Types */
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float float32;
typedef double float64;
typedef unsigned char boolean;

/* NULL Pointer Definition */
#define NULL_PTR               ((void *)0)

/* Definition for boolean values */
#define TRUE                   1U
#define FALSE                  0U

/* Definition of logic values of in/out pins */
#define LOGIC_HIGH             1U
#define LOGIC_LOW              0U

/* Definitions for reporting errors */
#define SUCCESS                1U
#define FAIL                   0U

#define ON                     1U
#define OFF                    0U

#endif /* STD_TYPES_H_ */
