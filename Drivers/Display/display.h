/*
****************************************************************************

****************************************************************************
*/
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
////////////////////////////////////////////////////////////////////////////
#include "Config/DEV_Config.h"
#include "GUI/GUI_Paint.h"
#include "Config/Debug.h"
#include "e-Paper/EPD_1in54_V2.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
////////////////////////////////////////////////////////////////////////////
class Display
{
private:
    UBYTE *BlackImage;
    int time_counter;
    bool nPrintFlag;

public:
    UBYTE init_panel(void);
    UBYTE boot_panel(void);
    UBYTE refresh_panel(float nTemperature, float nHumidity, float nPressure, float nAltitude);
private:
    UBYTE update_text(void);
public:
    Display()
    {

    }
    ~Display()
    {

    }

};

////////////////////////////////////////////////////////////////////////////
#endif //_DISPLAY_H_
