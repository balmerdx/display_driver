#include "UTFT.h"
#include "interface/interface.h"
#include "menu_root.h"
#include "hardware/delay.h"

static void SceneScrollQuant();

static uint32_t start_ms = 0;

void SceneScrollStart()
{
    start_ms = TimeMs();

    InterfaceGoto(SceneScrollQuant);
}

void SceneScrollQuant()
{
    uint32_t cur_ms = TimeMs();
    uint32_t dt = cur_ms - start_ms;

    uint16_t vsp = dt/2;
    if(vsp < UTFT_getDisplayXSize())
    {
        UTFT_verticalScroll(vsp);
    } else
    {
        UTFT_verticalScroll(0);
        MenuRootStart();
        return;
    }
}
