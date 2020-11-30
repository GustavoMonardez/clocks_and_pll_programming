/*
 * main.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Gustavo
 */


#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>

#define FALSE 	0
#define TRUE 	1

void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;


int main(void) {
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	HAL_Init();
	UART2_Init();
	// TODO: this project is configured for discovery board and the
	// settings are meant for nucleo board. Consider switching boards.
	memset(&osc_init, 0, sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;
	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
		Error_handler();
	}

	while(1);

	return 0;
}

// High level peripheral initialization
void UART2_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	//huart2.Init.OverSampling = UART_OVERSAMPLING_8; not configured
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_handler();
	}
}

void Error_handler(void) {
	while(1);
}
