/*
 * USB_Decode.c
 *
 *  Created on: ???/???/????
 *      Author: Tefa
 */

#include "USB_Decode.h"
#include <stdint.h>
/****************************************************
 *                Defines
 ****************************************************/

#define Numbers_Ascii_Base 0x30
#define Numbers_Ascii_Offset 9
#define STEERING_STEP 1.8
#define THROTLE_STEP 1.8
#define BRAKES_STEP 1.8


/****************************************************
 *                Global Variables
 ****************************************************/
extern QueueHandle_t Queue_steering;

/****************************************************
 *                Private Variables
 ****************************************************/


/****************************************************
 *                Private functions
 *****************************************************/

/*
 * Usage : For calculation of desired.
 *
 * Structure : moving old angle decimal point to add the new number
 *             converting the received number from ASCII into Decimal
 *             getting new angle by addition of last time angle and the new number
 *
 * Parameters :
 *             Received number
 *             last time  angle
 *
 * Return :     new angle
 *
 */

static unsigned long  uint32Angle_Decoding (unsigned long USB_Received_Angle , unsigned long New_Angle )
{
    New_Angle = New_Angle * 10 ;
    USB_Received_Angle = USB_Received_Angle - Numbers_Ascii_Base ; /* convert number from ASCII to Decimal */
    New_Angle = New_Angle + USB_Received_Angle ;
    return New_Angle ;
}




/****************************************************
 *                Public functions
 *****************************************************/


/*
 * Usage : For calculation of desired angle and send it to its required motor
 *
 * Structure : has two states :
 *            (1) Choose which motor we will assign the new angle into it or unexpected received data
 *            we will make an error action to handle it and also canceling last calculation to make sure it would not
 *            affect next angle.
 *            (2) calculation of Angle .
 * Parameters :
 *             Received character
 *
 * Return :     Void
 *
 */
void vUSB_Data_Decoding (char USB_Received_Data )
{

    static unsigned long uint32_Decoding_Angle =0; /* Getting Final Angle in here */
    uint16_t uint16_STEPS; // calculated steps
    if(((USB_Received_Data) > (Numbers_Ascii_Base + Numbers_Ascii_Offset)) || ((USB_Received_Data) < (Numbers_Ascii_Base)))
    {
        /*  which motor we will modify its current angle */
        switch (USB_Received_Data){
        /* X for steering motor */
        case 'x' :
        case 'X' :
            //uint32_Steering_Angle = uint32_Decoding_Angle ;
            uint16_STEPS = (int)(((float)uint32_Decoding_Angle)/STEERING_STEP);
            //Queue steering
            xQueueOverwrite(Queue_steering,
                            uint16_STEPS
                            );

            uint32_Decoding_Angle = 0 ;

            break;
        /* Y for Throttle motor */
        case 'y' :
        case 'Y' :
            //uint32_Throttle_Angle = uint32_Decoding_Angle ;
            uint16_STEPS = (int)(((float)uint32_Decoding_Angle)/THROTLE_STEP);
            // queue throtle

            uint32_Decoding_Angle = 0 ;
            break ;
        /* Z for brakes motor */
        case 'z' :
        case 'Z' :
            //uint32_Brakes_Angle = uint32_Decoding_Angle ;
            uint16_STEPS = (int)(((float)uint32_Decoding_Angle)/BRAKES_STEP);
            //  queue brakes
            uint32_Decoding_Angle = 0 ;
            break ;
        /* unexpected Received data Case */
        default :
            uint32_Decoding_Angle = 0 ;
            /* Any Error Action */
        }
    }
    else
    {
        /* calculating desired angle */
        uint32_Decoding_Angle = uint32Angle_Decoding ( USB_Received_Data , uint32_Decoding_Angle ) ;
    }

    return ;
}
