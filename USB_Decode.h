/*
 * USB_Decode.h
 *
 *  Created on: ???/???/????
 *      Author: Tefa
 */

#ifndef USB_DECODE_H_
#define USB_DECODE_H_

//freeRTOS includes

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <queue.h>

/****************************************************
 *                Global Variables
 ****************************************************/


/******************************************************
 *                Static Configuration
 ******************************************************/


/******************************************************
 *                Dynamic Configuration
 ******************************************************/


/****************************************************
 *                     Functions
 ****************************************************/

void vUSB_Data_Decoding (char USB_Received_Data ) ;

#endif /* USB_DECODE_H_ */
