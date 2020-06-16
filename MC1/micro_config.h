/********************************************************************************
 * Module : Micrp - Configration
 *
 * File Name : micro_config.h
 *
 * Description : File include All Microcontroller Libraries
 *
 * Author : Shreef Mohamed
 *
 * Created on: Sep 16, 2018
 *
 ********************************************************************************/


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_


#ifndef F_CPU
#define F_CPU 	8000000UL  // 1MHZ clock frequency
#endif


/***********************************************************************************************
 *                                    INCLUDES
 *********************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
