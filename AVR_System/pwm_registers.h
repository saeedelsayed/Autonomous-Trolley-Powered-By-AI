/**
 * @file pwm_registers.h
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief pwm registers header file
 * @date 17-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PWM_REGISTERS_H
#define PWM_REGISTERS_H

/*******************************************************************************************/
/*********************************** Timer0 Registers **************************************/
/*******************************************************************************************/
#define TCNT0 (*((volatile uint8 *)0x52))
#define OCR0 (*((volatile uint8 *)0x5C))

#define TCCR0 (*((volatile uint8 *)0x53))
#define FOC0 7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02 2
#define CS01 1
#define CS00 0

/*******************************************************************************************/
/*********************************** Timer1 Registers **************************************/
/*******************************************************************************************/
#define ICR1 (*((volatile uint16 *)0x46))
#define ICR1L (*((volatile uint8 *)0x46))
#define ICR1H (*((volatile uint8 *)0x47))

#define OCR1B (*((volatile uint16 *)0x48))
#define OCR1BL (*((volatile uint8 *)0x48))
#define OCR1BH (*((volatile uint8 *)0x49))

#define OCR1A (*((volatile uint16 *)0x4A))
#define OCR1AL (*((volatile uint8 *)0x4A))
#define OCR1AH (*((volatile uint8 *)0x4B))

#define TCNT1 (*((volatile uint16 *)0x4C))
#define TCNT1L (*((volatile uint8 *)0x4C))
#define TCNT1H (*((volatile uint8 *)0x4D))

#define TCCR1B (*((volatile uint8 *)0x4E))
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#define TCCR1A (*((volatile uint8 *)0x4F))
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A 3
#define FOC1B 2
#define WGM11 1
#define WGM10 0

/*******************************************************************************************/
/************************************ Timer2 Registers *************************************/
/*******************************************************************************************/
#define OCR2 (*((volatile uint8 *)0x43))
#define TCNT2 (*((volatile uint8 *)0x44))

#define TCCR2 (*((volatile uint8 *)0x45))
#define FOC2 7
#define WGM20 6
#define COM21 5
#define COM20 4
#define WGM21 3
#define CS22 2
#define CS21 1
#define CS20 0

#endif /* PWM_REGISTERS_H */
