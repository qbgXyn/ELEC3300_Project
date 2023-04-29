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
#include "main.h"、
#include "stdbool.h"
#include "stm32f1xx_it.h"
#include "stdint.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GUI.h"
#include "lcd.h"
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
MenuState menuState = MAIN_MENU;
uint8_t currentSubmenuItem = 0;
uint8_t gameInProgres = 0;
extern uint16_t savedScreen[CONFIRM_BOX_WIDTH * CONFIRM_BOX_HEIGHT];
extern uint8_t selectedDifficulty;
extern uint8_t selectedMap;
extern uint8_t selectedPlayers;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern volatile GUI_TIMER_TIME OS_TimeMS;

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


void EXTI0_IRQHandler(void) {
	 if (menuState == IN_GAME) {
	        if (ShowExitConfirmation()) {
	        	// Reload the map
	            GenerateGameMap(selectedDifficulty, selectedMap, selectedPlayers);
	            menuState = IN_GAME;
	            HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	            return;
	        }
	    }

    if (menuState != IN_GAME) {
        if (menuState == MAIN_MENU) {
            uint8_t menuItemCount = 5; // Update the number of items in the main menu
            uint8_t nextMenuItem = (currentMenuItem + 1) % menuItemCount;
            DrawMenuItem(nextMenuItem);
        } else {
            uint8_t submenuItemCount;
            if (menuState == DIFFICULTY_MENU) {
                submenuItemCount = 3; // Number of items updated as difficulty submenu
            } else if (menuState == MAP_MENU) {
                submenuItemCount = 3; // Number of items updated as map submenu
            } else if (menuState == PLAYERS_MENU) {
                submenuItemCount = 2; // Number of items updated as player submenu
            } else if (menuState == HIGH_SCORES_MENU) {
                submenuItemCount = 1; // Set to the currently selected number of players
            } else {
                submenuItemCount = 2; // Number of items updated to other submenus
            }
            uint8_t nextSubmenuItem = (currentSubmenuItem + 1) % submenuItemCount;
            LCD_ClearArrow(currentSubmenuItem); // Use the new clear arrow function
            LCD_DrawArrow(nextSubmenuItem); // Use the new draw arrow function
            currentSubmenuItem = nextSubmenuItem;
        }
    }
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI15_10_IRQHandler(void) {
	 if (menuState == IN_GAME) {
	        if (ShowExitConfirmation()) {
	            menuState = MAIN_MENU;
	            LCD_DrawMenu();
	            HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	            return;
	        }
	 }
    if (menuState == MAIN_MENU) {
        if (currentMenuItem == 4) { // If the "Start Game" option is selected
        	// Here the map is generated according to the user's choice of game difficulty, map and number of players
        	menuState = START_GAME;
            GenerateGameMap(selectedDifficulty, selectedMap, selectedPlayers);
            menuState = IN_GAME;
            //DisplayScore(0, selectedPlayers);
        } else if (currentMenuItem == 3) { // If the "High Scores" option is selected
            menuState = HIGH_SCORES_MENU;
            LCD_DrawSubmenu(currentMenuItem + 1);
        } else {
            menuState = (MenuState)(currentMenuItem + 1); // Set menuState according to currentMenuItem
            LCD_DrawSubmenu(currentMenuItem + 1);
        }
    } else {
        /// The confirmation of the submenu is handled here
        // Perform the corresponding actions based on menuState and currentSubmenuItem
        switch (menuState) {
            case DIFFICULTY_MENU:
                selectedDifficulty = currentSubmenuItem + 1;
                break;
            case MAP_MENU:
                selectedMap = currentSubmenuItem + 1;
                break;
            case PLAYERS_MENU:
                selectedPlayers = currentSubmenuItem + 1;
                break;
            case HIGH_SCORES_MENU:
            	// Handle high score list related operations here
                break;
        }
        // Back to the main menu
        menuState = MAIN_MENU;
        currentSubmenuItem = 0;
        LCD_DrawMenu();
    }
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
