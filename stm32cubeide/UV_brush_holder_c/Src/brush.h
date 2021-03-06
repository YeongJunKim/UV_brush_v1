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
}typedefEnum;

void set_uv_led(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(LED_UV_GPIO_Port, LED_UV_Pin, GPIO_PIN_RESET);
	}
	case ON:
	{
		HAL_GPIO_WritePin(LED_UV_GPIO_Port, LED_UV_Pin, GPIO_PIN_SET);
	}}
}
void set_boost(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_RESET);
	}
	case ON:
	{
		HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_SET);
	}}
}
void set_charging_led(typedefEnum state)
{
	switch(state){
	case OFF:
	{
		HAL_GPIO_WritePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin, GPIO_PIN_RESET);
	}
	case ON:
	{
		HAL_GPIO_WritePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin, GPIO_PIN_SET);
	}}
}

#endif /* BRUSH_H_ */
