/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdbool.h"
#include "stm32f1xx_it.h"
#include "stdint.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GUI.h"
#include "GUI/game_gui.h"
#include "lcd.h"
#include "GUI/bg.h"
#include "GUI/Menu.h"
#include "Game/Game.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

extern uint16_t savedScreen[CONFIRM_BOX_WIDTH * CONFIRM_BOX_HEIGHT];
extern uint8_t selectedPlayers;

extern uint8_t menuItemCount;
extern uint8_t currentMenuItemIndex;
extern char menuItemNameList[8][32];

extern MenuState menuState;


extern struct Game* game;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern volatile GUI_TIMER_TIME OS_TimeMS;


void handle_map_selection() {
  strcpy(game->map_name, menuItemNameList[currentMenuItemIndex]);
}

void handle_BTN_pressed_InGame() {
    Game_Pause(game);
    if (ShowExitConfirmation() == BTN_K2) {
        Game_End(game);
        menuState = MAIN_MENU;
        MENU_DrawMainMenu();
    }else if (ShowExitConfirmation() == BTN_K1){
        ClearPromptBox();
        Game_Resume(game);
    }
}

void handle_K2_pressed_EndGame() {
    menuState = MAIN_MENU;
    MENU_DrawMainMenu();
}

void handle_K2_pressed_MainMenu() {
    switch (currentMenuItemIndex) {
        case INDEX_SINGLE_PLAYER:
              menuState = IN_GAME;
              MENU_SwitchMenu(menuState);
              Game_Start(game);
              break;
        case INDEX_MULTI_PLAYER:
              menuState = ROOM_MENU;
              MENU_SwitchMenu(menuState);
              break;
        case INDEX_CHOOSE_MAP:
              menuState = MAP_MENU;
              MENU_SwitchMenu(menuState);
              break;
        default:
              break;
    }
}

void handle_K2_pressed_SubMenu() {
    switch (menuState) {
        case MAP_MENU:
              handle_map_selection();
              break;
        case ROOM_MENU:
              break;
        default:
              break;
    }
    menuState = MAIN_MENU;
    MENU_SwitchMenu(menuState);
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */


//handling K1 button
void EXTI0_IRQHandler(void) {
  if (menuState == MAIN_MENU || menuState == MAP_MENU) { 
    MENU_SelectNextItem();
  }

  if (menuState == IN_GAME) {
    handle_BTN_pressed_InGame();
  }

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


//handling K2 button
void EXTI15_10_IRQHandler(void) {

    
switch (menuState) {
    case IN_GAME:
          handle_BTN_pressed_InGame();
          break;
    case END_GAME:
          handle_K2_pressed_EndGame();
          break;
    case MAIN_MENU:
          handle_K2_pressed_MainMenu();
          break;
    default:
          handle_K2_pressed_SubMenu();
          break;
    }

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);


}



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
