#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
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

#include "motor.h"
/*
 * motor.c
 *
 *  Created on: 2023年7月15日
 *      Author: 71800
 */

/*
 * 初始化DIR和ST引脚
 * PC4使能为高
 */
void GPIO_PWM_DIR_ST_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//使能外设
    GPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_DIR_MODE_OUT);//设置PC4 PC5 PC6为输出模式
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);//推挽输出
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);//PC4输出高电平
}


/*
 *  motor初始化函数
 *  引脚为：PF2  PF3
 */
void PWM_Init(void)
{
    //因为设置了时钟总线是40MHz，所以在这里分一下频设置为4分频，那么PWM时钟就是10MHz
    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
    //使能GPIOF与PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
    //为GPIOF_PIN_2与GPIOF_PIN_3分配PWM信号
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
    //对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
    GPIOPinConfigure( GPIO_PF2_M1PWM6);
    GPIOPinConfigure( GPIO_PF3_M1PWM7);
    //设置PWM1模块的第三个发生器为向下计数与不同步计数
    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
}

/*
 * 电机速度控制函数
 * 参数：vel 越大 电机速度越慢
 */
void Set_PWM(int vel)
{
    //设置PWM1模块的第三个发生器每个计数周期为2000个数，而PWM时钟为10MHz，
    //那么PWM输出频率就是10^7/2000为5KHz，但是这个数为16位寄存器，不能超过65535
    //          如果vel=2000 →↓
    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, vel);
    //设置PWM1模块的第六个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数，
    //所以可以通过PWMGenPeriodGet得出一个周期内的计数总数再乘0.1然后减1就行
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //同理，只不过是设置第七个通道
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //使能第六个通道
    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);

    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
    //使能第三个发生器
    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
}



void PWM_Config(int vel)
{
    //因为设置了时钟总线是40MHz，所以在这里分一下频设置为4分频，那么PWM时钟就是10MHz
    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
    //使能GPIOF与PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
    //为GPIOF_PIN_2与GPIOF_PIN_3分配PWM信号
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
    //对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
    GPIOPinConfigure( GPIO_PF2_M1PWM6);
    GPIOPinConfigure( GPIO_PF3_M1PWM7);
    //设置PWM1模块的第三个发生器为向下计数与不同步计数
    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    //设置PWM1模块的第三个发生器每个计数周期为2000个数，而PWM时钟为10MHz，
    //那么PWM输出频率就是10^7/2000为5KHz，但是这个数为16位寄存器，不能超过65535
    //          如果vel=2000 →↓
    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, vel);
    //设置PWM1模块的第六个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数，
    //所以可以通过PWMGenPeriodGet得出一个周期内的计数总数再乘0.1然后减1就行
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //同理，只不过是设置第七个通道
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //使能第六个通道
    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);

    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
    //使能第三个发生器
    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
}

/*
 *关闭电机
*/
void Turn_off(void)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);//PC4输出低电平
}

/*
 * 打开电机
*/
void Turn_on(void)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);//PC4输出高电平
}
