/*
 * OLED.h
 *
 *  Created on: 2023Äê7ÔÂ16ÈÕ
 *      Author: 71800
 */

#ifndef DRIVERS_OLED_H_
#define DRIVERS_OLED_H_

#include <stdint.h>

void OLED_I2C_Init();
void I2CSendSingleByte(uint8_t slave_addr, char data);
void I2CSendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]);

#endif /* DRIVERS_OLED_H_ */
