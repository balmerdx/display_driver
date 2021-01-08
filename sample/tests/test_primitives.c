#include "UTFT.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "menu_root.h"
#include "math.h"

static void ScenePrimitivesQuant();

void DrawPrimitives()
{
    HeaderSetText("Draw primitives");
    HeaderRedraw();
    int ys = HeaderYEnd();

    UTFT_setBackColor(VGA_BLACK);
    UTFT_fillRectBack(0, ys, UTFT_getDisplayXSize(), UTFT_getDisplayYSize());

    UTFT_setColor(VGA_RED);
    UTFT_drawCircle(100, ys+50, 20);

    UTFT_setColor(VGA_GREEN);
    UTFT_fillCircle(150, ys+50, 20);

    UTFT_setColor(VGA_RED);
    UTFT_drawLine(10, ys+10, 30, ys+30);

    UTFT_setColor(VGA_GREEN);
    UTFT_drawLine(30, ys+30, 70, ys+10);

    UTFT_setColor(VGA_YELLOW);
    for(int i=0; i<360; i+=15)
    {
        float angle = i*((float)M_PI)/180;
        float len = 60;
        float x = 150;
        float y = ys+150;
        UTFT_drawLine(x, y, x+sinf(angle)*len, y+cosf(angle)*len);
    }

    UTFT_setColor(VGA_AQUA);
    UTFT_drawRect(180, ys+10, 220, ys+30);
    UTFT_fillRoundRect(180, ys+40, 220, ys+60);
    UTFT_fillRect(180, ys+70, 220, ys+90);
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
