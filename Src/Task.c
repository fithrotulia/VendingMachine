/*
 * Task.c
 *
 *  Created on: Nov 24, 2019
 *      Author: fithrotul
 */
#include "Task.h"
#include "main.h"

#define LED500 			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET)
#define LED500M 		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET)
#define LED1000			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED1000M 		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#define LEDPROSES		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LEDPROSESM 		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LEDCANCEL		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET)
#define LEDCANCELM 		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET)

enum state {start, koin500, koin1000, kembali500, kembali1000, proses, cancel500, cancel, out, finish} Kondisi;
volatile uint16_t timeout;

unsigned char PB500(void);
unsigned char PB1000(void);
unsigned char PBPROSES(void);
unsigned char PBCANCEL(void);

void Task_Init(void)
{
	timeout=0;
	Kondisi=start;
}
void Task_Run(void)
{
	switch(Kondisi)
	{
	case start:
	{
		LED500M;
		LED1000M;
		LEDPROSESM;
		LEDCANCELM;
		Kondisi=koin500;
		break;
	}
	case koin500:
	{
		if(PB500())
		{
			LED500;
			LED1000M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=koin1000;
		}
		if(PB1000())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=proses;
		}
		break;
	}
	case koin1000:
	{
		if(PB500())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=proses;
		}
		if(PB1000())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=kembali500;
		}
		if(PBPROSES())
		{
			LED500;
			LED1000;
			LEDPROSES;
			LEDCANCEL;
			HAL_Delay(500);
			LED500M;
			LED1000M;
			LEDPROSESM;
			LEDCANCELM;
			HAL_Delay(500);
			LED500;
			LED1000;
			LEDPROSES;
			LEDCANCEL;
			HAL_Delay(500);
			LED500M;
			LED1000M;
			LEDPROSESM;
			LEDCANCELM;
			HAL_Delay(1);
			LED500;
			Kondisi=koin1000;
		}
		if(PBCANCEL())
		{
			Kondisi=cancel500;
		}
		break;
	}
	case kembali500:
	{
		HAL_Delay(500);
		LED500;
		HAL_Delay(500);
		LED500M;
		Kondisi=proses;
		break;
	}
	case kembali1000:
	{
		HAL_Delay(500);
		LED1000M;
		HAL_Delay(500);
		LED1000;
		HAL_Delay(500);
		LED1000M;
		HAL_Delay(500);
		LED1000;
		Kondisi=proses;
		break;
	}
	case proses:
	{
		if(PB500())
		{
			Kondisi=kembali500;
		}
		if(PB1000())
		{
			Kondisi=kembali1000;
		}
		if(PBPROSES())
		{
			LEDPROSES;
			LED500M;
			LED1000M;
			LEDCANCELM;
			HAL_Delay(1000);
			Kondisi=out;
		}
		if(PBCANCEL())
		{
			Kondisi=cancel;
		}
		break;
	}
	case cancel:
	{
		LED500M;
		LED1000;
		LEDPROSESM;
		LEDCANCEL;
		HAL_Delay(2000);
		Kondisi=finish;
		break;
	}
	case cancel500:
	{
		LED500;
		LED1000M;
		LEDPROSESM;
		LEDCANCEL;
		HAL_Delay(2000);
		Kondisi=finish;
		break;
	}
	case out:
	{
		LEDPROSES;
		HAL_Delay(3000);
		LEDPROSESM;
		HAL_Delay(3000);
		LEDPROSES;
		Kondisi=finish;
		break;
	}
	case finish:
	{
		Kondisi=start;
	}
	}
}

unsigned char PB500(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PB1000(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PBPROSES(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PBCANCEL(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
