/*
 * MC2.c
 *
 *  Created on: Nov 20, 2018
 *      Author: Ayman
 */


#include "eeprom.h"
#include "usart.h"
#include "lcd.h"

#define DEFAULT_VALUE 0x41
#define MC_IS_READY 0x01
#define NO_OF_PINS 4

void eeprom_allocation(void);


uint16 DEFAULT_ADDRESS = 0x0310;
uint16 PASSWORD_ADDRESS = 0x0311;
uint8 password[NO_OF_PINS];

void main(void)
{

	//configuration for the USART
	USART_configType config = {ASYNCHRONOUS, BIT_8 , DISABLED , BIT_1 , DOUBLE_SPEED_MODE};
	USART_init(&config);
	/* Writing a default address with a default value to use as a check*/
	EEPROM_writeByte(DEFAULT_ADDRESS,DEFAULT_VALUE);
	_delay_ms(100) ;

	/* Defining new variable to use a check for the allocation */
	uint8 Value_of_mem;
	/*read the default value from the memory*/
	EEPROM_readByte(DEFAULT_ADDRESS , &Value_of_mem) ;

    /* Notify MC1 to be ready to start receiving
     * Start to send the default value of the memory
     */
	USART_sendByte(MC_IS_READY);
	USART_sendByte(Value_of_mem);

	/*Notify the MC1 that MC2 is ready to Receive the Password
	 * then MC2 Start to allocate the Password at the PASSWORD_ADDRESS
	 */
	USART_sendByte(MC_IS_READY);
	eeprom_allocation();
	PASSWORD_ADDRESS = 0x0311 ;

	/* Read the 1st value in the PASSWORD_ADDRESS
	 * to check that we already have set the password  */
	EEPROM_readByte(PASSWORD_ADDRESS , &Value_of_mem) ;

	USART_sendByte(MC_IS_READY);
	USART_sendByte(Value_of_mem);



	while(1)
	{

			if (USART_recieveByte()== '#')
			{
				uint8 counter;
				for(counter=0;counter<NO_OF_PINS;counter++)
				{
					EEPROM_readByte(PASSWORD_ADDRESS, &Value_of_mem);
					while(USART_recieveByte()!=MC_IS_READY){}
					USART_sendByte(Value_of_mem);
					PASSWORD_ADDRESS ++ ;

				}

				PASSWORD_ADDRESS = 0x0311;
			}

			else
			{
				DDRA=0xff;
				PORTA=0xff;
			while(USART_recieveByte()!=MC_IS_READY){}
			 eeprom_allocation();
			}

	}


}




void eeprom_allocation(void)
{
	uint8 counter;
	for(counter=0;counter<NO_OF_PINS;counter++)
	{
		password[counter]=USART_recieveByte();
	}

	for(counter=0;counter<NO_OF_PINS;counter++)
	{
		EEPROM_writeByte(PASSWORD_ADDRESS,password[counter]);
		_delay_ms(100) ;
		PASSWORD_ADDRESS++ ;
	}
}





















