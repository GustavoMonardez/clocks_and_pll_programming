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
void SystemClock_Config(uint8_t clock_freq);

UART_HandleTypeDef huart2;


int main(void) {
	HAL_Init();
	UART2_Init();

	//SystemClock_Config();

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

void SystemClock_Config(uint8_t clock_freq) {
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(clock_freq) {
		case SYS_CLOCK_FREQ_50_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;
			break;
		case SYS_CLOCK_FREQ_84_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;
			break;
		case SYS_CLOCK_FREQ_120_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;
			break;

		default:
			return;
	}

	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
		Error_handler();
	}
}
