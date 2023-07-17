#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
/*
 * myiic.c
 *
 *  Created on: 2023年7月15日
 *      Author: 71800
 */
void Init_I2C()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlDelay(2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlDelay(2);
    //引脚设置
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    //外设使能
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    //配置I2C
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true);
}



