#include "UTFT.h"
#include "interface/interface.h"
#include "menu_root.h"
#include "math.h"

static void ScenePrimitivesQuant();

void DrawPrimitives()
{
    UTFT_fillScr(VGA_BLACK);

    UTFT_setColor(VGA_RED);
    UTFT_drawCircle(100, 50, 20);

    UTFT_setColor(VGA_GREEN);
    UTFT_fillCircle(150, 50, 20);

    UTFT_setColor(VGA_RED);
    UTFT_drawLine(10, 10, 30, 30);

    UTFT_setColor(VGA_GREEN);
    UTFT_drawLine(30, 30, 70, 10);

    UTFT_setColor(VGA_YELLOW);
    for(int i=0; i<360; i+=15)
    {
        float angle = i*((float)M_PI)/180;
        float len = 60;
        float x = 150;
        float y = 150;
        UTFT_drawLine(x, y, x+sinf(angle)*len, y+cosf(angle)*len);
    }
}


void ScenePrimitivesStart()
{
    DrawPrimitives();
    InterfaceGoto(ScenePrimitivesQuant);
}

void ScenePrimitivesQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }

}
