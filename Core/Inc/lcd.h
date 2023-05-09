#ifndef __LCD_H
#define	__LCD_H

#include "stm32f1xx_hal.h"

#define      FSMC_Addr_LCD_CMD         ( ( uint32_t ) 0x60000000 )
#define      FSMC_Addr_LCD_DATA        ( ( uint32_t ) 0x60020000 )

#define      FSMC_Bank1_NORSRAMx       FSMC_Bank1_NORSRAM1

#define      LCD_RST_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      LCD_RST_CLK               RCC_APB2Periph_GPIOE
#define      LCD_RST_PORT              GPIOE
#define      LCD_RST_PIN               GPIO_PIN_1

#define      LCD_BK_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      LCD_BK_CLK                RCC_APB2Periph_GPIOD
#define      LCD_BK_PORT               GPIOD
#define      LCD_BK_PIN                GPIO_PIN_12

#define      DEBUG_DELAY()

#define      LCD_Default_Max_COLUMN	240
#define      LCD_Default_Max_PAGE	320

#define      LCD_DispWindow_Start_COLUMN	0
#define      LCD_DispWindow_Start_PAGE		0

#define      LCD_DispWindow_COLUMN	240
#define      LCD_DispWindow_PAGE	320

#define      WIDTH_EN_CHAR		8
#define      HEIGHT_EN_CHAR		16

#define      GetGBKCode( ucBuffer, usChar )


#define      WHITE		           0xFFFF
#define      BLACK                         0x0000
#define      GREY                          0xF7DE
#define      BLUE                          0x001F
#define      GREEN                         0x07E0
#define      RED                           0xF800
#define      MAGENTA                       0xF81F
#define      CYAN                          0x7FFF
#define      YELLOW                        0xFFE0
#define      TITLE_TEXT_COLOR              0xB6FD
#define      TITLE_TEXT_BACKGROUND         0x5ACB
#define      BACKGROUND		               WHITE
#define      PLAYER_1_HEAD_COLOR           MAGENTA
#define      PLAYER_1_BODY_COLOR           BLUE
#define      PLAYER_2_HEAD_COLOR           GREEN
#define      PLAYER_2_BODY_COLOR           YELLOW
#define      STONE_COLOR                   BLACK
#define      FOOD_COLOR                    RED
#define      EMPTY_COLOR                   BLACK


#define      CMD_Set_COLUMN		   0x2A
#define      CMD_Set_PAGE		   0x2B
#define      CMD_SetPixel		   0x2C

void            LCD_INIT		( void );
void            LCD_Rst			( void );
void            LCD_BackLed_Control	( FunctionalState enumState );
void            LCD_Write_Cmd		( uint16_t usCmd );
void            LCD_Write_Data		( uint16_t usData );
uint16_t        LCD_Read_Data		( void );
void		    LCD_FillColor		( uint32_t   usPoint, uint16_t usColor );
void            LCD_OpenWindow		( uint16_t usC, uint16_t usP, uint16_t usWidth, uint16_t usHeight );
void            LCD_Clear		( uint16_t usC, uint16_t usP, uint16_t usWidth, uint16_t usHeight, uint16_t usColor );
uint16_t        LCD_GetPointPixel	( uint16_t usC , uint16_t usP );
void            LCD_DrawLine		( uint16_t usC1, uint16_t usP1, uint16_t usC2, uint16_t usP2, uint16_t usColor );
void            LCD_DrawChar		( uint16_t usC, uint16_t usP, const char cChar);
void            LCD_DrawCharWithColor ( uint16_t usC, uint16_t usP, const char cChar, uint16_t usColor, uint16_t bgColor);
void            LCD_DrawCharTranslucent ( uint16_t usC, uint16_t usP, const char cChar, uint16_t usColor);
void            LCD_DrawString		( uint16_t usC, uint16_t usP, const char * pStr);
void            LCD_DrawStringWithColor ( uint16_t usC, uint16_t usP, const char * pStr, uint16_t usColor, uint16_t bgColor);
void            LCD_DrawImgTranslucent ( uint16_t usC, uint16_t usP, const unsigned short* img);
void            LCD_DrawDot		( uint16_t usC, uint16_t usP, uint16_t usColor );
void            LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);




// Color
#define LCD_COLOR_WHITE 0xFFFF
#define LCD_COLOR_GRAY 0x7BEF
#define LCD_COLOR_YELLOW 0xFFE0
#define LCD_COLOR_GREEN 0x07E0
#define LCD_COLOR_BLACK 0x0000

void LCD_Fill(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight, uint16_t usColor);

// Handling the map square and score position
#define GRID_SIZE_X 12
#define GRID_SIZE_Y 15
#define BLOCK_SIZE 20
#define SCORE_AREA_HEIGHT 20

// Handles generating an in-game prompt box for whether or not to exit the game
#define CONFIRM_BOX_WIDTH 150
#define CONFIRM_BOX_HEIGHT 60
#define SCREEN_CENTER_X 120
#define SCREEN_CENTER_Y 160

// PIN
#define K2_Pin GPIO_PIN_13
#define K2_GPIO_Port GPIOC
#define K2_EXTI_IRQn EXTI15_10_IRQn
#define K1_Pin GPIO_PIN_0
#define K1_GPIO_Port GPIOA
#define K1_EXTI_IRQn EXTI0_IRQn
#define LCD_BL_Pin GPIO_PIN_12
#define LCD_BL_GPIO_Port GPIOD
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOE

#endif

