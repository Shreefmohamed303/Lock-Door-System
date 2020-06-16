/********************************************************************************
 * Module : I2C (TWI)
 *
 * File Name : i2c.h
 *
 * Description : Header File For i2C (TWI) Driver
 *
 * Author : Shreef Mohamed
 *
 * Created on: Nov 5, 2018
 *
 ********************************************************************************/


#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define TWPS_PRESCALER_VALUE 1
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W 0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave


/*******************************************************************************
 *                      STRUCTURES & ENUMS                                     *
 *******************************************************************************/
typedef enum{NORMAL_MODE,FAST_MODE,FAST_MODE_PLUS,HIGH_SPEED_MODE}TWI_speed_modes;
typedef enum{INTERRUPT_OFF,INTERRUPT_ON}TWI_inetrrupt_on_off ;

/* Configuration structure*/
typedef struct{
	TWI_speed_modes       speedMode;
	TWI_inetrrupt_on_off  interruptMode;
}TWI_SysConfig;

 /*******************************************************************************
  *                     FUNCTIONS PROTOTYPE                                     *
  *******************************************************************************/
void TWI_init ( TWI_SysConfig * a_configure_ptr) ;
void TWI_start (void) ;
void TWI_stop (void)  ;
void TWI_write (uint8 data)  ;
uint8 TWI_readWithAck (void) ;
uint8 TWI_readWithNack (void);
uint8 TWI_getStatus (void);


#endif /* I2C_H_ */
