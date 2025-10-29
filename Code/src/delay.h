/* 
 * File:    delay.h
 * 
 * Author:  Felix Neumann
 *
 * @desc    This file implements an delay function by using the Timer TC3
 *          of the microcontroller SAMD21.
 * 
 * @Hardware
 *          Microcontroller     ->  SAMD21J18A
 *  
 * Created on 26. September 2025, 11:16
 */

#ifndef DELAY_H
#define	DELAY_H

#include <stdbool.h> 
#include <stdint.h>
#include "definitions.h" 

//flag for delay_ms()
extern volatile bool delayDone;

/**
 * @desc    callback function for the delay_ms() funcion
 * 
 *          The function is called when the TC3 timer
 *          has counted up to one millisecond.
 *    
 * @param   TC_TIMER_STATUS status
 * @param   uintptr_t context      
 *
 * @return  void
 */
void TC3_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context);

/**
 * @desc    This function delays the program sequence by a specified time.
 *     
 * @param   uint16_t delayTime      ->  delay time in milliseconds      
 *
 * @return  void
 */
void delay_ms(uint16_t delayTime);

#endif	/* DELAY_H */

