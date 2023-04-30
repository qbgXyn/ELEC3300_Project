#include "lcd.h"
#include "ascii.h"	
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include "internal_bg.h"
#include <string.h>


extern uint8_t selectedDifficulty;
extern uint8_t selectedMap;
extern uint8_t selectedPlayers;


void		LCD_REG_Config          ( void );
void		LCD_FillColor           ( uint32_t ulAmout_Point, uint16_t usColor );
uint16_t	LCD_Read_PixelData      ( void );
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
int player1HighScore = 0;
int player2HighScore = 0;
void initMap(uint8_t difficulty);
void drawMap(uint8_t mapStyle);
void LCD_DrawForest();
void LCD_DrawDesert();
void LCD_DrawCity();


uint8_t currentMenuItem = 0;
void LCD_WriteArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *buffer);
void LCD_ReadArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *buffer);


void Delay ( __IO uint32_t nCount ){  for ( ; nCount != 0; nCount -- );}

void LCD_INIT ( void )
{
	LCD_BackLed_Control(ENABLE);      
	LCD_Rst();
	LCD_REG_Config();
	LCD_Clear (0, 0, 240, 320, BACKGROUND);
}



void LCD_Rst ( void )
{			
	HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_RESET);
	Delay ( 0xAFFf<<2 ); 					   
	HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET);
	Delay ( 0xAFFf<<2 ); 	
}


void LCD_BackLed_Control ( FunctionalState enumState )
{
	if ( enumState )
		HAL_GPIO_WritePin(LCD_BK_PORT,LCD_BK_PIN,GPIO_PIN_RESET);	
	else
		HAL_GPIO_WritePin(LCD_BK_PORT,LCD_BK_PIN,GPIO_PIN_SET);			
}

void LCD_Write_Cmd ( uint16_t usCmd )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_LCD_CMD ) = usCmd;
}

void LCD_Write_Data ( uint16_t usData )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = usData;
}

uint16_t LCD_Read_Data ( void )
{
	return ( * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) );	
}


void LCD_REG_Config ( void )
{
	/*  Power control B (CFh)  */
	DEBUG_DELAY  ();
	LCD_Write_Cmd ( 0xCF  );
	LCD_Write_Data ( 0x00  );
	LCD_Write_Data ( 0x81  );
	LCD_Write_Data ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xED );
	LCD_Write_Data ( 0x64 );
	LCD_Write_Data ( 0x03 );
	LCD_Write_Data ( 0x12 );
	LCD_Write_Data ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xE8 );
	LCD_Write_Data ( 0x85 );
	LCD_Write_Data ( 0x10 );
	LCD_Write_Data ( 0x78 );
	
	/*  Power control A (CBh) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xCB );
	LCD_Write_Data ( 0x39 );
	LCD_Write_Data ( 0x2C );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x34 );
	LCD_Write_Data ( 0x02 );
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xF7 );
	LCD_Write_Data ( 0x20 );
	
	/* Driver timing control B */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xEA );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xB1 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x1B );
	
	/*  Display Function Control (B6h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xB6 );
	LCD_Write_Data ( 0x0A );
	LCD_Write_Data ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xC0 );
	LCD_Write_Data ( 0x35 );
	
	/* Power Control 2 (C1h) */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0xC1 );
	LCD_Write_Data ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	LCD_Write_Cmd ( 0xC5 );
	LCD_Write_Data ( 0x45 );
	LCD_Write_Data ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	LCD_Write_Cmd ( 0xC7 );
	LCD_Write_Data ( 0xA2 );
	
	/* Enable 3G (F2h) */
	LCD_Write_Cmd ( 0xF2 );
	LCD_Write_Data ( 0x00 );
	
	/* Gamma Set (26h) */
	LCD_Write_Cmd ( 0x26 );
	LCD_Write_Data ( 0x01 );
	DEBUG_DELAY ();
	
	/* Positive Gamma Correction */
	LCD_Write_Cmd ( 0xE0 ); //Set Gamma
	LCD_Write_Data ( 0x0F );
	LCD_Write_Data ( 0x26 );
	LCD_Write_Data ( 0x24 );
	LCD_Write_Data ( 0x0B );
	LCD_Write_Data ( 0x0E );
	LCD_Write_Data ( 0x09 );
	LCD_Write_Data ( 0x54 );
	LCD_Write_Data ( 0xA8 );
	LCD_Write_Data ( 0x46 );
	LCD_Write_Data ( 0x0C );
	LCD_Write_Data ( 0x17 );
	LCD_Write_Data ( 0x09 );
	LCD_Write_Data ( 0x0F );
	LCD_Write_Data ( 0x07 );
	LCD_Write_Data ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	LCD_Write_Cmd ( 0XE1 ); //Set Gamma
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x19 );
	LCD_Write_Data ( 0x1B );
	LCD_Write_Data ( 0x04 );
	LCD_Write_Data ( 0x10 );
	LCD_Write_Data ( 0x07 );
	LCD_Write_Data ( 0x2A );
	LCD_Write_Data ( 0x47 );
	LCD_Write_Data ( 0x39 );
	LCD_Write_Data ( 0x03 );
	LCD_Write_Data ( 0x06 );
	LCD_Write_Data ( 0x06 );
	LCD_Write_Data ( 0x30 );
	LCD_Write_Data ( 0x38 );
	LCD_Write_Data ( 0x0F );
	
	/* memory access control set */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0x36 ); 	
	LCD_Write_Data ( 0xC8 );  // Version 1
//	LCD_Write_Data ( 0x00 );  // Version 2
	DEBUG_DELAY ();

	/* display inversion */
//	LCD_Write_Cmd ( 0x21 );   // Version 2
	DEBUG_DELAY ();
	
	/* column address control set */
	LCD_Write_Cmd ( CMD_Set_COLUMN ); 
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0xEF );
	
	/* page address control set */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( CMD_Set_PAGE ); 
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x01 );
	LCD_Write_Data ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY ();
	LCD_Write_Cmd ( 0x3a ); 
	LCD_Write_Data ( 0x55 );
	
	/* Sleep Out (11h)  */
	LCD_Write_Cmd ( 0x11 );	
	Delay ( 0xAFFf<<2 );
	DEBUG_DELAY ();
	
	/* Display ON (29h) */
	LCD_Write_Cmd ( 0x29 ); 
	
	
}

void LCD_OpenWindow ( uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight )
{	
	LCD_Write_Cmd ( CMD_Set_COLUMN ); 				
	LCD_Write_Data ( usCOLUMN >> 8  );	 
	LCD_Write_Data ( usCOLUMN & 0xff  );	 
	LCD_Write_Data ( ( usCOLUMN + usWidth - 1 ) >> 8  );
	LCD_Write_Data ( ( usCOLUMN + usWidth - 1 ) & 0xff  );

	LCD_Write_Cmd ( CMD_Set_PAGE ); 			     
	LCD_Write_Data ( usPAGE >> 8  );
	LCD_Write_Data ( usPAGE & 0xff  );
	LCD_Write_Data ( ( usPAGE + usHeight - 1 ) >> 8 );
	LCD_Write_Data ( ( usPAGE + usHeight - 1) & 0xff );
	
}

void LCD_FillColor ( uint32_t usPoint, uint16_t usColor )
{
	uint32_t i = 0;
	
	/* memory write */
	LCD_Write_Cmd ( CMD_SetPixel );	
		
	for ( i = 0; i < usPoint; i ++ )
		LCD_Write_Data ( usColor );
		
}

void LCD_Clear ( uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight, uint16_t usColor )
{
	LCD_OpenWindow ( usCOLUMN, usPAGE, usWidth, usHeight );
	LCD_FillColor ( usWidth * usHeight, usColor );		
	
}

uint16_t LCD_Read_PixelData ( void )	
{	
	uint16_t usR=0, usG=0, usB=0 ;

	
	LCD_Write_Cmd ( 0x2E ); 
	
	usR = LCD_Read_Data (); 	/*FIRST READ OUT DUMMY DATA*/
	
	usR = LCD_Read_Data ();  	/*READ OUT RED DATA  */
	usB = LCD_Read_Data ();  	/*READ OUT BLUE DATA*/
	usG = LCD_Read_Data ();  	/*READ OUT GREEN DATA*/	
	
  return ( ( ( usR >> 11 ) << 11 ) | ( ( usG >> 10 ) << 5 ) | ( usB >> 11 ) );
	
}

uint16_t LCD_GetPointPixel ( uint16_t usCOLUMN, uint16_t usPAGE )
{ 
	uint16_t usPixelData;

	LCD_OpenWindow ( usCOLUMN, usPAGE, 1, 1 );
	
	usPixelData = LCD_Read_PixelData ();
	
	return usPixelData;
	
}

void LCD_DrawLine ( uint16_t usC1, uint16_t usP1, uint16_t usC2, uint16_t usP2, uint16_t usColor )
{
	uint16_t us; 
	uint16_t usC_Current, usP_Current;
	
	int32_t lError_C = 0, lError_P = 0, lDelta_C, lDelta_P, lDistance; 
	int32_t lIncrease_C, lIncrease_P; 	
	
	
	lDelta_C = usC2 - usC1;
	lDelta_P = usP2 - usP1; 
	
	usC_Current = usC1; 
	usP_Current = usP1; 
	
	
	if ( lDelta_C > 0 ) 
		lIncrease_C = 1;  
	
	else if ( lDelta_C == 0 ) 
		lIncrease_C = 0;
	
	else 
  	{ 
    		lIncrease_C = -1;
    		lDelta_C = - lDelta_C;
  	} 
	if ( lDelta_P > 0 )
		lIncrease_P = 1; 
	else if ( lDelta_P == 0 )
		lIncrease_P = 0;
	else 
	{
  		lIncrease_P = -1;
    		lDelta_P = - lDelta_P;
 	} 
	if (  lDelta_C > lDelta_P )
		lDistance = lDelta_C; 
	else 
		lDistance = lDelta_P;
	for ( us = 0; us <= lDistance + 1; us ++ ) 
	{  
		LCD_DrawDot ( usC_Current, usP_Current, usColor );

		lError_C += lDelta_C ; 
		lError_P += lDelta_P ; 
		
		if ( lError_C > lDistance ) 
		{ 
			lError_C -= lDistance; 
			usC_Current += lIncrease_C; 
		}  
		
		if ( lError_P > lDistance ) 
		{ 
			lError_P -= lDistance; 
			usP_Current += lIncrease_P; 
		} 
	}  
}   


void LCD_DrawChar ( uint16_t usC, uint16_t usP, const char cChar )
{
	uint8_t ucTemp, ucRelativePositon, ucPage, ucColumn;


	ucRelativePositon = cChar - ' ';

	LCD_OpenWindow ( usC, usP, WIDTH_EN_CHAR, HEIGHT_EN_CHAR );

	LCD_Write_Cmd ( CMD_SetPixel );

	for ( ucPage = 0; ucPage < HEIGHT_EN_CHAR; ucPage ++ )
	{
		ucTemp = ucAscii_1608 [ ucRelativePositon ] [ ucPage ];

		for ( ucColumn = 0; ucColumn < WIDTH_EN_CHAR; ucColumn ++ )
		{
			if ( ucTemp & 0x01 )
				LCD_Write_Data ( 0x001F );

			else
				LCD_Write_Data (  0xFFFF );

			ucTemp >>= 1;

		}

	}

}


void LCD_DrawString ( uint16_t usC, uint16_t usP, const char * pStr )
{
	while ( * pStr != '\0' )
	{
		if ( ( usC - LCD_DispWindow_Start_COLUMN + WIDTH_EN_CHAR ) > LCD_DispWindow_COLUMN )
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP += HEIGHT_EN_CHAR;
		}
		
		if ( ( usP - LCD_DispWindow_Start_PAGE + HEIGHT_EN_CHAR ) > LCD_DispWindow_PAGE )
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP = LCD_DispWindow_Start_PAGE;
		}
		
		LCD_DrawChar ( usC, usP, * pStr );
		
		pStr ++;
		
		usC += WIDTH_EN_CHAR;
		
	}
	
}

void LCD_DrawDot(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usColor)	
{	
	LCD_OpenWindow (usCOLUMN, usPAGE, 1, 1);
	LCD_FillColor(1, usColor);
		
}

void LCD_DrawBackgroundImage()
{
    uint16_t x, y;
    uint16_t width = 240; // Width
    uint16_t height = 320; // Height

    LCD_OpenWindow(0, 0, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            LCD_Write_Data(main_menu[y * width + x]);
        }
    }
}



void LCD_DrawMenu(void)
{
    //LCD_Clear(0, 0, 240, 320, 0); // Clear LCD
	// Draw title and option text
    LCD_DrawBackgroundImage();
    LCD_DrawString(60, 10, "Snake Game");
    LCD_DrawString(40, 60, "1. Choose difficulty");
    LCD_DrawString(40, 90, "2. Choose map");
    LCD_DrawString(40, 120, "3. Choose player(s) (1-2)");
    LCD_DrawString(40, 150, "4. High scores");
    LCD_DrawString(40, 180, "5. Start game");

    // Shows the selected game difficulty, map and number of players
    char buffer[32];

    // Difficulty
    switch (selectedDifficulty)
    {
        case 1:
            strcpy(buffer, "Difficulty: Easy");
            break;
        case 2:
            strcpy(buffer, "Difficulty: Medium");
            break;
        case 3:
            strcpy(buffer, "Difficulty: Hard");
            break;
        default:
            strcpy(buffer, "Difficulty: Unknown");
            break;
    }
    LCD_DrawString(40, 210, buffer);

    // Map
    switch (selectedMap)
    {
        case 1:
            strcpy(buffer, "Map: Forest");
            break;
        case 2:
            strcpy(buffer, "Map: Desert");
            break;
        case 3:
            strcpy(buffer, "Map: Empty");
            break;
        default:
            strcpy(buffer, "Map: Unknown");
            break;
    }
    LCD_DrawString(40, 240, buffer);

    // Players
    switch (selectedPlayers)
    {
        case 1:
            strcpy(buffer, "Player: 1");
            break;
        case 2:
            strcpy(buffer, "Players: 2");
            break;
        default:
            strcpy(buffer, "Players: Unknown");
            break;
    }
    LCD_DrawString(40, 270, buffer);
}

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

void LCD_DrawSubmenu(uint8_t submenuIndex) {
    //LCD_Clear(0, 0, 240, 320, 0); // Clear LCD
    LCD_DrawBackgroundImage();
    char buffer[32]; // Define the buffer array inside the function
    switch (submenuIndex) {
        case 1: // Choose difficulty
            LCD_DrawString(40, 60, "1. Easy");
            LCD_DrawString(40, 90, "2. Medium");
            LCD_DrawString(40, 120, "3. Hard");
            LCD_DrawSubmenuArrow(0);
            break;
        case 2: // Choose map
            LCD_DrawString(40, 60, "1. Map: Forest");
            LCD_DrawString(40, 90, "2. Map: Desert");
            LCD_DrawString(40, 120, "3. Map: Empty");
            LCD_DrawSubmenuArrow(0);
            break;
        case 3: // Choose players
            LCD_DrawString(40, 60, "1. 1 Player");
            LCD_DrawString(40, 90, "2. 2 Players");
            LCD_DrawSubmenuArrow(0);
            break;
        case 4: // High scores
            LCD_DrawString(40, 60, "High Scores:");
            snprintf(buffer, sizeof(buffer), "P1 High Score: %d", player1HighScore);
            LCD_DrawString(40, 90, buffer);
            if (selectedPlayers == 2) {
                snprintf(buffer, sizeof(buffer), "P2 High Score: %d", player2HighScore);
                LCD_DrawString(40, 120, buffer);
            }
            break;
        default:
            break;
    }
}

uint8_t gameMap[GRID_SIZE_X][GRID_SIZE_Y];
uint8_t player1Score = 0;
uint8_t player2Score = 0;

void LCD_Fill(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight, uint16_t usColor)
{
    LCD_OpenWindow(usCOLUMN, usPAGE, usWidth, usHeight);
    LCD_FillColor(usWidth * usHeight, usColor);
}

void GenerateGameMap(uint8_t difficulty, uint8_t map, uint8_t players)
{
    // Clear LCD
    // LCD_Clear(0, 0, 240, 320, 0);

    // Draw the background according to the type of map chosen by the player
    switch (map) {
        case 1: // Forest Map
            LCD_DrawForest();
            break;
        case 2: // City Map
            LCD_DrawDesert();
            break;
        case 3:
            LCD_Clear(0, 0, 240, 320, 0xFFFF);
            break;
        default:
            // Handle any other cases if necessary
            break;
    }

    // Show player score
    char scoreBuffer[32];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "P1 Score: %d", player1Score);
    LCD_DrawString(10, 2, scoreBuffer);

    if (players == 2) {
        snprintf(scoreBuffer, sizeof(scoreBuffer), "P2 Score: %d", player2Score);
        LCD_DrawString(140, 2, scoreBuffer);
    }

    // Generate maps
    srand(HAL_GetTick()); // Initialize the random number seed with the current system clock
    for (uint8_t x = 0; x < GRID_SIZE_X; x++) {
        for (uint8_t y = 0; y < GRID_SIZE_Y; y++) {
        	// Initialize the random number seed with the current system clock
            if ((rand() % 100) < (difficulty * 3)) {
                gameMap[x][y] = 1;
                LCD_Fill(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLACK);
            } else {
                gameMap[x][y] = 0;
                // Draw a black square border
                LCD_DrawRectangle(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, (x * BLOCK_SIZE) + BLOCK_SIZE, (SCORE_AREA_HEIGHT + y * BLOCK_SIZE) + BLOCK_SIZE, BLACK);
            }
        }
    }
}

// This function is mainly used to prompt the user for the K1 and K2 buttons in the game
// The first time you click K1 or K2 in the game, an info box will be displayed.
// and then
// K1 - Reload Map
// k2 - Main Menu
int8_t ShowExitConfirmation() {
		// Draw the game's prompt box
	    LCD_DrawRectangle(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2),
	                      SCREEN_CENTER_X + (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y + (CONFIRM_BOX_HEIGHT / 2), BLACK);
	    LCD_Fill(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2) + 1, SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2) + 1,
	             CONFIRM_BOX_WIDTH - 2, CONFIRM_BOX_HEIGHT - 2, WHITE);

	    // Display prompt text
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y - 10, "K1: Reload Map");
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y + 10, "K2: Main Menu");

	    // Waiting for user input
	    uint8_t exitConfirmed = 0;
	    while (1) {
	        if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_SET) {
	            exitConfirmed = 1;
	            break;
	        }
	        if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_SET) {
	            exitConfirmed = 1;
	            break;
	        }
	    }

	    return exitConfirmed;
}

//uint16_t savedScreen[240][320];
//void SaveScreen(void) {
//    for (uint16_t x = 0; x < 240; x++) {
//        for (uint16_t y = 0; y < 320; y++) {
//            savedScreen[x][y] = LCD_GetPointPixel(x, y);
//        }
//    }
//}
//
//void RestoreScreen(void) {
//    for (uint16_t x = 0; x < 240; x++) {
//        for (uint16_t y = 0; y < 320; y++) {
//            LCD_DrawDot(x, y, savedScreen[x][y]);
//        }
//    }
//}

void LCD_ClearSubmenuArrow(uint8_t submenuIndex) {
    uint16_t arrow_y = 60 + submenuIndex * 30;
    LCD_DrawString(20, arrow_y, " ");
}

void LCD_DrawSubmenuArrow(uint8_t submenuIndex) {
    uint16_t arrow_y = 60 + submenuIndex * 30;
    LCD_DrawString(20, arrow_y, ">");
}


/////////////////////////////////////////////////////////////
//														   //
//														   //
//														   //
//    The following section is about the map background	   //
//														   //
//														   //
//														   //
/////////////////////////////////////////////////////////////
void LCD_DrawForest()
{
    uint16_t x, y;
    uint16_t width = 240; // Width
    uint16_t height = 320; // Height
    LCD_OpenWindow(0, 0, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            LCD_Write_Data(forest[y * width + x]);
        }
    }
}
void LCD_DrawDesert()
{
    uint16_t x, y;
    uint16_t width = 240; // Width
    uint16_t height = 320; // Height
    LCD_OpenWindow(0, 0, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            LCD_Write_Data(desert[y * width + x]);
        }
    }
}

void LCD_DrawCity()
{
    uint16_t x, y;
    uint16_t width = 240; // Width
    uint16_t height = 320; // Height

    LCD_OpenWindow(0, 0, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            LCD_Write_Data(city[y * width + x]);
        }
    }
}

