/********************************************************************************
 * Module : USART
 *
 * File Name : usart.c
 *
 * Description : Source File For USART Driver
 *
 * Author : Shreef Mohamed
 *
 * Created on: Nov 3, 2018
 *
 ********************************************************************************/

#include "usart.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)




void USART_init (const USART_configType *configPtr )
{
	/* RXEN  = 1 Receiver Enable
	 * TXEN  = 1 Transmitter Enable */
	UCSRB = (1<<RXEN) | (1<<TXEN);


	/* URSEL bit must equal when we use UCSRC REG */
	UCSRC |=(1<<URSEL);


	/*
	 * USART_operationMode
	 * 1-ASYNCHRONOUS ( this case we put zero in UMSEL)
	 * 2-SYNCHRONOUS  ( this case we put one  in UMSEL)
	 */
	UCSRC = (UCSRC & 0xBF) | ( (configPtr->operationMode) << UMSEL);


	/*
	 * USART_numDataBits
	 *  BIT_5 (UCSZ2=0 , UCSZ1=0 , UCSZ0=0 )
	 *  BIT_6 (UCSZ2=0 , UCSZ1=0 , UCSZ0=1 )
	 *  BIT_7 (UCSZ2=0 , UCSZ1=1 , UCSZ0=0 )
	 *  BIT_8 (UCSZ2=0 , UCSZ1=1 , UCSZ0=1 )
	 *  BIT_9 (UCSZ2=1 , UCSZ1=1 , UCSZ0=1 )  Note that UCSZ2 in UCSRB REG and BIT_9 = 7
	 */
	if ((configPtr->operationMode) <4)
	{
		UCSRC = (UCSRC & 0xF9) | ( (configPtr->numDataBits) << UCSZ0) ;
	}
	else if ( (configPtr->operationMode) ==7)
	{
		UCSRC = (UCSRC & 0xF9) | (3<<UCSZ0) ;
		UCSRB |= (1<<UCSZ2);
	}


	/*
	 * USART_parityMode
	 *  -Disabled     : ( UPM1=0 , UPM0=0 )
	 *  -Even parity  : ( UPM1=1 , UPM0=0 )
	 *  -odd parity   : ( UPM1=1 , UPM0=1 )
	 */
	UCSRC = (UCSRC & 0xCF) | ( (configPtr->parityMode) << UPM0 );


	/*
	 * USART_numStopBits
	 *  - 1 stop bit
	 *  - 2 stop bits
	 */
	UCSRC = (UCSRC & 0xF7) | ( (configPtr->numStopBits) <<USBS ) ;

	/*
	 * USART_transmissionSpeed
	 *  -Normal Mode       : U2X=0
	 *  -Double Speed Mode : U2X=1
	 */
	UCSRA = (UCSRA & 0x00) | ( (configPtr->transmissionSpeed) << U2X) ;


	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;

}
void USART_sendByte (const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while (BIT_IS_CLEAR (UCSRA,UDRE)) {}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR= data ;
	/************************* Another Method *************************
	UDR = data;
	//Wait until the transmission is complete TXC = 1
	// it's take more time as we wait until the data transmission complete
	while(BIT_IS_CLEAR(UCSRA,TXC)){}
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

uint8 USART_recieveByte (void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while (BIT_IS_CLEAR(UCSRA,RXC)) {}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR ;
}

void USART_sendString (const uint8 *str)
{
	uint8 i=0;
	while (str[i]!= '\0')
	{
		USART_sendByte(str[i]) ;
		i++ ;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}


void USART_recievString ( uint8 *str)
{
	uint8 i=0;
	str[i]=USART_recieveByte();
	while( str[i]!='\0' )
	{
		i++;
		str[i]=USART_recieveByte();
	}
}
