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
 *  Created on: 2023��7��15��
 *      Author: 71800
 */

/*
 * ��ʼ��DIR��ST����
 * PC4ʹ��Ϊ��
 */
void GPIO_PWM_DIR_ST_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//ʹ������
    GPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_DIR_MODE_OUT);//����PC4 PC5 PC6Ϊ���ģʽ
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);//�������
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);//PC4����ߵ�ƽ
}


/*
 *  motor��ʼ������
 *  ����Ϊ��PF2  PF3
 */
void PWM_Init(void)
{
    //��Ϊ������ʱ��������40MHz�������������һ��Ƶ����Ϊ4��Ƶ����ôPWMʱ�Ӿ���10MHz
    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
    //ʹ��GPIOF��PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
    //ΪGPIOF_PIN_2��GPIOF_PIN_3����PWM�ź�
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
    //��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
    GPIOPinConfigure( GPIO_PF2_M1PWM6);
    GPIOPinConfigure( GPIO_PF3_M1PWM7);
    //����PWM1ģ��ĵ�����������Ϊ���¼����벻ͬ������
    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
}

/*
 * ����ٶȿ��ƺ���
 * ������vel Խ�� ����ٶ�Խ��
 */
void Set_PWM(int vel)
{
    //����PWM1ģ��ĵ�����������ÿ����������Ϊ2000��������PWMʱ��Ϊ10MHz��
    //��ôPWM���Ƶ�ʾ���10^7/2000Ϊ5KHz�����������Ϊ16λ�Ĵ��������ܳ���65535
    //          ���vel=2000 ����
    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, vel);
    //����PWM1ģ��ĵ�����ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ����
    //���Կ���ͨ��PWMGenPeriodGet�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //ͬ��ֻ���������õ��߸�ͨ��
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //ʹ�ܵ�����ͨ��
    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);

    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
    //ʹ�ܵ�����������
    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
}



void PWM_Config(int vel)
{
    //��Ϊ������ʱ��������40MHz�������������һ��Ƶ����Ϊ4��Ƶ����ôPWMʱ�Ӿ���10MHz
    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
    //ʹ��GPIOF��PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
    //ΪGPIOF_PIN_2��GPIOF_PIN_3����PWM�ź�
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
    //��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
    GPIOPinConfigure( GPIO_PF2_M1PWM6);
    GPIOPinConfigure( GPIO_PF3_M1PWM7);
    //����PWM1ģ��ĵ�����������Ϊ���¼����벻ͬ������
    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    //����PWM1ģ��ĵ�����������ÿ����������Ϊ2000��������PWMʱ��Ϊ10MHz��
    //��ôPWM���Ƶ�ʾ���10^7/2000Ϊ5KHz�����������Ϊ16λ�Ĵ��������ܳ���65535
    //          ���vel=2000 ����
    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, vel);
    //����PWM1ģ��ĵ�����ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ����
    //���Կ���ͨ��PWMGenPeriodGet�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //ͬ��ֻ���������õ��߸�ͨ��
    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
    //ʹ�ܵ�����ͨ��
    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);

    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
    //ʹ�ܵ�����������
    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
}

/*
 *�رյ��
*/
void Turn_off(void)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);//PC4����͵�ƽ
}

/*
 * �򿪵��
*/
void Turn_on(void)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);//PC4����ߵ�ƽ
}
