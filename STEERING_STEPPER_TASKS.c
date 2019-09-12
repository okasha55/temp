#include "STEERING_STEPPER_TASKS.h"

/*****************************************************************
 *                    Global Variables
 *****************************************************************/

// making two global variables for current and desired angle and initialize them with STEERING_ORIGIN_ANGLE(180).
// float f_steering_desired_angle = STEERING_ORIGIN_ANGLE ;
// float f_steering_current_angle = STEERING_ORIGIN_ANGLE ;

 // variable for steering direction RIGHT or LEFT.
 // uint8_t ui8_steering_direction ;

 // variable ( TCB structure pointer ) to handle of vTask_Rotate_Steering_Stepper.
 // TaskHandle_t rotate_steering_stepper_task_handle ;


extern QueueHandle_t Queue_steering;

typedef struct {
    QueueHandle_t  Queue_steps_desired;
    uint32_t driver_port_clock;
    uint32_t driver_port_base;
    uint8_t driver_pulse_pin;
    uint8_t driver_direction_pin;
    uint8_t driver_enable_pin;
} stepper_params;




/*
 *
 * driver port clock
 * driver port base
 * driver pulse pin
 * driver direction pin
 * driver enable pin
 * Queue handler
 *
 */




 /********************************************************************
  *                        Public Functions
  ********************************************************************/
 void vInit_Stepper_Driver(uint32_t driver_port_clock,
 uint32_t driver_port_base,
 uint8_t driver_pulse_pin,
 uint8_t driver_direction_pin,
 uint8_t driver_enable_pin)
 {
     // Enable the clock to GPIO portA that is used for the steering stepper driver.
     SysCtlPeripheralEnable(driver_port_clock);
     // Check if the peripheral access is enabled.
     while( !SysCtlPeripheralReady(driver_port_clock) ) ;

     // Enable the GPIO pin for steering stepper driver pulse.
     // --> Set the direction as output, and enable the GPIO pin for digital function.
     GPIOPinTypeGPIOOutput(driver_port_base, driver_pulse_pin) ;

     // Enable the GPIO pin for steering stepper driver direction.
     // --> Set the direction as output, and enable the GPIO pin for digital function.
     GPIOPinTypeGPIOOutput(driver_port_base, driver_direction_pin) ;

     // Enable the GPIO pin for steering stepper driver enable.
     // --> Set the direction as output, and enable the GPIO pin for digital function.
     GPIOPinTypeGPIOOutput(driver_port_base, driver_enable_pin) ;

     // Initialize Enable pin by HIGH to enable rotating steering manually.
     GPIOPinWrite(driver_port_base, driver_enable_pin, driver_enable_pin) ;
 }


 void vInit_Steppers_Tasks()
 {
     // creating the steering stepper controlling task.

     static stepper_params steering_structure;
     //static stepper_params throtle_structure;
     //static stepper_params steering_structure;

     steering_structure.Queue_steps_desired=Queue_steering;
     steering_structure.driver_port_clock=SYSCTL_PERIPH_GPIOA;
     steering_structure.driver_port_base=GPIO_PORTA_BASE;
     steering_structure.driver_direction_pin=GPIO_PIN_3;
     steering_structure.driver_enable_pin=GPIO_PIN_4;
     steering_structure.driver_pulse_pin=GPIO_PIN_2;



     xTaskCreate( vTask_Stepper ,                          // name of the task ( its address ).
                  "steering_task" ,                       // A descriptive name for the task.
                  STEPPER_vTASK_STACK_DEPTH ,                  // size of the stack.
                  &steering_structure ,                                                // task parameter.
                  STEPPER_vTASK_PRIO ,                       // task priority.
                  NULL ) ;            // handle of the task.

    /* xTaskCreate( vTask_Stepper ,                          // name of the task ( its address ).
                  "throttle_task" ,                       // A descriptive name for the task.
                  ROTATE_STEPPER_vTASK_STACK_DEPTH ,                  // size of the stack.
                  &throtle_structure ,                                                // task parameter.
                  STEPPER_vTASK_PRIO ,                       // task priority.
                  NULL ) ;            // handle of the task.

     xTaskCreate( vTask_Stepper ,                          // name of the task ( its address ).
                  "brakes_task" ,                       // A descriptive name for the task.
                  STEPPER_vTASK_STACK_DEPTH ,                  // size of the stack.
                  &brakes_structure,                                                // task parameter.
                  STEPPER_vTASK_PRIO ,                       // task priority.
                  NULL ) ;            // handle of the task.
                  */
 }


 void vTask_Stepper(void * para)
 {

     /*
      *
      * driver port clock
      * driver port base
      * driver pulse pin
      * driver direction pin
      * driver enable pin
      * Queue handler
      *
      */

      uint32_t driver_port_clock =((stepper_params *)para)->driver_port_clock;
      uint32_t driver_port_base=((stepper_params *)para)->driver_port_base;
      uint8_t driver_pulse_pin=((stepper_params *)para)->driver_pulse_pin;
      uint8_t driver_direction_pin=((stepper_params *)para)->driver_direction_pin;
      uint8_t driver_enable_pin=((stepper_params *)para)->driver_enable_pin;


     void vInit_Sterring_Stepper_Driver(driver_port_clock,
                                        driver_port_base,
                                        driver_pulse_pin,
                                        driver_direction_pin,
                                        driver_enable_pin);

     QueueHandle_t Queue_steps_desired =((stepper_params *)para)->Queue_steps_desired;

     uint16_t steps_current = 100;
     uint16_t  * steps_desired;
     while(1)
     {
         // Check if the Desired Angle greater than Current Angle by a step (1.8 degree) or more.
         // If this is true , make a step in right direction.

        //qUEUE BLOCKING
         xQueueReceive(                 Queue_steps_desired,
                                        steps_desired,
                                        portMAX_DELAY);
        while ((*steps_desired) != steps_current){
            //QUEUE nonBLOCKING
            xQueueReceive(                 Queue_steps_desired,
                                           steps_desired,
                                           0);
         if( (*steps_desired) > steps_current )
         {
                 // set direction to right.
                 //ui8_steering_direction = RIGHT ;
                 // make a high logic (RIGHT) on direction pin.
                 GPIOPinWrite(driver_port_base, driver_direction_pin, driver_direction_pin) ;

                 // making a high pulse on pulse pin to make a step.
                 // making pulse start by making a rising edge.
                 GPIOPinWrite(driver_port_base, driver_pulse_pin, driver_pulse_pin) ;
                 // delay to recognize the high pulse.
                 vTaskDelay(100);
                 // end of pulse by making a falling edge.
                 GPIOPinWrite(driver_port_base, driver_pulse_pin, 0x0) ;
                 // delay before another pulse.
                 vTaskDelay(100);

                 // set current angle to the new angle by adding a step.
                 steps_current++ ;
         }

         // else if the current Angle greater than desired Angle by a step ( 1.8 degree) or more ,
         // make a step in left direction.
         else if( (*steps_desired) < steps_current )
         {
                 // set direction to left.
                 //ui8_steering_direction = LEFT ;
                 // make a low logic (LEFT) on direction pin.
                 GPIOPinWrite(driver_port_base, driver_direction_pin, driver_direction_pin) ;

                 // making a high pulse on pulse pin to make a step.
                 // making pulse start by making a rising edge.
                 GPIOPinWrite(driver_port_base, driver_pulse_pin, driver_pulse_pin) ;
                 // delay to recognize the high pulse.
                 vTaskDelay(100);
                 // end of pulse by making a falling edge.
                 GPIOPinWrite(driver_port_base, driver_pulse_pin, 0x0) ;
                 // delay before another pulse.
                 vTaskDelay(100);

                 // set current angle to the new angle by subtracting a step.
                 steps_current-- ;
         }

        }
     }
 }











































