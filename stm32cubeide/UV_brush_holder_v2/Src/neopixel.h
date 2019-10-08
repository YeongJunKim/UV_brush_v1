/*
 * neopixel.h
 *
 *  Created on: Oct 8, 2019
 *      Author: colson
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#include "main.h"
#include "string.h"
#define BIT_PERIOD 	10
#define BIT_HIGH	6
#define BIT_LOW		3

uint8_t is_init = 0;
uint16_t led_cnt = 0;

uint8_t led_buf[50 + 32*64];

extern TIM_HandleTypeDef htim2;

void neopixel_init(void)
{
	memset(led_buf, 0, sizeof(led_buf));
	is_init = 1;
}

void neopixel_begin(uint32_t led_cnt)
{
	led_cnt = led_cnt;

	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t *)led_buf, (50 + 32 * led_cnt) * 1);
}
void neopixel_SetColor(uint32_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
	uint8_t r_bit[8];
	uint8_t g_bit[8];
	uint8_t b_bit[8];
	uint8_t w_bit[8];

	uint32_t offset;

	for (int i = 0; i < 8; i ++)
	{
		if(red & (1<<7))
			r_bit[i] = BIT_HIGH;
		else
			r_bit[i] = BIT_LOW;
		red <<= 1;
		if(red & (1<<7))
			g_bit[i] = BIT_HIGH;
		else
			g_bit[i] = BIT_LOW;
		green <<= 1;
		if(red & (1<<7))
			b_bit[i] = BIT_HIGH;
		else
			b_bit[i] = BIT_LOW;
		blue <<= 1;
		if(red & (1<<7))
			w_bit[i] = BIT_HIGH;
		else
			w_bit[i] = BIT_LOW;
		white <<= 1;
	}

	offset = 50;

	memcpy(&led_buf[offset + index*32 + 8 * 0], g_bit, 8*1);
	memcpy(&led_buf[offset + index*32 + 8 * 1], r_bit, 8*1);
	memcpy(&led_buf[offset + index*32 + 8 * 2], b_bit, 8*1);
	memcpy(&led_buf[offset + index*32 + 8 * 3], w_bit, 8*1);
}


#endif /* NEOPIXEL_H_ */
