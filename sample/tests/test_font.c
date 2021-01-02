#include "UTFT.h"
#include "utf_font.h"
#include "fonts/DefaultFonts.h"
#include "fonts/font_condensed30.h"
#include "fonts/font_condensed59.h"
#include "fonts/font_small.h"
#include "fonts/font_big.h"
#include "fonts/font_8x15.h"
#include "fonts/font_seven_seg.h"

void DrawFontAlphabet()
{

#define DL(str) UTF_DrawStringJustify(0, y, str, UTFT_getDisplayXSize(), UTF_CENTER); \
        y+=UTF_Height();
//    UTFT_setColorW(VGA_GREEN); UTFT_drawLine(0, y+UTF_Ascent(), UTFT_getDisplayXSize()-1, y+UTF_Ascent()); UTFT_setColorW(VGA_WHITE);

    int y = 0;
    UTFT_setBackColorW(VGA_BLACK);
    UTFT_setColorW(VGA_WHITE);
/*
    UTF_SetFont(font_small);
    DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
    DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
    DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");

    UTF_SetFont(font_big);
    DL(" !\"#$%&'()*+,-./");
    DL("0123456789:;<=>?");
    DL("@ABCDEFGHIJKLMNOP");
    DL("QRSTUVWXYZ[\\]^_");
    DL("`abcdefghijklmnop");
    DL("qrstuvwxyz{|}~ ");

    UTF_SetFont(font_8x15);
    DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
    DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
    DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");

    UTF_SetFont(font_seven_seg);
    DL("0123456789");
*/

    UTF_SetFont(font_condensed30);
    DL(" !\"#$%&'()*+,-./0123456789:;<=>?");
    DL("()*+,-./0123456789:;<=>?");
    DL("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
    DL("`abcdefghijklmnopqrstuvwxyz{|}~ ");

    UTF_SetFont(font_condensed59);
    DL(" -.0123456789");

#undef DL
}
