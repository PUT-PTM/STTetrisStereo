#include "tm_stm32f4_rng.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dac.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include <stdbool.h>
#include "defines.h"
#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "tm_stm32f4_pcd8544.h"

#include <alfabet.h>

extern bool screen[84][48];
extern int current[2][4];
extern int shape;
extern bool collision;
extern bool gameOver;
extern int score;
extern const u8 music[102050];

bool right = false, left = false, down = false, turn = false, next = false,
		prev = false, select = false, back = false, func = false, spawn = true,
		end = false, movement = true;

int choice = 0;
int choiceX = 50;

int coll = 0;
int soundPlayer = 0;
int letterSelect = 0;
extern int rank[7][2];
int actualNick;
int a1 = 1, a2 = 2, a3 = 3, a4 = 4;
int letterPos = 35;

void INITSYS() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//--------------------------------------------------

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 8999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

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

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
	TIM_TimeBaseStructureD1.TIM_Period = 8399;
	TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
	TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructureD1);

	NVIC_InitTypeDef NVIC_InitStructureD2;
	NVIC_InitStructureD2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructureD2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructureD2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructureD2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructureD2);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 10000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM5, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);
	PCD8544_Refresh();
}

void TetrisButtons() { //left, right, down, turn
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {
		GPIO_SetBits(GPIOD, GPIO_Pin_12); //instrukcja do wykonania kiedy wcisniety

		right = true;
		TIM_Cmd(TIM2, ENABLE);
	} else {
		//right = false;
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0) {

		left = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	} else {
		//left = false;
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0) {

		down = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	} else {
		//down = false;
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {

		turn = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	} else {
		//turn = false;
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}

}

void MenuButtons() { // select, next, prev, func, back
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {

		select = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0) {

		next = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0) {
		prev = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
		func = true;
		TIM_Cmd(TIM2, ENABLE);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	} else {

		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0) {
	//	back = true;
	//	TIM_Cmd(TIM2, ENABLE);
	//	GPIO_SetBits(GPIOD, GPIO_Pin_15);
	//} else {
//
	//	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	//}

}

void TIM3_IRQHandler(void) { // Tetris Game Main Loop
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		if (spawn) {
			movement = true;

			SpawnBlock();
			spawn = false;
		}

		MoveDown();

		if (collision) {
			coll++;
		} else {
			coll = 0;
		}

		if (coll == 1) {
			movement = false;
		}
		if (coll == 2) {

			collision = false;
			coll = 0;
			CheckHorizontal();

			spawn = true;
		}

		DrawScreen();

		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {

		if (right) {
			MoveRight();
			right = false;

		}

		if (left) {
			MoveLeft();
			left = false;

		}
		if (down) {
			MoveDown();
			down = false;
		}
		if (turn) {
			Turn();
			turn = false;
		}

		if (next) {

			if (choice == 0) {
				ClearPointer(choiceX, 47, 3);
				if (choiceX == 74)
					choiceX = 50;
				else
					choiceX += 12;
				DrawPointer(choiceX, 47, 3);
			} else if (choice == 1) {
				switch (letterSelect) {
				case 0: {
					FillREC(50, letterPos, 58, letterPos - 4, false);

					a1++;
					if (a1 == 27)
						a1 = 1;

					DrawLetter(50, letterPos, 4, a1, true);

					break;
				}
				case 1: {
					FillREC(50, letterPos - 6, 58, letterPos - 10, false);
					a2++;
					if (a2 == 27)
						a2 = 1;

					DrawLetter(50, letterPos - 6, 4, a2, true);
					break;
				}
				case 2: {
					FillREC(50, letterPos - 12, 58, letterPos - 16, false);
					a3++;
					if (a3 == 27)
						a3 = 1;
					DrawLetter(50, letterPos - 12, 4, a3, true);
					break;
				}
				case 3: {
					FillREC(50, letterPos - 18, 58, letterPos - 22, false);
					a4++;
					if (a4 == 27)
						a4 = 1;

					DrawLetter(50, letterPos - 18, 4, a4, true);
					break;
				}
				}

			}
			DrawScreen();
			next = false;

		}
		if (prev) {

			if (choice == 0) {
				ClearPointer(choiceX, 47, 3);
				if (choiceX == 50)
					choiceX = 74;
				else
					choiceX -= 12;

				DrawPointer(choiceX, 47, 3);
			} else if (choice == 1) {
				switch (letterSelect) {
				case 0:
					FillREC(50, letterPos, 58, letterPos - 4, false);
					a1--;
					if (a1 == 0)
						a1 = 26;
					DrawLetter(50, letterPos, 4, a1, true);
					break;
				case 1:
					FillREC(50, letterPos - 6, 58, letterPos - 10, false);
					a2--;
					if (a2 == 0)
						a2 = 26;
					DrawLetter(50, letterPos - 6, 4, a2, true);
					break;
				case 2:
					FillREC(50, letterPos - 12, 58, letterPos - 16, false);
					a3--;
					if (a3 == 0)
						a3 = 26;
					DrawLetter(50, letterPos - 12, 4, a3, true);
					break;
				case 3:
					FillREC(50, letterPos - 18, 58, letterPos - 22, false);
					a4--;
					if (a4 == 0)
						a4 = 26;
					DrawLetter(50, letterPos - 18, 4, a4, true);
					break;
				}
			}
			DrawScreen();
			prev = false;
		}

		if (select) {
			if (choice == 0) {

				if (choiceX == 50)
					choice = 1;
				if (choiceX == 62)
					choice = 3;
				if (choiceX == 74)
					choice = 5;
			}

			select = false;

		}

		if (func) {
			if (choice == 1) {

				switch (letterSelect) {

				case 0: {

					ClearChangePointerUP(50, letterPos, 4);
					ClearChangePointerDOWN(50, letterPos, 4);
					letterSelect = 1;

					DrawChangePointerUP(50, letterPos - 6, 4);
					DrawChangePointerDOWN(50, letterPos - 6, 4);
					break;
				}
				case 1: {
					ClearChangePointerUP(50, letterPos - 6, 4);
					ClearChangePointerDOWN(50, letterPos - 6, 4);
					letterSelect = 2;
					DrawChangePointerUP(50, letterPos - 12, 4);
					DrawChangePointerDOWN(50, letterPos - 12, 4);
					break;
				}
				case 2: {
					ClearChangePointerUP(50, letterPos - 12, 4);
					ClearChangePointerDOWN(50, letterPos - 12, 4);
					letterSelect = 3;
					DrawChangePointerUP(50, letterPos - 18, 4);
					DrawChangePointerDOWN(50, letterPos - 18, 4);
					break;
				}
				case 3: {
					ClearChangePointerUP(50, letterPos - 18, 4);
					ClearChangePointerDOWN(50, letterPos - 18, 4);

					letterSelect = 0;

					DrawChangePointerUP(50, letterPos, 4);
					DrawChangePointerDOWN(50, letterPos, 4);
					break;
				}

				}
			}

			DrawScreen();
			func = false;
		}

		DrawScreen();

		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {

		DAC_SetChannel1Data(DAC_Align_12b_R, music[soundPlayer]);
		soundPlayer++;
		if (soundPlayer == 103230)
			soundPlayer = 0;

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

int main(void) {
//--------------------
	INITSYS();
	SystemInit();
	PCD8544_Init(0x38);
	TM_RNG_Init();
	FillRank();

//--------------------
	while (!end) {

		switch (choice) {
		case 0: { //Main Menu

			TetrisMenu();
			DrawPointer(choiceX, 47, 3);
			MenuButtons();
			DrawScreen();

			break;

		}

		case 1: { //Nick Menu

			ClearScreen();
			ClearPointer(choiceX, 47, 3);
			FillREC(0, 0, 83, 47, false);
			WriteSETNICK(20, 45, 4, true);
			DrawLetter(50, letterPos, 4, a1, true);
			DrawLetter(50, letterPos - 6, 4, a2, true);
			DrawLetter(50, letterPos - 12, 4, a3, true);
			DrawLetter(50, letterPos - 18, 4, a4, true);

			letterSelect = 0;

			DrawChangePointerUP(50, letterPos, 4);
			DrawChangePointerDOWN(50, letterPos, 4);
			DrawScreen();
			while (!select) {

				MenuButtons();
			}

			actualNick = a1 * 1000000 + a2 * 10000 + a3 * 100 + a4;
			choice = 2;
			break;

		}
		case 2: { // Game

			ClearScreen();
			DrawTetrisBorder();

			ParseScore(0, 47, 0000);
			WriteFUNCTOSTART(38, 42, 4, true);
			while (!func) {
				MenuButtons();

			}
			ClearScreen();
			DrawTetrisBorder();

			ParseScore(0, 47, 0000);
			gameOver = false;
			movement = true;
			spawn = true;
			soundPlayer = 0;
			TIM_Cmd(TIM3, ENABLE);
			TIM_Cmd(TIM5, ENABLE);

			while (!gameOver) {
				if (movement)
					TetrisButtons();
			}
			spawn = true;
			TIM_Cmd(TIM3, DISABLE);
			TIM_Cmd(TIM5, DISABLE);

			FillREC(35, 38, 59, 11, false);
			WriteGAMEOVER(38, 36, 4, true);
			DrawScreen();

			if(score>0)
			AddToRank(score,actualNick);

			score = 0;
			actualNick=0;
			while (!func) {
				MenuButtons();

			}

			ClearScreen();
			choice = 0;

			break;

		}
		case 3: { // Rank

			ClearScreen();

			DrawRank();

			while (!func) {
				MenuButtons();

			}

			ClearScreen();
			choice = 0;

			break;

		}
		}

	}
}

