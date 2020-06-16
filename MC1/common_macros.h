/********************************************************************************
 * Module : Common - Macros
 *
 * File Name : common_macros.h
 *
 * Description : Commanly used Macros
 *
 * Author : Shreef Mohamed
 *
 * Created on: Sep 16, 2018
 *
 ********************************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a Certain bit in any Register */
#define SET_BIT(REG,BIT) (REG |= (1<<BIT) )

/* Clear a Certain bit in any Register */
#define CLEAR_BIT(REG,BIT) (REG &= (~ (1<<BIT) ) )

/* Toggle a Certain bit in any Register */
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT) )

/* Rotate right the Register value with specific number of Rotate */
#define ROTATE_RIGHT(REG,NUM)  ( REG = (REG>>NUM) | (REG<<( (sizeof(REG)*8) - NUM)) )

/* Rotate Left the Register value with specific number of Rotate */
#define ROTATE_LEFT(REG,NUM)  ( REG = (REG<<>NUM) | (REG>>( (sizeof(REG)*8) - NUM)) )

/* Rotate Half the Register value with the another Half of Register */
#define ROTATE_HALF(REG)  ( REG = ( (REG>>(sizeof(REG)*4)) | (REG<<(sizeof(REG)*4)) ) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif /* COMMON_MACROS_H_ */
