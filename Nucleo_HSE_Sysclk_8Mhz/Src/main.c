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
	char msg[100];

	HAL_Init();
	UART2_Init();

	/***************************************************************/
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK :%ldHz\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK :%ldHz\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 :%ldHz\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
	/***************************************************************/

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 :%ldHz\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(&osc_init, 0, sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;
	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
		Error_handler();
	}

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
						 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_0) != HAL_OK) {
		Error_handler();
	}

	__HAL_RCC_HSI_DISABLE();

	// redoing systick configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK :%ldHz\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK :%ldHz\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 :%ldHz\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 :%ldHz\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

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
