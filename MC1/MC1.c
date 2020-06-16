/*
 * MC1.c
 *
 *  Created on: Nov 19, 2018
 *      Author: Ayman
 */

#include "lcd.h"
#include "keypad.h"
#include "usart.h"
#include "std_types.h"


#define MC_IS_READY 0x01
#define DEFAULT_VALUE 0x41
#define NO_OF_PINS 4

uint8 Value_of_mem ;
uint8 g_flag = 0;
uint8 verification_password[NO_OF_PINS];
uint8 password[NO_OF_PINS];

/* Function prototypes*/
void takingPwFromUser(void);
void verifingPw(void);
void comparePw(void);



void main(void)
{
	USART_configType config = {ASYNCHRONOUS, BIT_8 , DISABLED , BIT_1 , DOUBLE_SPEED_MODE};
	USART_init(&config);
	//USART_sendByte(MC_IS_READY);

	/* Initiating the lcd */
	LCD_init();

	/* Checking if the user is first time to enter PW or not by reading a defined value from memory
	 * Loop assures that the PW is entered successfully*/


while(1)
{
	while(USART_recieveByte()!=MC_IS_READY){}
Value_of_mem = USART_recieveByte() ;
	if(Value_of_mem==DEFAULT_VALUE)
	{

		while(g_flag==0)
		{
			takingPwFromUser();
			verifingPw();
			comparePw();
		}
		while(USART_recieveByte()!=MC_IS_READY){}
		 uint8 counter;
		for(counter=0;counter<NO_OF_PINS;counter++)
		{
			USART_sendByte(password[counter]);
		}
	}

	else
	{
		LCD_displayStringRowColumn(0,0,"#:To ENTER PW");
		LCD_displayStringRowColumn(1,0,"*:To CHANGE PW");

		uint8 check_Key = Keypad_getPressedKey();
		_delay_ms(1000);
		USART_sendByte(check_Key);

		if( check_Key == '#')
		{
			uint8 counter;
			LCD_clearScreen();
			takingPwFromUser();

			for(counter=0;counter<NO_OF_PINS;counter++)
			{
				USART_sendByte(MC_IS_READY);
				verification_password[counter] = USART_recieveByte();
			}
			comparePw();
			LCD_displayString("Door is open");
			_delay_ms(10000);

		}
		else if(check_Key =='*')
		{
			g_flag = 0;

			while(g_flag==0)
			{
				takingPwFromUser();
				verifingPw();
				comparePw();
			}

			 uint8 counter;
			 USART_sendByte(MC_IS_READY);
			for(counter=0;counter<NO_OF_PINS;counter++)
			{
				USART_sendByte(password[counter]);
			}


		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("INCORRECT ENTERY !");
		}


	}


}



return ;
}



/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

void takingPwFromUser(void)
{
	/* clearing screen then
	 * sending enter a password string to lcd */
	LCD_clearScreen();

	LCD_displayString("ENTER PW");
	//_delay_ms(3000);

	/* Defining an incrementing variable and array of chars to save the password
	 * the array is defined static to be used when the function finishes executing
	 * password is taken from user by a keypad */
	uint8 no_of_pressed_keys=0;

	while(no_of_pressed_keys < NO_OF_PINS)
	{
		password[no_of_pressed_keys] = Keypad_getPressedKey();
		_delay_ms(1500);
		LCD_goToRowColumn(1,no_of_pressed_keys);

		LCD_displayCharacter('*');
		no_of_pressed_keys ++;
	}
}


void verifingPw(void)
{
	/* Clearing the screen to re display a verification message to the user to re enter
	 * the password again then compares the 2nd password to the last one
	 * if matches then continue, if not then print an error message */
	LCD_clearScreen();


	LCD_displayString("Verify the PW");
	//_delay_ms(3000);

	uint8 no_of_pressed_keys = 0;
	while(no_of_pressed_keys < NO_OF_PINS)
	{

		verification_password[no_of_pressed_keys] = Keypad_getPressedKey();
		_delay_ms(1200);
		LCD_goToRowColumn(1,no_of_pressed_keys);

		LCD_displayCharacter('*');
		no_of_pressed_keys ++;
	}

}


void comparePw(void)
{
	/* Clearing Screen &
	 * Comparing the 2 entered passwords*/
	 uint8 counter;
	for(counter=0;counter<NO_OF_PINS;counter++)
	{
		if (verification_password[counter] != password[counter])
		{


			/* Flashing PW doesn't match string to the user indicating that the password is incorrect*/
			LCD_clearScreen();
			LCD_displayString("PW doesn't match");
			_delay_ms(1000);
			LCD_clearScreen();
			_delay_ms(1000);
			LCD_displayString("PW doesn't match");
			_delay_ms(1000);
			LCD_clearScreen();
			return;
		}
	}
	/* Printing success on the lcd indicating that the PW is successfully entered &
	 * setting flag by 1 to terminate the initiation loop at the main function */
	LCD_clearScreen();
	LCD_displayString("Success");
	_delay_ms(3000);
	LCD_clearScreen();
	g_flag = 1 ;
}



































