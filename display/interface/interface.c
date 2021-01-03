#include "main.h"
#include "interface.h"
#include "hardware/quadrature_encoder.h"

static int16_t encValue = 0;
SceneQuantHandler g_quant_handler = NULL;

const uint32_t* g_default_font = NULL;

void InterfaceStart()
{
    UTFT_setBackColor(VGA_BLACK);
    UTFT_fillScr(VGA_BLACK);

    UTF_SetFont(g_default_font);
    UTFT_setColor(VGA_WHITE);

    encValue = QuadEncValue();
}

void InterfaceQuant()
{
    if(g_quant_handler)
        (*g_quant_handler)();
}

void InterfaceGoto(SceneQuantHandler handler)
{
    EncClear();
    g_quant_handler = handler;
}

bool InterfaceIsActive(SceneQuantHandler handler)
{
    return g_quant_handler == handler;
}

void EncClear()
{
    if(EncValueChanged())
    {
        EncValueDelta();
    }

    EncButtonPressed();
}

bool EncValueChanged()
{
    return QuadEncValue() != encValue;
}

int EncValueDelta()
{
    int16_t v = QuadEncValue();
    int16_t delta = v - encValue;
    encValue = v;
    return delta;
}

void AddSaturated(int *value, int add, int max)
{
    *value = (*value + add)%max;
    if(*value<0)
        *value += max;

}
