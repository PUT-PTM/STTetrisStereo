#include "tm_stm32f4_rng.h"
//#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"

#include "misc.h"
#include "stm32f4xx_tim.h"
#include <stdbool.h>
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_pcd8544.h"

#include <alfabet.h>

int i = 0;
extern bool screen[84][48];
extern int current[2][4];
extern int shape;
bool right = false, left = false, down = false, turn = false;
int score = 0;
bool spawn = true;
extern bool collision;
extern bool gameOver;

void MoveScreenDownFrom(int number) {
	for (int i = number; i >= 0; i--) {
		for (int j = 1; j <= 9; j++) {
			if (screen[i * 5 + 8][j * 5 + 1]) {
				ClearChunk(i * 5 + 8, j * 5 + 1);
				DrawChunk(i * 5 + 8 + 5, j * 5 + 1);

			}
		}
	}

}

void CheckHorizontal() {
	int counter = 0;

	for (int i = 0; i <= 14; i++) {
		for (int j = 1; j <= 9; j++) {
			if (screen[i * 5 + 8][j * 5 + 1])
				counter++;
		}

		if (counter == 9) {
			ClearRow(i);
			MoveScreenDownFrom(i);
			score++;

		}
		counter = 0;

	}
	DrawTetrisBorder();

}

void ClearRow(int number) {
	for (int j = 1; j <= 9; j++)
		ClearChunk(number * 5 + 8, j * 5 + 1);

}

void ButtonNoticer() {
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {
		GPIO_SetBits(GPIOD, GPIO_Pin_12); //instrukcja do wykonania kiedy wcisniety

		right = true;
		TIM_Cmd(TIM2, ENABLE);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0) {

		left = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0) {

		down = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0) {

		turn = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}

}

void TIM3_IRQHandler(void) {

	if (spawn == true) {
		shape = TM_RNG_Get() % 30;
		while(shape>19)
		{
				shape = shape/2;

		}
		if(shape<0)
			shape = 0;
		//shape = 2;
		SpawnBlock(18, 26);

		spawn = false;
	}

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		MoveDown(current[0][0], current[1][0], shape);

		DrawTetrisBorder();
		DrawScreen();

		if (collision) {

			screen[current[0][0]][current[1][0]] = true;
			screen[current[0][1]][current[1][1]] = true;
			screen[current[0][2]][current[1][2]] = true;
			screen[current[0][3]][current[1][3]] = true;
			collision = false;

			CheckHorizontal();
			DrawScreen();

			spawn = true;
		}

		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {

		//kod np. zapal diode

		if (right) {
			MoveRight(current[0][0], current[1][0], shape);
			DrawScreen();
			right = false;
			//collision = false;
		}

		if (left) {
			MoveLeft(current[0][0], current[1][0], shape);
			DrawScreen();
			left = false;
			//collision = false;
		}
		if (down) {
			MoveDown(current[0][0], current[1][0], shape);
			DrawScreen();
			down = false;
		}
		if (turn) {
			Turn();
			DrawScreen();
			turn = false;
		}

		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(void) {
//--------------------

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
			| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//--------------------------------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 8999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	//debouncer------------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
	TIM_TimeBaseStructureD1.TIM_Period = 8399;
	TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
	TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructureD1);

	TIM_Cmd(TIM2, DISABLE);

	NVIC_InitTypeDef NVIC_InitStructureD2;
	NVIC_InitStructureD2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructureD2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructureD2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructureD2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructureD2);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	//-----------------
	//random

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructureD1.TIM_Period = 8399;
	TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
	TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructureD1);

	TIM_Cmd(TIM4, ENABLE);
//-------------
	SystemInit();
	PCD8544_Init(0x38);
	DrawTetrisBorder(); //border
	TM_RNG_Init();

	//for (int i = 1; i < 9; i++) {
	//	DrawChunk(78, i * 5 + 1);
	//	DrawChunk(68, i * 5 + 1);
	//}

	DrawScreen();
	while (1) {

		if (!gameOver) {
			ButtonNoticer();
	}

	}
}

