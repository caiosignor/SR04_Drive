/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/*  Tivaware Library */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/cfg/global.h>

/* Board Header file */
#include "project_includes/Board.h"
#include "project_includes/sr04.h"
#include "project_includes/pwm.h"

/*  Tivaware Library */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

void heartBeat_TASK(void);

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

uint32_t duty1,
         duty2,
         setPoint,
         kp,
         kd,
         ki,
         distance,
         pwmTest;
#define MAX_PWM 3000
/* ----- There always a led blinking.... -----*/
void heartBeat_TASK(void)
{
   pwmInit();
   sr04_Init();

    distance = 10;
    kp = 150;
    extern uint32_t pulseWidth;
    while (1)
    {
        Task_sleep(100);
        GPIO_toggle(Board_LED0);

//        Semaphore_pend(newDistance_SEM, BIOS_WAIT_FOREVER);

        distance = pulseWidth/80/58;
        if(distance < 20 ){
            //vira pra esquerda
            duty1 = 4000;
            duty2 = 2000;
        }else{
            //anda reto
            duty1 = distance*kp;
            duty2 = duty1;
        }

        if(distance < 10){
            //vai dar ré
            duty1 = 90;
            duty2 = 90;
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, duty1);
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, duty2);
            while(distance < 30){
                Semaphore_pend(newDistance_SEM, BIOS_WAIT_FOREVER);
                distance = pulseWidth/80/58;

            }
        }

        if(duty1 > 4000){
            duty1 = MAX_PWM;
            duty2 = duty1 + 20;
        }
         if(duty1 > MAX_PWM)duty1 = MAX_PWM;
         if(duty2 > MAX_PWM)duty2 = MAX_PWM +20;

        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, duty1);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, duty2);
    }
}

