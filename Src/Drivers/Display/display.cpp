/*
****************************************************************************

****************************************************************************
*/
#include "display.h"
////////////////////////////////////////////////////////////////////////////
UBYTE Display::init_panel(void)
{
    //---------------------------
    time_counter = 0;
    //_______________________
    DEV_Module_Init();

    EPD_1IN54_V2_Init();
    EPD_1IN54_V2_Clear();
    DEV_Delay_ms(500);

    UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;

    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        return 0;
    }

    Paint_NewImage(BlackImage, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);

	return 1;
}
UBYTE Display::boot_panel(void)
{
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    //Paint_DrawBitMap(gImage_1in54);

    Paint_DrawRectangle(5, 5, 195, 195, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    //Paint_DrawCircle(100, 100, 95, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    Paint_DrawString_EN(25, 25, "Amaterasu", &Font24, WHITE, BLACK);

    EPD_1IN54_V2_Display(BlackImage);
    DEV_Delay_ms(500);

    EPD_1IN54_V2_Init_Partial();
    Paint_SelectImage(BlackImage);

    nPrintFlag = true;

    return 1;
}

UBYTE Display::refresh_panel(float nTemperature, float nHumidity, float nPressure, float nAltitude)
{
    Paint_ClearWindows(20, 60, 190, 190, WHITE);

/*
    int tmpInt1;
    float tmpFrac;
    int tmpInt2;

    char sTemperature[20];
    tmpInt1 = nTemperature;
    tmpFrac = nTemperature - tmpInt1;
    tmpInt2 = trunc(tmpFrac * 10);
    sprintf (sTemperature, "%d.%02d  C", tmpInt1, tmpInt2);

    char sHumidity[20];
    tmpInt1 = nHumidity;
    tmpFrac = nHumidity - tmpInt1;
    tmpInt2 = trunc(tmpFrac * 10);
    sprintf (sHumidity, "%d.%02d  %%RH", tmpInt1, tmpInt2);

    char sPressure[20];
    tmpInt1 = nPressure;
    tmpFrac = nPressure - tmpInt1;
    tmpInt2 = trunc(tmpFrac * 10);
    sprintf (sPressure, "%d.%01d  hPa", tmpInt1/100, tmpInt2);
*/
/*
    char *tmpSign = (adc_read < 0) ? "-" : "";
    float tmpVal = (adc_read < 0) ? -adc_read : adc_read;

    int tmpInt1 = tmpVal;                  // Get the integer (678).
    float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
    int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

    sprintf (str, "adc_read = %s%d.%04d\n", tmpSign, tmpInt1, tmpInt2);
*/
    char sTemperature[20];
    char sHumidity[20];
    char sPressure[20];
    char sAltitude[20];
    sprintf(sTemperature, "%6.1f C",   nTemperature);
    sprintf(sHumidity, "%6.1f %%",  nHumidity);
    sprintf(sPressure, "%6.1f hPa", nPressure);
    sprintf(sAltitude, "%6.1f m",   nAltitude);

    Paint_DrawString_EN(30, 70, (const char *) sTemperature,    &Font20, WHITE, BLACK);
    Paint_DrawString_EN(30, 100, (const char *) sHumidity,      &Font20, WHITE, BLACK);
    Paint_DrawString_EN(30, 130, (const char *) sPressure,      &Font20, WHITE, BLACK);
    Paint_DrawString_EN(30, 160, (const char *) sAltitude,      &Font20, WHITE, BLACK);

    if(nPrintFlag)
    {
        Paint_DrawLine(30, 60, 170, 60, WHITE, DOT_PIXEL_2X2, LINE_STYLE_DOTTED);
        //Paint_DrawLine(30, 175, 170, 175, BLACK, DOT_PIXEL_2X2, LINE_STYLE_DOTTED);
    }
    else
    {
        Paint_DrawLine(30, 60, 170, 60, BLACK, DOT_PIXEL_2X2, LINE_STYLE_DOTTED);
        //Paint_DrawLine(30, 175, 170, 175, WHITE, DOT_PIXEL_2X2, LINE_STYLE_DOTTED);
    }

    nPrintFlag = !nPrintFlag;

    EPD_1IN54_V2_DisplayPart(BlackImage);

    time_counter ++;
	return 1;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
