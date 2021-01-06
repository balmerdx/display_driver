#include "UTFT.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "float_to_string.h"
#include "menu_root.h"
#include "hardware/delay.h"
#include <string.h>


static void DrawFullScreen(int idx, float fps)
{
    char str[40];
    strcpy(str, "FPS=");
    floatToString(str+strlen(str), 27, fps, 2, 0, false);

    HeaderSetTextAndRedraw("Redraw full screen");
    StatusbarSetTextAndRedraw(str);
    UTFT_setBackColor(idx);
    UTFT_fillRectBack(0, HeaderYEnd(), UTFT_getDisplayXSize(), StatusbarYMin()-1);
}

void SceneFpsStart()
{
    uint32_t start_ms = TimeMs();
    float fps = -1;
    int count = 0;
    while(1)
    {
        if(EncButtonPressed())
            break;
        DrawFullScreen(count, fps);
        count++;

        uint32_t delta_ms = TimeMs()-start_ms;
        fps = count*1000.f/delta_ms;
    }

    MenuRootStart();
}

