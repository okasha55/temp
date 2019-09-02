//******************************************************//
//                                                      //
// Empty template for TM4C123GXL Projects using FreeRTOS//
//                                                      //
//******************************************************//

//******************************************************//
//                                                      //
// SHELL ECO Autonomous team                            //
//                                                      //
// Electric Control Sub-team                            //
//                                                      //
//******************************************************//



#include "Initializations.h"
#include "Defines.h"



//freeRTOS includes

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>


//CCS Default includes

#include <stdint.h>
#include <stdbool.h>


//TivaWARE minimal includes

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"

#include "inc/hw_uart.h"




#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "driverlib/uart.h"
#include "driverlib/usb.h"



#include "usblib/usblib.h"
#include "usblib/usbcdc.h"
#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdcdc.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"

void BlinkMyLED(void *);

int main(void)
{
    //50Hz
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // activate internal bus clocking for GPIO port F
    while (!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) ; // busy-wait until GPIOF's bus clock is ready

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // PF_1(RED) PF_2(BLUE) PF_3(GREEN) as output

    // doesn't need too much drive strength as the RGB LEDs on the TM4C123 launchpad are switched via N-type transistors
    MAP_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); // off by default

    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);


    // Prototype for xTaskCreate:
        //
        //  BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
        //                          const char * const pcName,
        //                          uint16_t usStackDepth,
        //                          void *pvParameters,
        //                          UBaseType_t uxPriority,
        //                          TaskHandle_t *pvCreatedTask);
    if (pdTRUE != xTaskCreate(BlinkMyLED, "Blinker", 32, NULL, 4, NULL)) { // (void *)1 is our pvParameters for our task func specifying PF_1
           while (1) ; // error creating task, out of memory?
    }

    vTaskStartScheduler();  // Start FreeRTOS!

    // Should never get here since the RTOS should never "exit".
    while(1) ;
    return 0;


}



void BlinkMyLED(void *pvParameters) {
                                                        /* While pvParameters is technically a pointer, a pointer is nothing
                                                         * more than an unsigned integer of size equal to the architecture's
                                                         * memory address bus width, which is 32-bits in ARM.  We're abusing
                                                         * the parameter then to hold a simple integer value.  Could also have
                                                         * used this as a pointer to a memory location holding the value, but
                                                         * our method uses less memory.
                                                         */
    uint8_t ui8whichBit = 0;

    while (1) {

        MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, ui8whichBit);
        ui8whichBit += 2;
        ui8whichBit %= 15;

        vTaskDelay(1000 / portTICK_RATE_MS);  // Suspend this task (so others may run) for 1s or as close as we can get with the current RTOS tick setting.
    }
    // No way to kill this blinky task unless another task has an xTaskHandle reference to it and can use vTaskDelete() to purge it.
}
