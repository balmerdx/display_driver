#include "UTFT.h"
#include "utf_font.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "menu_root.h"

#include "fonts/font_condensed30.h"
#include "fonts/font_condensed59.h"
#include "fonts/font_small.h"
#include "fonts/font_big.h"
#include "fonts/font_8x15.h"
#include "fonts/font_seven_seg.h"

static void SceneFontsQuant();

static int font_idx = 0;

enum
{
    FONT_COUNT = 6
};

void DrawFontAlphabet()
{

#define DL(str) UTF_DrawStringJustify(0, y, str, UTFT_getDisplayXSize(), UTF_CENTER); \
        y+=UTF_Height();
//    UTFT_setColor(VGA_GREEN); UTFT_drawLine(0, y+UTF_Ascent(), UTFT_getDisplayXSize()-1, y+UTF_Ascent()); UTFT_setColor(VGA_WHITE);

    int y = 0;
    UTFT_setBackColor(VGA_BLACK);
    UTFT_setColor(VGA_WHITE);

    if(font_idx==0)
    {
        StatusbarSetText0("font_small");
        UTF_SetFont(font_small);
        DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
        DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
        DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");
    }

    if(font_idx==1)
    {
        StatusbarSetText0("font_big");
        UTF_SetFont(font_big);
        DL(" !\"#$%&'()*+,-./");
        DL("0123456789:;<=>?");
        DL("@ABCDEFGHIJKLMNOP");
        DL("QRSTUVWXYZ[\\]^_");
        DL("`abcdefghijklmnop");
        DL("qrstuvwxyz{|}~ ");
    }


    if(font_idx==2)
    {
        StatusbarSetText0("font_8x15");
        UTF_SetFont(font_8x15);
        DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
        DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
        DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");
    }

    if(font_idx==3)
    {
        StatusbarSetText0("font_seven_seg");
        UTF_SetFont(font_seven_seg);
        DL("0123456789");
    }

    if(font_idx==4)
    {
        StatusbarSetText0("font_condensed30");
        UTF_SetFont(font_condensed30);
        DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
        DL("()*+,-./0123456789:;<=>?");
        DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
        DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");
    }

    if(font_idx==5)
    {
        StatusbarSetText0("font_condensed59");
        UTF_SetFont(font_condensed59);
        DL(" -.0123456789");
    }

    UTFT_fillRectBack(0, y, UTFT_getDisplayXSize(), StatusbarYMin()-1);
    StatusbarRedraw();
#undef DL
}

void SceneFontsStart()
{
    UTFT_setBackColor(VGA_BLACK);
    StatusbarSetText1("View fonts");
    DrawFontAlphabet();

    InterfaceGoto(SceneFontsQuant);
}

void SceneFontsQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }

    if(EncValueChanged())
    {
        AddSaturated(&font_idx, EncValueDelta(), FONT_COUNT);
        DrawFontAlphabet();
    }
}
