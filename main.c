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
    //设置系统时钟40mhz
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







//捕获PWM 暂时失败
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
////配置输入捕获引脚
//void PWM_IN_Config(void)
//{
//    //使能定时器与GPIO
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    //使能引脚复用
//    GPIOPinConfigure(GPIO_PB6_T0CCP0);
//    //分配引脚信号
//    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);
//    //设置引脚方向，注意虽然这是输入捕获，但是这是由外界的PWM信号控制，属于硬件控制，要设置为GPIO_DIR_MODE_HW
//    GPIODirModeSet( GPIO_PORTB_BASE,  GPIO_PIN_6, GPIO_DIR_MODE_HW);
//    //设置为推挽上拉输入
//    GPIOPadConfigSet( GPIO_PORTB_BASE,  GPIO_PIN_6, GPIO_STRENGTH_2MA,  GPIO_PIN_TYPE_STD_WPU);
//    //因为是输入捕获，只有在拆分模式下可以用输入捕获，所以将TIMER_CFG_SPLIT_PAIR与A周期计数进行或运算
//    TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_TIME_UP);
//    //设置为上升沿触发
//    TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_POS_EDGE);
//    //注册中断函数
//    TimerIntRegister( TIMER0_BASE,  TIMER_A, PWM_IN_IRQHandler);
//    //设置中断优先级
//    IntPrioritySet( INT_TIMER0A, 0);
//    //使能定时器中断的计时中断
//    TimerIntEnable( TIMER0_BASE,  TIMER_CAPA_EVENT);
//    //使能中断
//    IntEnable( INT_TIMER0A);
//    IntMasterEnable();
//    TimerEnable( TIMER0_BASE,  TIMER_A);
//    /*设置装载值，在边沿计时模式下可以省略，会自己填入默认值。
//    如果设置了预分频值，那么默认装载值就是2^24,如果没有预分频值，那么默认装载值就是2^16。
//    相当于STM32中使用了oc——toggle模式，默认预装载值填写65535*/
//    //TimerLoadSet(TIMER0_BASE, TIMER_A, Capture_LoadSet);
//}
////输入捕获中断
//void PWM_IN_IRQHandler(void)
//{
//    //读取中断状态
//    uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //清除中断标志位
//    TimerIntClear( TIMER0_BASE,  status);
//    //第一次进中断是由于检测到了上升沿，然后将计时值读取，并将边沿检测变为下降沿
//    if(timer_flag==0)
//    {
//        TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_NEG_EDGE);
//        capture_1=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        timer_flag=1;
//    }
//    //第二次进中断是因为检测到了下降沿，然后将计时值读取，这时就已经获得了高电平数，
//    //可以计算出占空比，并将边沿检测变为上升沿
//    else if(timer_flag==1)
//    {
//        TimerControlEvent( TIMER0_BASE,  TIMER_A, TIMER_EVENT_POS_EDGE);
//        capture_2=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        timer_flag=2;
//    }
//    //第三次进中断时因为检测到了上升沿，至此，已经检测到了两个上升沿，也就可以得到周期值
//    else if(timer_flag==2)
//    {
//        timer_flag=0;
//        capture_3=TimerValueGet( TIMER0_BASE,  TIMER_A);
//        /* ____   ___ capture_1相当于检测到第一个上升沿记的数，
//               |  |   |   capture_2相当于检测到第一个下降沿记的数
//              _|  |___|   所以capture_2与capture_1之间即为高电平数
//            capture_3相当于检测到第二个上升沿记的数，所以capture_3与capture_1之间为周期数*/
//        /*  /|   /| 现在要求占空比和频率，因为设置的是定时器A周期性加计数，
//               / |  / | 定时器A记的数先到最大然后再从0开始计数，现在通过求高电平和低电平时间来计算
//              /  | /  | 如果capture_1与capture_2都在第一个计数周期的上升阶段，那1与2的差就是高电平
//             /   |/   | 如果1与2分别落在两个周期的上升阶段，那高电平就要通过0xffff-capture_1+capture_2获得。
//            如果capture_2与capture_3都在第一个计数周期的上升阶段，那2与3的差就是低电平，
//            如果分别落在两个周期上升阶段，低电平就要通过0xffff-capture_2+capture_3来获得*/
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
//        //频率用主频除周期即可得到
//        freq=SysCtlClockGet()/(up_count+down_count);
//        //占空比为高电平占周期的比值即可得到
//        duty=up_count*100/(up_count+down_count);
//    }
//}
//
//void Timer_Wid_Config(void)
//{
//    //使能32/64bit定时器
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//    //使能复用
//    TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC_UP);
//    //设置预装载值，使1s进一次中断
//    TimerLoadSet64( WTIMER0_BASE,  SysCtlClockGet()/1000-1);
//    //使能定时器A超时中断
//    TimerIntEnable( WTIMER0_BASE,  TIMER_TIMA_TIMEOUT);
//    //注册中断函数
//    TimerIntRegister( WTIMER0_BASE,  TIMER_A, TIMER_WID_IRQHandler);
//    //设置优先级
//    IntPrioritySet( INT_WTIMER0A,  1);
//    //设置中断
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
//    //1s打印一次，但是不知道为什么用UARTprintf打印一次就不打印了，需要改进，但是输入捕获那块是没问题的
//    if(time_count==1000)
//    {
//        time_count=0;
//        UARTprintf("duty:%d", duty);
//        UARTprintf("freq:%d", freq);
//    }
//}

////timer定时器示例，分别使用16/32bit的定时器拆分与32/64bit的定时器级联实现同样的功能
//void TIMER_IRQHandler(void);
//void TIMER_WID_IRQHandler(void);
////16/32bit定时器拆分
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
//    //使能定时器TIMER0，16/32bit
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER0);
//    //配置定时器，将定时器拆分，并配置拆分后的定时器A为周期性计数
//    TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC_UP);
//    //设置定时器A装载值，因为要1ms进一次中断，所以1ms=1/1000，
//    //所以重装载值为SysCtlClockGet()/1000-1
//    TimerLoadSet( TIMER0_BASE,  TIMER_A, SysCtlClockGet()/1000-1);
//    //为定时器A注册中断函数
//    TimerIntRegister( TIMER0_BASE,  TIMER_A, TIMER_IRQHandler);
//    //使能time0的定时器A为超时中断
//    TimerIntEnable( TIMER0_BASE,  TIMER_TIMA_TIMEOUT);
//    //设置中断优先级
//    IntPrioritySet( INT_TIMER0A,  0);
//    //使能中断
//    IntEnable( INT_TIMER0A);
//    IntMasterEnable();
//    //使能定时器
//    TimerEnable( TIMER0_BASE,  TIMER_A);
//}
//
//void TIMER_IRQHandler(void)
//{
//    static uint32_t time_count=0;
//    //读取定时器中断状态
//    uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //清除中断标志位
//    TimerIntClear( TIMER0_BASE,  status);
//    //1ms进一次中断
//    time_count++;
//    //进一千次，也就是1s，翻转flag
//    if(time_count==1000)
//    {
//        time_count=0;
//        flag=!flag;
//    }
//}
//
////32/64bit的定时器级联
//void Timer_Wid_Config(void)
//{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//    //设置不拆分并且周期计数
//    TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC_UP);
//    TimerLoadSet64( WTIMER0_BASE,  SysCtlClockGet()/1000-1);
//    //级联的情况下默认都是设置定时器A
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


////PWM示例
//#define Delay_ms(n) SysCtlDelay(n*(SysCtlClockGet()/3000));
//void LED_Config();
//void PWM_Config();
//void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty);
//float d=0.01;
//float duty=0.1;
//_Bool flag=0;
//void main(void)
//{
//    //设置系统时钟40mhz
//    SysCtlClockSet( SYSCTL_SYSDIV_5|SYS CTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    LED_Config();
//    PWM_Config();
//    while(1)
//    {
//        duty+=d;
//        //控制一个颜色的灯先亮后灭之后再换另一个颜色先亮后灭，依次往复
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
//    //因为设置了时钟总线是40MHz，所以在这里分一下频设置为4分频，那么PWM时钟就是10MHz
//    SysCtlPWMClockSet( SYSCTL_PWMDIV_4);
//    //使能GPIOF与PWM1
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
//    SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
//    //为GPIOF_PIN_2与GPIOF_PIN_3分配PWM信号
//    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
//    GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
//    //对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
//    GPIOPinConfigure( GPIO_PF2_M1PWM6);
//    GPIOPinConfigure( GPIO_PF3_M1PWM7);
//    //设置PWM1模块的第三个发生器为向下计数与不同步计数
//    PWMGenConfigure( PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//    //设置PWM1模块的第三个发生器每个计数周期为2000个数，而PWM时钟为10MHz，
//    //那么PWM输出频率就是10^7/2000为5KHz，但是这个数为16位寄存器，不能超过65535
//    PWMGenPeriodSet( PWM1_BASE, PWM_GEN_3, 2000);
//    //设置PWM1模块的第六个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数，
//    //所以可以通过PWMGenPeriodGet得出一个周期内的计数总数再乘0.1然后减1就行
//    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
//    //同理，只不过是设置第七个通道
//    PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.1 - 1);
//    //使能第六个通道
//    PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT, true);
//
//    PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT, true);
//    //使能第三个发生器
//    PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
//}
//
////自定义函数用来设置占空比
//void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty)
//{
//    PWMPulseWidthSet( ui32Base,  ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen)*duty - 1);
//    PWMOutputState( ui32Base,  ui32PWMOutBits, true);
//    PWMGenEnable( ui32Base,  ui32Gen);
//}

////串口示例
////串口中断服务函数
//void UART0_Handler();
//
//int main(void)
//{
//    //配置系统时钟
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    //使能外设
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    //配置PF2引脚，这个引脚连接到了LED
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//    //将PA0 PA1 设置成串口引脚
//    GPIOPinConfigure(GPIO_PA0_U0RX);//RX=GPIO_PIN_0
//    GPIOPinConfigure(GPIO_PA1_U0TX);//TX=GPIO_PIN_1
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
//    //配置串口波特时钟源以及参数
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);//8位数据位 停止位1 无校验位
//    //使能FIFO并设置深度
//    UARTFIFOEnable(UART0_BASE);
//    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
//    //配置串口中断
//    UARTIntRegister(UART0_BASE, UART0_Handler);
//    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);//开启串口接收中断和接收超时中断
//    UARTIntClear(UART0_BASE, UART0_BASE);
//    //启用串口0的中断并开启处理器中断控制器
//    IntEnable(INT_UART0);
//    IntMasterEnable();
//    //使能串口
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
//    //读取中断状态
//    uint32_t status = UARTIntStatus(UART0_BASE, true);
//    //清除中断标志位
//    UARTIntClear(UART0_BASE, status);
//    //检查FIFO中是否有字符，若有，读取出来并发送
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        rxbuf = UARTCharGetNonBlocking(UART0_BASE);
//        UARTCharPutNonBlocking(UART0_BASE, rxbuf);
//    }
//}

//GPIO中断
//void KEY_Handler();
//volatile uint16_t led=1;
//int main()
//{
//    //使能外设时钟
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    //配置GPIO
//
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//    //配置PF4为输入 推挽模式 内部上拉
//    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
//    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//    //配置GPIO外部中断
//
//    //设置引脚中断触发类型：双边缘触发
//    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
//    //注册GPIO外部中断的中断服务程序：KEY_Handler
//    GPIOIntRegister(GPIO_PORTF_BASE, KEY_Handler);
//    //使能指定引脚的中断
//    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
//    //使能一个中断源的中断（中断控制器层面的使能）
//    IntEnable(INT_GPIOF);
//    //使能一个中断源的中断（处理器层面的使能）
//    IntMasterEnable();
//    //清除指定中断源的标志位
//    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
//    //设置中断优先级：0xE0到0x00
//    IntPrioritySet(INT_GPIOF, 0xE0);
//    //配置GPIO外部中断
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




//GPIO输入输出
//   int32_t state = 1;
//   //配置系统时钟80mhz
//   SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能外设
//   //配置PF1 PF2 PF3为输出模式
//   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//   //配置PF4为输入 推挽模式 内部上拉
//   GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
//   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//
//   while(1)
//   {
//       //读取GPIO状态 检测按键状态sw1是否按下
//       if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==GPIO_PIN_4))
//       {
//           SysCtlDelay(SysCtlClockGet()*0.01/3);//延时消抖
//           if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==GPIO_PIN_4))
//               state = state*2;
//           if(state>8)
//               state = 2;
//       }
//       switch(state)
//       {
//          //切换灯的颜色
//          case 2: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);break;
//          case 4: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);break;
//          case 6: GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);break;
//          default: break;
//       }
//   }

