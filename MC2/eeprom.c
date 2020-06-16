/*
 * eeprom_an.c
 *
 *  Created on: Nov 18, 2018
 *      Author: Ayman
 */

#include "eeprom.h"
#include "i2c.h"

/* Initializing EEPROM chip of 24C16 that is 2048 Bytes of 11bits addressing is used*/
void EEPROM_init(void)
{
	TWI_SysConfig eeprom,*eeprom_config_ptr;
	eeprom_config_ptr= &eeprom;
	eeprom_config_ptr->speedMode = 0;
	eeprom_config_ptr->interruptMode = 0;

	TWI_init(&eeprom);
}


/* Writing a byte on specific address at EEPROM 24C16 with sending 0 for fail and 1 for success */
uint8 EEPROM_writeByte(uint16 address, uint8 data)
{
	/* Sending a start bit to being the communication then
	 * check for status */
	TWI_start();
	if(TW_START != TWI_getStatus() )
		{return 0;}

	/* Sending the chip address on bus by ORing 0x00A0 four high bits to MS 4bits then
	 * mask A10 A9 A8 to A3 A2 A1 by ANDing the address with 0x0700 to get the device address bits then shift by 7 to locate them at A3 A2 A1 then
	 * ORing by 0 for (write) command then
	 * checking for error */
	TWI_write((uint8) (0x00A0 | ((address & 0x0700)>>7) | 0));
	if(TW_MT_SLA_W != TWI_getStatus())
		{return 0;}

	/* Sending the memory address that is desired to be written in then
	 * checking for error */
	TWI_write((uint8) address);
	if(TW_MT_DATA != TWI_getStatus())
		{return 0;}

	/* Writing data to memory then
	 * checking for error */
	TWI_write(data);
	if(TW_MT_DATA != TWI_getStatus())
		{return 0;}

	/* Stop bit is set to stop communication*/
	TWI_stop();

	return 1;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_START)
        return 0;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W)
        return 0;

    /* Send the required memory location address */
    TWI_write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA)
        return 0;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_REP_START)
        return 0;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R)
        return 0;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNack();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return 0;

    /* Send the Stop Bit */
    TWI_stop();
    return 1;
}








