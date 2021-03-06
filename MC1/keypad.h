/********************************************************************************
 * Module : KEYPAD
 *
 * File Name : keypad.h
 *
 * Description : Header File For Keypad Driver
 *
 * Author : Shreef Mohamed
 *
 * Created on: Sep 16, 2018
 *
 ********************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*
 *  includes the H files That contain types , Macros and the Micro-controller Includes
 */
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_DIR DDRA

/*******************************************************************************
 *                      Functions Prototypes(Public)                           *
 *******************************************************************************/

/*
 * Function Responsible For Getting the Pressed Key
 */
unsigned char Keypad_getPressedKey (void) ;



#endif /* KEYPAD_H_ */
