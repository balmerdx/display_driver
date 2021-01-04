#include "menu_root.h"
#include "interface/interface.h"
#include "interface/menu.h"
#include "interface/progress_bar.h"
#include "hardware/delay.h"
#include "float_to_string.h"
#include <string.h>

enum
{
    MR_RETURN,
    MR_START,
    MR_STOP,
    MR_STEP,
    MR_RESET,
};

static void SceneProgressbarQuant();
static void ProgressSetPosAndStatus(float pos);

static bool start_progress = false;
static uint32_t prev_ms = 0;

void SceneProgressbarStart()
{
    start_progress = false;
    ProgressInit(10, StatusbarYMin()-30, UTFT_getDisplayXSize()-20, 20);
    ProgressSetPosAndStatus(0);

    MenuReset("Test progressbar");
    MenuAdd("..", MR_RETURN);
    MenuAdd("Start", MR_START);
    MenuAdd("Stop", MR_STOP);
    MenuAdd("Step", MR_STEP);
    MenuAdd("Reset", MR_RESET);
    MenuRedraw();

    ProgressSetVisible(true);
    InterfaceGoto(SceneProgressbarQuant);
}

void ProgressSetPosAndStatus(float pos)
{
    ProgressSetPos(pos);

    char fs[10];
    floatToString(fs, sizeof(fs), pos*100, 1, 4, false);
    char text[STATUSBAR_STR_LEN];
    strcpy(text, "value = ");
    strcat(text, fs);
    strcat(text, " %");
    StatusbarSetTextAndRedraw(text);
}

void SceneProgressbarQuant()
{
    uint32_t cur_ms = TimeMs();
    if(start_progress)
    {
        uint32_t dt = cur_ms - prev_ms;
        prev_ms = cur_ms;
        float new_pos = ProgressPos() + dt * 0.2e-3f;
        if(new_pos > 1.f)
        {
            new_pos = 1.f;
            start_progress = false;
        }

        ProgressSetPosAndStatus(new_pos);
    }

    MenuQuant();
    if(!EncButtonPressed())
        return;

    if(MenuData()==MR_RETURN)
    {
        MenuRootStart();
        return;
    }

    if(MenuData()==MR_START)
    {
        start_progress = true;
        prev_ms = cur_ms;
    }

    if(MenuData()==MR_STOP)
    {
        start_progress = false;
    }

    if(MenuData()==MR_STEP)
    {
        float new_pos = ProgressPos() + 0.1f;
        if(new_pos > 1.f)
            new_pos = 1.f;
        ProgressSetPosAndStatus(new_pos);
    }

    if(MenuData()==MR_RESET)
    {
        start_progress = false;
        ProgressSetPosAndStatus(0);
    }
}
