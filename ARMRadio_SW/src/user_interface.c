/*
 * user_interface.c
 *
 *  Created on: 18 apr 2020
 *      Author: albytest
 */

#include "main.h"

#ifdef USE_LCD
/**
  * @brief  Display ADCs converted values on LCD
  * @param  None
  * @retval None
  */

#define DISPLAY_H 320
#define CELL_H 36
#define CELL_W 60

void DisplayFrequency(void)
{
	 uint8_t aTextBuffer[50];
	 sprintf((char*)aTextBuffer, "F %-4.3f KHz", (LOfreq/1000.0));
	    LCD_DisplayStringLine(LCD_LINE_3, (uint8_t*)aTextBuffer);
}

void Touch(void)
{
	 static TP_STATE* TP_State;
	 static uint16_t Old_TP_State, AllowAutoRepeatCounter;

    TP_State = IOE_TP_GetState();

    if (Old_TP_State!=0)
    {
    	Old_TP_State=TP_State->TouchDetected;

    	if(AllowAutoRepeatCounter<20)
    	{
    		AllowAutoRepeatCounter++;
    		return;
    	}
    }
    else
    {
    	AllowAutoRepeatCounter=0;
    }

	Old_TP_State = TP_State->TouchDetected;

	if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H)
			&& (TP_State->Y >= DISPLAY_H - CELL_H) && (TP_State->X >= 0)
			&& (TP_State->X <= 2 * CELL_W)) {
		FminusClicked();
		DisplayFrequency();
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H)
			&& (TP_State->Y >= DISPLAY_H - CELL_H) && (TP_State->X >= 2 * CELL_W + 1)
			&& (TP_State->X <= 4 * CELL_W)) {
		FplusClicked();
		DisplayFrequency();
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 2) && (TP_State->X >= 0)
			&& (TP_State->X <= 2 * CELL_W)) {
		volume -= 0.1;
		if (volume < 0)
			volume = 0;
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 2) && (TP_State->X >= 2 * CELL_W + 1)
			&& (TP_State->X <= 4 * CELL_W)) {
		volume += 0.1;
		if (volume > 1.0)
			volume = 1.0;
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 2)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 3) && (TP_State->X >= 0)
			&& (TP_State->X <= CELL_W)) {
		SetFstep(4);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 2)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 3) && (TP_State->X >= CELL_W + 1)
			&& (TP_State->X <= 2 * CELL_W)) {
		SetFstep(3);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 2)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 3) && (TP_State->X >= 2 * CELL_W + 1)
			&& (TP_State->X <= 3 * CELL_W)) {
		SetFstep(2);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 2)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 3) && (TP_State->X >= 3 * CELL_W + 1)
			&& (TP_State->X <= 4 * CELL_W)) {
		SetFstep(1);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 3)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 4) && (TP_State->X >= 0)
			&& (TP_State->X <= CELL_W)) {
		SetMode(AM);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 3)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 4) && (TP_State->X >= CELL_W + 1)
			&& (TP_State->X <= 2 * CELL_W)) {
		SetMode(LSB);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 3)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 4) && (TP_State->X >= 2 * CELL_W + 1)
			&& (TP_State->X <= 3 * CELL_W)) {
		SetMode(USB);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 3)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 4) && (TP_State->X >= 3 * CELL_W + 1)
			&& (TP_State->X <= 4 * CELL_W)) {
		SetMode(CW);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 4)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 5) && (TP_State->X >= 0)
			&& (TP_State->X <= CELL_W)) {
		SetAGC(Fast);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 4)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 5) && (TP_State->X >= CELL_W + 1)
			&& (TP_State->X <= 2 * CELL_W)) {
		SetAGC(Slow);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 4)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 5) && (TP_State->X >= 2 * CELL_W + 1)
			&& (TP_State->X <= 3 * CELL_W)) {
		SetBW(Narrow);
	} else if ((TP_State->TouchDetected) && (TP_State->Y <= DISPLAY_H - CELL_H * 4)
			&& (TP_State->Y >= DISPLAY_H - CELL_H * 5) && (TP_State->X >= 3 * CELL_W + 1)
			&& (TP_State->X <= 4 * CELL_W)) {
		SetBW(Wide);
	} else {
	}
}

void Display(void)
{
  uint8_t aTextBuffer[50];
  float SValue;

  /* "The recommendation defines a difference of one S-unit corresponds to a difference of 6 decibels (dB),
   *  equivalent to a voltage ratio of two, or power ratio of four." https://en.wikipedia.org/wiki/S_meter
   */

  SValue = 10 / 3.01 * log10(PeakAudioValue * 2000.0);


  sprintf((char*)aTextBuffer, "S %-4.1f ", SValue);
  LCD_DisplayStringLine(LCD_LINE_2, (uint8_t*)aTextBuffer);

}

/**
  * @brief  Display Init (LCD)
  * @param  None
  * @retval None
  */
void Display_Init(void)
{
	uint16_t n;
  /* Initialize the LCD */
  LCD_Init();
  LCD_LayerInit();

  /* Eable the LTDC */
  LTDC_Cmd(ENABLE);

  /* Set LCD Background Layer  */
  LCD_SetLayer(LCD_BACKGROUND_LAYER);

  /* Configure the transparency for background */
  LCD_SetTransparency(0);

  /* Set LCD Foreground Layer  */
  LCD_SetLayer(LCD_FOREGROUND_LAYER);

  /* Configure the transparency for foreground */
  LCD_SetTransparency(255);

  /* Clear the Foreground Layer */
  LCD_Clear(LCD_COLOR_BLACK);



  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(LCD_COLOR_BLACK);

  LCD_SetTextColor(LCD_COLOR_GREEN);
  LCD_SetFont(&Font12x12);

  LCD_DisplayStringLine(LINE(24), (uint8_t*) "  F-             F+");
  LCD_DisplayStringLine(LINE(21), (uint8_t*) "  V-             V+");
  LCD_DisplayStringLine(LINE(18), (uint8_t*) "10   100   1K   10K");
  LCD_DisplayStringLine(LINE(15), (uint8_t*) "AM   LSB   USB   CW");
  LCD_DisplayStringLine(LINE(12), (uint8_t*) "FAST SLOW  NRRW WIDE");

  for (n=0; n<6; n++)
  {
	  LCD_DrawLine(0, 319 - n*CELL_H, 240, LCD_DIR_HORIZONTAL);
  }
  LCD_DrawLine(120, 319 - 5*CELL_H, 5*CELL_H, LCD_DIR_VERTICAL);
  LCD_DrawLine(60, 319 - 5*CELL_H, 3*CELL_H, LCD_DIR_VERTICAL);
  LCD_DrawLine(180, 319 - 5*CELL_H, 3*CELL_H, LCD_DIR_VERTICAL);
  LCD_SetFont(&Font16x24);

}
#endif /* USE_LCD */
