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

#include "drivers/motor.h"
#include "drivers/SSD1306.h"
#include "drivers/OLED.h"
/**
 * main.c
 */

#define Delay_ms(n) SysCtlDelay(n*(SysCtlClockGet()/3000));


void main(void)
{
    //����ϵͳʱ��40mhz
    SysCtlClockSet( SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    OLED_I2C_Init();
    InitializeDisplay();
    clear_display();
    int i, j ,n;
    for(i=0; i<128;i++)
    {
        for(j=0; j<32;j++)
        {
            printBigNumber('2', i, j);
            for(n=0; n < 1000000; n++);
        }
    }
    while(1)
    {}
}







//����PWM ��ʱʧ��
//void PWM_IN_IRQHandler(void);
//void TIMER_WID_IRQHandler(void);
//
//void USART_Config(void);
//void PWM_OUT_Config(void);
//void PWM_IN_Config(void);
//void Timer_Wid_Config(void);
//
//_Bool flag=0;
//uint32_t zhouqi=0;
//uint32_t freq=0;
//_Bool uart_flag=0;
//_Bool led_flag=0;
//uint32_t capture_1=0,capture_2=0,capture_3=0;
//uint32_t timer_flag=0;
//uint32_t duty=0;
//uint32_t up_count=0,down_count=0;
//
//void main(void)
//{
//    SysCtlClockSet( SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    PWM_OUT_Config();
//    PWM_IN_Config();
//    USART_Config();
//    Timer_Wid_Config();
//    while(1)
//    {
//
//    }
//}
//
//void USART_Config(void)
//{
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0);
//    GPIOPinConfigure( GPIO_PA0_U0RX);
//    GPIOPinConfigure( GPIO_PA1_U0TX);
//    GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_0);
//    GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_1);
//    UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
//    UARTStdioConfig(0, 115200, 16000000);
//}
//
//void PWM_OUT_Config(void)
//{
//    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
//    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
//    GPIOPinConfigure( GPIO_PF2_M1PWM6);
//    PWMGenConfigure( PWM1_BASE,  PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//    PWMGenPeriodSet( PWM1_BASE,  PWM_GEN_3, 2000);
//    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.5 - 1);
//    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);
//    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
//}
////�������벶������
//void PWM_IN_Config(void)
//{
//    //ʹ�ܶ�ʱ����GPIO
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    //ʹ�����Ÿ���
//    GPIOPinConfigure(GPIO_PB6_T0CCP0);
//    //���������ź�
//    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);
//    //�������ŷ���ע����Ȼ�������벶�񣬵�������������PWM�źſ��ƣ�����Ӳ�����ƣ�Ҫ����ΪGPIO_DIR_MODE_HW
//    GPIODirModeSet( GPIO_PORTB_BASE,  GPIO_PIN_6, GPIO_DIR_MODE_HW);
//    //����Ϊ������������
//    GPIOPadConfigSet( GPIO_PORTB_BASE,  GPIO_PIN_6, GPIO_STRENGTH_2MA,  GPIO_PIN_TYPE_STD_WPU);
//    //��Ϊ�����벶��ֻ���ڲ��ģʽ�¿��������벶�����Խ�TIMER_CFG_SPLIT_PAIR��A���ڼ������л�����
//    TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_TIME_UP);
//    //����Ϊ�����ش���
//    TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_POS_EDGE);
//    //ע���жϺ���
//    TimerIntRegister( TIMER0_BASE,  TIMER_A, PWM_IN_IRQHandler);
//    //�����ж����ȼ�
//    IntPrioritySet( INT_TIMER0A, 0);
//    //ʹ�ܶ�ʱ���жϵļ�ʱ�ж�
//    TimerIntEnable( TIMER0_BASE,  TIMER_CAPA_EVENT);
//    //ʹ���ж�
//    IntEnable( INT_TIMER0A);
//    IntMasterEnable();
//    TimerEnable( TIMER0_BASE,  TIMER_A);
//    /*����װ��ֵ���ڱ��ؼ�ʱģʽ�¿���ʡ�ԣ����Լ�����Ĭ��ֵ��
//    ���������Ԥ��Ƶֵ����ôĬ��װ��ֵ����2^24,���û��Ԥ��Ƶֵ����ôĬ��װ��ֵ����2^16��
//    �൱��STM32��ʹ����oc����toggleģʽ��Ĭ��Ԥװ��ֵ��д65535*/
//    //TimerLoadSet(TIMER0_BASE, TIMER_A, Capture_LoadSet);
//}
////���벶���ж�
//void PWM_IN_IRQHandler(void)
//{
//    //��ȡ�ж�״̬
//    uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //����жϱ�־λ
//    TimerIntClear( TIMER0_BASE,  status);
//    //��һ�ν��ж������ڼ�⵽�������أ�Ȼ�󽫼�ʱֵ��ȡ���������ؼ���Ϊ�½���
//    if(timer_flag==0)
//    {
//        TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_NEG_EDGE);
//        capture_1=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        timer_flag=1;
//    }
//    //�ڶ��ν��ж�����Ϊ��⵽���½��أ�Ȼ�󽫼�ʱֵ��ȡ����ʱ���Ѿ�����˸ߵ�ƽ����
//    //���Լ����ռ�ձȣ��������ؼ���Ϊ������
//    else if(timer_flag==1)
//    {
//        TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_POS_EDGE);
//        capture_2=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        timer_flag=2;
//    }
//    //�����ν��ж�ʱ��Ϊ��⵽�������أ����ˣ��Ѿ���⵽�����������أ�Ҳ�Ϳ��Եõ�����ֵ
//    else if(timer_flag==2)
//    {
//        timer_flag=0;
//        capture_3=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        /* ____   ___ capture_1�൱�ڼ�⵽��һ�������ؼǵ�����
//               |  |   |   capture_2�൱�ڼ�⵽��һ���½��ؼǵ���
//              _|  |___|   ����capture_2��capture_1֮�伴Ϊ�ߵ�ƽ��
//            capture_3�൱�ڼ�⵽�ڶ��������ؼǵ���������capture_3��capture_1֮��Ϊ������*/
//        /*  /|   /| ����Ҫ��ռ�ձȺ�Ƶ�ʣ���Ϊ���õ��Ƕ�ʱ��A�����ԼӼ�����
//               / |  / | ��ʱ��A�ǵ����ȵ����Ȼ���ٴ�0��ʼ����������ͨ����ߵ�ƽ�͵͵�ƽʱ��������
//              /  | /  | ���capture_1��capture_2���ڵ�һ���������ڵ������׶Σ���1��2�Ĳ���Ǹߵ�ƽ
//             /   |/   | ���1��2�ֱ������������ڵ������׶Σ��Ǹߵ�ƽ��Ҫͨ��0xffff-capture_1+capture_2��á�
//            ���capture_2��capture_3���ڵ�һ���������ڵ������׶Σ���2��3�Ĳ���ǵ͵�ƽ��
//            ����ֱ������������������׶Σ��͵�ƽ��Ҫͨ��0xffff-capture_2+capture_3�����*/
//        if(capture_2>capture_1)
//        {
//            up_count=capture_2-capture_1;
//        }
//        else
//        {
//            up_count=0xffff-capture_1+capture_2;
//        }
//        if(capture_3>capture_2)
//        {
//            down_count=capture_3-capture_2;
//        }
//        else
//        {
//            down_count=0xffff-capture_2+capture_3;
//        }
//        //Ƶ������Ƶ�����ڼ��ɵõ�
//        freq=SysCtlClockGet()/(up_count+down_count);
//        //ռ�ձ�Ϊ�ߵ�ƽռ���ڵı�ֵ���ɵõ�
//        duty=up_count*100/(up_count+down_count);
//    }
//}
//
//void Timer_Wid_Config(void)
//{
//    //ʹ��32/64bit��ʱ��
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//    //ʹ�ܸ���
//    TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC_UP);
//    //����Ԥװ��ֵ��ʹ1s��һ���ж�
//    TimerLoadSet64( WTIMER0_BASE,  SysCtlClockGet()/1000-1);
//    //ʹ�ܶ�ʱ��A��ʱ�ж�
//    TimerIntEnable( WTIMER0_BASE,  TIMER_TIMA_TIMEOUT);
//    //ע���жϺ���
//    TimerIntRegister( WTIMER0_BASE,  TIMER_A, TIMER_WID_IRQHandler);
//    //�������ȼ�
//    IntPrioritySet( INT_WTIMER0A,  1);
//    //�����ж�
//    IntEnable( INT_WTIMER0A);
//    IntMasterEnable();
//    TimerEnable( WTIMER0_BASE,  TIMER_A);
//}
//
//void TIMER_WID_IRQHandler(void)
//{
//    static uint32_t time_count=0;
//
//    uint32_t status=TimerIntStatus( WTIMER0_BASE,  true);
//    TimerIntClear( WTIMER0_BASE,  status);
//
//    time_count++;
//    //1s��ӡһ�Σ����ǲ�֪��Ϊʲô��UARTprintf��ӡһ�ξͲ���ӡ�ˣ���Ҫ�Ľ����������벶���ǿ���û�����
//    if(time_count==1000)
//    {
//        time_count=0;
//        UARTprintf("duty:%d", duty);
//        UARTprintf("freq:%d", freq);
//    }
//}

////timer��ʱ��ʾ�����ֱ�ʹ��16/32bit�Ķ�ʱ�������32/64bit�Ķ�ʱ������ʵ��ͬ���Ĺ���
//void TIMER_IRQHandler(void);
//void TIMER_WID_IRQHandler(void);
////16/32bit��ʱ�����
//void Timer_Config(void);
//void Timer_Wid_Config(void);
//void LED_Config(void);
//_Bool flag=0;
//void main(void)
//{
//    SysCtlClockSet( SYSCTL_SYSDIV_4|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN|SYSCTL_USE_PLL);
//    LED_Config();
//    //Timer_Config();
//    Timer_Wid_Config();
//    while(1)
//    {
//        if(flag==0)
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
//        else
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//    }
//}
//
//void LED_Config(void)
//{
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
//    GPIODirModeSet( GPIO_PORTF_BASE,  GPIO_PIN_2, GPIO_DIR_MODE_OUT);
//    GPIOPadConfigSet( GPIO_PORTF_BASE,  GPIO_PIN_2, GPIO_STRENGTH_2MA,  GPIO_PIN_TYPE_STD);
//}
//
//void Timer_Config(void)
//{
//    //ʹ�ܶ�ʱ��TIMER0��16/32bit
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER0);
//    //���ö�ʱ��������ʱ����֣������ò�ֺ�Ķ�ʱ��AΪ�����Լ���
//    TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC_UP);
//    //���ö�ʱ��Aװ��ֵ����ΪҪ1ms��һ���жϣ�����1ms=1/1000��
//    //������װ��ֵΪSysCtlClockGet()/1000-1
//    TimerLoadSet( TIMER0_BASE,  TIMER_A, SysCtlClockGet()/1000-1);
//    //Ϊ��ʱ��Aע���жϺ���
//    TimerIntRegister( TIMER0_BASE,  TIMER_A, TIMER_IRQHandler);
//    //ʹ��time0�Ķ�ʱ��AΪ��ʱ�ж�
//    TimerIntEnable( TIMER0_BASE,  TIMER_TIMA_TIMEOUT);
//    //�����ж����ȼ�
//    IntPrioritySet( INT_TIMER0A,  0);
//    //ʹ���ж�
//    IntEnable( INT_TIMER0A);
//    IntMasterEnable();
//    //ʹ�ܶ�ʱ��
//    TimerEnable( TIMER0_BASE,  TIMER_A);
//}
//
//void TIMER_IRQHandler(void)
//{
//    static uint32_t time_count=0;
//    //��ȡ��ʱ���ж�״̬
//    uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //����жϱ�־λ
//    TimerIntClear( TIMER0_BASE,  status);
//    //1ms��һ���ж�
//    time_count++;
//    //��һǧ�Σ�Ҳ����1s����תflag
//    if(time_count==1000)
//    {
//        time_count=0;
//        flag=!flag;
//    }
//}
//
////32/64bit�Ķ�ʱ������
//void Timer_Wid_Config(void)
//{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//    //���ò���ֲ������ڼ���
//    TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC_UP);
//    TimerLoadSet64( WTIMER0_BASE,  SysCtlClockGet()/1000-1);
//    //�����������Ĭ�϶������ö�ʱ��A
//    TimerIntEnable( WTIMER0_BASE,  TIMER_TIMA_TIMEOUT);
//    TimerIntRegister( WTIMER0_BASE,  TIMER_A,
//                             TIMER_WID_IRQHandler);
//    IntPrioritySet( INT_WTIMER0A,  1);
//    IntEnable( INT_WTIMER0A);
//    IntMasterEnable();
//    TimerEnable( WTIMER0_BASE,  TIMER_A);
//}
//
//void TIMER_WID_IRQHandler(void)
//{
//    static uint32_t time_count=0;
//
//    uint32_t status=TimerIntStatus( WTIMER0_BASE,  true);
//    TimerIntClear( WTIMER0_BASE,  status);
//
//    time_count++;
//    if(time_count==1000)
//    {
//        time_count=0;
//        flag=!flag;
//    }
//}


////PWMʾ��
//#define Delay_ms(n) SysCtlDelay(n*(SysCtlClockGet()/3000));
//void LED_Config();
//void PWM_Config();
//void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty);
//float d=0.01;
//float duty=0.1;
//_Bool flag=0;
//void main(void)
//{
//    //����ϵͳʱ��40mhz
//    SysCtlClockSet( SYSCTL_SYSDIV_5|SYS CTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    LED_Config();
//    PWM_Config();
//    while(1)
//    {
//        duty+=d;
//        //����һ����ɫ�ĵ���������֮���ٻ���һ����ɫ����������������
//        if(duty>0.9)
//            d=-0.01;
//        else if(duty<0.1)
//        {
//            d=0.01;
//            flag=!flag;
//        }
//
//        if(flag==0)
//            PWM_duty( PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, duty);
//        else
//            PWM_duty( PWM1_BASE, PWM_OUT_7, PWM_OUT_7_BIT, PWM_GEN_3, duty);
//        Delay_ms(10);
//    }
//}
//
//void LED_Config(void)
//{
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
//    GPIODirModeSet( GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, GPIO_DIR_MODE_OUT);
//    GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
//}
//
//void PWM_Config(void)
//{
//    //��Ϊ������ʱ��������40MHz�������������һ��Ƶ����Ϊ4��Ƶ����ôPWMʱ�Ӿ���10MHz
//    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
//    //ʹ��GPIOF��PWM1
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
//    //ΪGPIOF_PIN_2��GPIOF_PIN_3����PWM�ź�
//    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
//    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
//    //��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
//    GPIOPinConfigure( GPIO_PF2_M1PWM6);
//    GPIOPinConfigure( GPIO_PF3_M1PWM7);
//    //����PWM1ģ��ĵ�����������Ϊ���¼����벻ͬ������
//    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//    //����PWM1ģ��ĵ�����������ÿ����������Ϊ2000��������PWMʱ��Ϊ10MHz��
//    //��ôPWM���Ƶ�ʾ���10^7/2000Ϊ5KHz�����������Ϊ16λ�Ĵ��������ܳ���65535
//    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, 2000);
//    //����PWM1ģ��ĵ�����ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ����
//    //���Կ���ͨ��PWMGenPeriodGet�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
//    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
//    //ͬ��ֻ���������õ��߸�ͨ��
//    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
//    //ʹ�ܵ�����ͨ��
//    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);
//
//    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
//    //ʹ�ܵ�����������
//    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
//}
//
////�Զ��庯����������ռ�ձ�
//void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty)
//{
//    PWMPulseWidthSet( ui32Base,  ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen)*duty - 1);
//    PWMOutputState( ui32Base,  ui32PWMOutBits, true);
//    PWMGenEnable( ui32Base,  ui32Gen);
//}

////����ʾ��
////�����жϷ�����
//void UART0_Handler();
//
//int main(void)
//{
//    //����ϵͳʱ��
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    //ʹ������
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    //����PF2���ţ�����������ӵ���LED
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//    //��PA0 PA1 ���óɴ�������
//    GPIOPinConfigure(GPIO_PA0_U0RX);//RX=GPIO_PIN_0
//    GPIOPinConfigure(GPIO_PA1_U0TX);//TX=GPIO_PIN_1
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
//    //���ô��ڲ���ʱ��Դ�Լ�����
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);//8λ����λ ֹͣλ1 ��У��λ
//    //ʹ��FIFO���������
//    UARTFIFOEnable(UART0_BASE);
//    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
//    //���ô����ж�
//    UARTIntRegister(UART0_BASE, UART0_Handler);
//    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);//�������ڽ����жϺͽ��ճ�ʱ�ж�
//    UARTIntClear(UART0_BASE, UART0_BASE);
//    //���ô���0���жϲ������������жϿ�����
//    IntEnable(INT_UART0);
//    IntMasterEnable();
//    //ʹ�ܴ���
//    UARTEnable(UART0_BASE);
//
//    while(1)
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
//        SysCtlDelay(SysCtlClockGet()*0.5/3);
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//        SysCtlDelay(SysCtlClockGet()*0.5/3);
//    }
//}
//
//void UART0_Handler()
//{
//    int32_t rxbuf;
//    //��ȡ�ж�״̬
//    uint32_t status = UARTIntStatus(UART0_BASE, true);
//    //����жϱ�־λ
//    UARTIntClear(UART0_BASE, status);
//    //���FIFO���Ƿ����ַ������У���ȡ����������
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        rxbuf = UARTCharGetNonBlocking(UART0_BASE);
//        UARTCharPutNonBlocking(UART0_BASE, rxbuf);
//    }
//}

//GPIO�ж�
//void KEY_Handler();
//volatile uint16_t led=1;
//int main()
//{
//    //ʹ������ʱ��
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    //����GPIO
//
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//    //����PF4Ϊ���� ����ģʽ �ڲ�����
//    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
//    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//    //����GPIO�ⲿ�ж�
//
//    //���������жϴ������ͣ�˫��Ե����
//    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
//    //ע��GPIO�ⲿ�жϵ��жϷ������KEY_Handler
//    GPIOIntRegister(GPIO_PORTF_BASE, KEY_Handler);
//    //ʹ��ָ�����ŵ��ж�
//    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
//    //ʹ��һ���ж�Դ���жϣ��жϿ����������ʹ�ܣ�
//    IntEnable(INT_GPIOF);
//    //ʹ��һ���ж�Դ���жϣ������������ʹ�ܣ�
//    IntMasterEnable();
//    //���ָ���ж�Դ�ı�־λ
//    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
//    //�����ж����ȼ���0xE0��0x00
//    IntPrioritySet(INT_GPIOF, 0xE0);
//    //����GPIO�ⲿ�ж�
//
//    while(1)
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, led);
//    }
//}
//
//void KEY_Handler(void)
//{
//    uint32_t status;
//    //get the masked interrupt status of GPIOF
//    status = GPIOIntStatus(GPIO_PORTF_BASE, true);
//    //clear the aforementioned status
//    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
//
//    if(status==GPIO_PIN_4)//KEY1
//    {
//        if(led<8)
//            led=led*2;
//        else
//            led=2;
//    }
//}




//GPIO�������
//   int32_t state = 1;
//   //����ϵͳʱ��80mhz
//   SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//ʹ������
//   //����PF1 PF2 PF3Ϊ���ģʽ
//   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//   //����PF4Ϊ���� ����ģʽ �ڲ�����
//   GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
//   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//
//   while(1)
//   {
//       //��ȡGPIO״̬ ��ⰴ��״̬sw1�Ƿ���
//       if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==GPIO_PIN_4))
//       {
//           SysCtlDelay(SysCtlClockGet()*0.01/3);//��ʱ����
//           if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==GPIO_PIN_4))
//               state = state*2;
//           if(state>8)
//               state = 2;
//       }
//       switch(state)
//       {
//          //�л��Ƶ���ɫ
//          case 2: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);break;
//          case 4: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);break;
//          case 6: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);break;
//          default: break;
//       }
//   }

