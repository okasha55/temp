#ifndef STEERING_STEPPER_TASKS_H_
#define STEERING_STEPPER_TASKS_H_


/*                      TIVAware libraries                   */
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//freeRTOS includes

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <queue.h>


/*****************************************************************
 *                      Static Configuration
 *****************************************************************/
#define STEERING_ORIGIN_ANGLE 180
#define RIGHT STEERING_DIRECTION_PIN
#define LEFT 0x0
#define STEERING_STEP 1.8
#define STEPPER_vTASK_STACK_DEPTH 64
#define STEPPER_vTASK_PRIO 2



/*****************************************************************
 *           Steering Driver Port&Pins configurations
 *****************************************************************/
 #define STEERING_DRIVER_PORT_CLOCK SYSCTL_PERIPH_GPIOA
 #define STEERING_DRIVER_PORT_BASE GPIO_PORTA_BASE
 #define STEERING_PULSE_PIN GPIO_PIN_2
 #define STEERING_DIRECTION_PIN GPIO_PIN_3
 #define STEERING_ENABLE_MANUAL_PIN GPIO_PIN_4



/*****************************************************************
 *                    TASKS Declaration
 *****************************************************************/
 extern void vInit_Sterring_Stepper_Driver() ;
 extern void vInit_Steppers_Tasks();
 extern void vTask_Stepper( void * para ) ;
 
 
 
 #endif /* STEERING_STEPPER_TASKS_H_ */
 
