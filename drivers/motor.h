/*
 * motor.h
 *
 *  Created on: 2023Äê7ÔÂ15ÈÕ
 *      Author: 71800
 */

#ifndef DRIVERS_MOTOR_H_
#define DRIVERS_MOTOR_H_





void GPIO_PWM_DIR_ST_Init(void);
void PWM_Init(void);
void Set_PWM(int vel);
void PWM_Config(int vel);
void Turn_off(void);
void Turn_on(void);


#endif /* DRIVERS_MOTOR_H_ */
