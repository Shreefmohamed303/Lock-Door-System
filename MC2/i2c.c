/********************************************************************************
 * Module : I2C (TWI)
 *
 * File Name : i2c.c
 *
 * Description : Source File For i2C (TWI) Driver
 *
 * Author : Shreef Mohamed
 *
 * Created on: Nov 5, 2018
 *
 ********************************************************************************/


#include "i2c.h"



 void TWI_init ( TWI_SysConfig * a_configure_ptr)
 {
	 /* Configure the Speed of Trasmitting data in i2c
	  * Normal_Mode     : 0
	  * Fast_Mode_Plus  : 1
	  * High_Speed_mode : 2
	  */
	 switch (a_configure_ptr->speedMode)
	 {
	 case 0 : TWBR = ((F_CPU/100000 -16)/(2*TWPS_PRESCALER_VALUE)) ;
	          break ;
	 case 1 : TWBR = ((F_CPU/400000 -16)/(2*TWPS_PRESCALER_VALUE)) ;
	          break ;
	 case 2 : TWBR = ((F_CPU/1000000 -16)/(2*TWPS_PRESCALER_VALUE)) ;
	          break ;
	 case 3 : TWBR = ((F_CPU/4300000 -16)/(2*TWPS_PRESCALER_VALUE)) ;
	          break ;
	 }


	 /* Checking on the prescaler value to mask TWPS0 & TWPS1 */
#if (TWPS_PRESCALER_VALUE == 1)
	 {
		 TWCR = (TWCR & 0xFC) | (0<<TWPS0);
	 }
#elif (TWPS_PRESCALER_VALUE == 4)
	 {
		 TWCR = (TWCR & 0xFC) | (1<<TWPS0);
	 }
#elif (TWPS_PRESCALER_VALUE == 16)
	 {
		 TWCR = (TWCR & 0xFC) | (2<<TWPS0);
	 }
#elif (TWPS_PRESCALER_VALUE == 64)
	 {
		 TWCR = (TWCR & 0xFC) | (3<<TWPS0);
	 }
#endif


	 /* Anding TWCR register with 0xFE to save the 7MSbits then Oring
	  * interruptMode = 1 ==> 'interrupt on  ' bit is set
	  * interruptMode = 0 ==> 'interrupt off ' bit is cleared */


    TWCR = (TWCR & 0xFE) | ( (a_configure_ptr->interruptMode) << TWIE ) ;
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = 0b00000010; // my address = 0x01


    /* Enable bit for the TWI*/
    TWCR = ( 1<<TWEN) ;
 }

 void TWI_start (void)
 {
	    /*
		 * Clear the TWINT flag before sending the start bit TWINT=1
		 * send the start bit by TWSTA=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	    while( BIT_IS_CLEAR(TWCR,TWINT) ) {}
 }

 void TWI_stop (void)
 {
	    /*
		 * Clear the TWINT flag before sending the stop bit TWINT=1
		 * send the start bit by TWSTO=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
 }

 void TWI_write (uint8 data)
 {
	 /* Put data On TWI data Register */
	 TWDR = data ;
     /*
      * Clear the TWINT flag before sending the data TWINT=1
      * Enable TWI Module TWEN=1
	  */
	 TWCR = (1<<TWINT) | (1<<TWEN) ;
	 /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	 while( BIT_IS_CLEAR(TWCR,TWINT) ) {}
 }

uint8 TWI_readWithAck (void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	 while( BIT_IS_CLEAR(TWCR,TWINT) ) {}
	/* Read Data */
	 return TWDR ;
}

uint8 TWI_readWithNack (void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus (void)
{
	uint8 status ;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = (TWSR & 0xF8) ;
	return status ;
}
