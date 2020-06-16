/********************************************************************************
 * Module : USART
 *
 * File Name : usart.h
 *
 * Description : Header File For USART Driver
 *
 * Author : Shreef Mohamed
 *
 * Created on: Nov 3, 2018
 *
 ********************************************************************************/
#ifndef USART_H_
#define USART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600


/*******************************************************************************
 *                      STRUCTURES & ENUMS                                     *
 *******************************************************************************/
typedef enum {ASYNCHRONOUS,SYNCHRONOUS}USART_operationMode;
typedef enum {BIT_5,BIT_6,BIT_7,BIT_8,BIT_9=7}USART_numDataBits;
typedef enum {DISABLED,EVEN_PARITY=2,ODD_PARITY=3}USART_parityMode;
typedef enum {BIT_1,BIT_2}USART_numStopBits;
typedef enum {NORMAL_MODE,DOUBLE_SPEED_MODE}USART_transmissionSpeed;

typedef struct {
USART_operationMode operationMode ;
USART_numDataBits numDataBits ;
USART_parityMode parityMode ;
USART_numStopBits numStopBits ;
USART_transmissionSpeed transmissionSpeed ;
}USART_configType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void USART_init(const USART_configType *configPtr ) ;
void USART_sendByte (const uint8 data);
uint8 USART_recieveByte (void);
void USART_sendString (const uint8 *str);
void USART_recievString ( uint8 *str);




#endif /* USART_H_ */
