/******************************************************************************
 * @file     Main.c
 * @brief    Easy Start project:
 * 			 Toggle LED1(P1_1) and LED2(P1_0) of a Lite board.
 * 			 Using push buttons BUTTON1(P1_14) and BUTTON2(P1_15), stop toggling
 * 			 LED1 and LED2 respectively
 * @version  V1.0
 * @date     20. February 2015
 * @note
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon’s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/

/* SFR declarations of the selected device */
#include <XMC4500.h>
#include "GPIO.h"

void SysTick_Handler(void);

typedef enum { OFF = 0, ON = 1} state_t ;
state_t led1_state = ON;
state_t led2_state = ON;


int main(void) {
	/* Initialize LED1 */
	P1_1_set_mode(OUTPUT_PP_GP);
	P1_1_set_driver_strength(STRONG);

	/* Initialize LED2 */
	P1_0_set_mode(OUTPUT_PP_GP);
	P1_0_set_driver_strength(STRONG);
	
	/* Initialize BUTTON1 */
	P1_14_set_mode(INPUT);
	
	/* Initialize BUTTON2 */
	P1_15_set_mode(INPUT);

	/* fSYS=fCPU at 120MHz */
	/* Systick every 120000 cycles = 10ms */
	if(SysTick_Config(SystemCoreClock / 100UL) == 0){

		/* Loop forever */
		for(;;) {
		}
	}
	else{
		asm("BKPT 255");
	}

}

void SysTick_Handler(void) {
	static uint32_t ticks = 0UL;
	static state_t button1_state = OFF;
	static state_t button2_state = OFF;

	ticks++;

	/* Read BUTTON1, update state if pressed */
	if(P1_14_read() == 0UL){
		button1_state = ON;
	}
	else{
		if(button1_state == ON){
			if(led1_state == ON){
				led1_state = OFF;
			}
			else{
				led1_state = ON;
			}
		}
		button1_state = OFF;
	}

	/* Read BUTTON2, update state if pressed */
	if(P1_15_read() == 0UL){
		button2_state = ON;
	}
	else{
		if(button2_state == ON){
			if(led2_state == ON){
				led2_state = OFF;
			}
			else{
				led2_state = ON;
			}
		}
		button2_state = OFF;
	}

	/* Toggle every 1s */
	if(ticks == 100UL){
		if(led1_state == ON){
			/* Toggle LED1 */
			P1_1_toggle();
		}

		if(led2_state == ON){
			/* Toggle LED2 */
			P1_0_toggle();
		}

		ticks = 0UL;
	}
}
