/*
 * brush.h
 *
 *  Created on: Sep 23, 2019
 *      Author: colson
 */

#ifndef BRUSH_H_
#define BRUSH_H_

#include "main.h"

typedef enum{
	OFF = 0,
	ON = 1,
	TOGGLE = 2,
}typedefEnum;

void set_uv_led(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(LED_UV_GPIO_Port, LED_UV_Pin, GPIO_PIN_RESET);
		break;
	}
	case ON:
	{
		HAL_GPIO_WritePin(LED_UV_GPIO_Port, LED_UV_Pin, GPIO_PIN_SET);
		break;
	}
	case TOGGLE:
	{}}
}
void set_uv_boost(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(BOOST_EN_UV_GPIO_Port, BOOST_EN_UV_Pin, GPIO_PIN_RESET);
		break;
	}
	case ON:
	{
		HAL_GPIO_WritePin(BOOST_EN_UV_GPIO_Port, BOOST_EN_UV_Pin, GPIO_PIN_SET);
		break;
	}
	case TOGGLE:
	{}}
}
void set_neopixel_led(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(LED_NEOPIXEL_GPIO_Port, LED_NEOPIXEL_Pin, GPIO_PIN_RESET);
		break;
	}
	case ON:
	{
		HAL_GPIO_WritePin(LED_NEOPIXEL_GPIO_Port, LED_NEOPIXEL_Pin, GPIO_PIN_SET);
		break;
	}
	case TOGGLE:
	{}}
}
void set_neopixel_boost(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(BOOST_EN_NEOPIXEL_GPIO_Port, BOOST_EN_NEOPIXEL_Pin, GPIO_PIN_RESET);
		break;
	}
	case ON:
	{
		HAL_GPIO_WritePin(BOOST_EN_NEOPIXEL_GPIO_Port, BOOST_EN_NEOPIXEL_Pin, GPIO_PIN_SET);
		break;
	}
	case TOGGLE:
	{}}
}
void set_charging_led(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin, GPIO_PIN_RESET);
		break;
	}
	case ON:
	{
		HAL_GPIO_WritePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin, GPIO_PIN_SET);
		break;
	}
	case TOGGLE:
	{
		HAL_GPIO_TogglePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin);
	}
	}
}

#endif /* BRUSH_H_ */
