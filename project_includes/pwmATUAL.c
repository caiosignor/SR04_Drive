#include "project_includes/pwm.h"


void pwmInit(void)
{

    // PE4 PE5
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);                  //Configure PWM Clock to match system - 80MHz.


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);         // Enable clock to Port E      ok
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));        //ok
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);         // Enable clock to Port E      ok
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);         // Enable clock to Port E      ok
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));        //ok
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);         // Enable clock to Port E      ok
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

    MAP_GPIOPinConfigure(GPIO_PE4_M0PWM4);                  // Configure the GPIO Pin Mux for PE4
    MAP_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);        // for M0PWM4
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); //Configure PWM Options    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWM_PERIOD);      //PWM_FREQUENCY 20KHz
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWM_PERIOD);      //PWM_FREQUENCY 20KHz
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, PWM_PERIOD / 2); //Set PWM duty-50% (Period /2)
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);                     // Enable the PWM generator
    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
    // Use negative logic
    // PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, true);
    // Turn on output 0


    MAP_GPIOPinConfigure(GPIO_PE5_M0PWM5);                  // Configure the GPIO Pin Mux for PE5
    MAP_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);        // for M0PWM5
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, PWM_PERIOD / 2); //Set PWM duty-50% (Period /2)
    PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);         // Turn on output 1
    PWMDeadBandEnable(PWM0_BASE, PWM_GEN_2, DEAD_TIME, DEAD_TIME ); // Dead band enabled turns PWM into complementary mode




    //SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    //SysCtlPeriphe

    // PF2 PF3
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);         // Enable clock to Port F      ok

    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); //Configure PWM Options

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, PWM_PERIOD);      //PWM_FREQUENCY 20KHz

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 3000); //Set PWM duty-50% (Period /2)

    MAP_GPIOPinConfigure(GPIO_PF2_M1PWM6);                  // Configure the GPIO Pin Mux for PF2
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);        // for M1PWM6

    PWMGenEnable(PWM1_BASE, PWM_GEN_3);                     // Enable the PWM generator
    // Use negative logic
    // Turn on output 0
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);




    MAP_GPIOPinConfigure(GPIO_PF3_M1PWM7);                  // Configure the GPIO Pin Mux for PF3,,,,,,
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);        // for M0PWM1
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 3000); //Set PWM duty-50% (Period /2)
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);         // Turn on output 1
    PWMDeadBandEnable(PWM1_BASE, PWM_GEN_3, DEAD_TIME, DEAD_TIME ); // Dead band enabled turns PWM into complementary mode





}
