/*
 * eeprom_an.h
 *
 *  Created on: Nov 18, 2018
 *      Author: Ayman
 */

#ifndef EEPROM_EEPROM_AN_H_
#define EEPROM_EEPROM_AN_H_

#include "std_types.h"

/* Function prototypes*/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 address, uint8 data);
uint8 EEPROM_readByte(uint16 address, uint8 *data );

#endif /* EEPROM_EEPROM_AN_H_ */
