#include "UTFT.h"
#include "utf_font.h"
#include "fonts/DefaultFonts.h"
#include "fonts/font_condensed30.h"
#include "fonts/font_condensed59.h"

void DrawFontAlphabet()
{
    int y = 0;
    UTFT_setBackColorW(VGA_BLACK);
    UTFT_setColorW(VGA_WHITE);

    UTFT_setFont(SmallFont);
    UTF_DrawStringJustify(0, y, " !\"#$%&'()*+,-./0123456789:;<=>?", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "`abcdefghijklmnopqrstuvwxyz{|}~ ", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();

    UTFT_setFont(BigFont);
    UTF_DrawStringJustify(0, y, " !\"#$%&'()*+,-./0123456789:;<=>?", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "`abcdefghijklmnopqrstuvwxyz{|}~ ", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();

    UTFT_setFont(FONT8x15);
    UTF_DrawStringJustify(0, y, " !\"#$%&'()*+,-./0123456789:;<=>?", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "`abcdefghijklmnopqrstuvwxyz{|}~ ", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();

    UTFT_setFont(SevenSegNumFont);
    UTF_DrawStringJustify(0, y, "0123456789", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();

    UTF_SetFont(font_condensed30);
    UTF_DrawStringJustify(0, y, " !\"#$%&'()*+,-./0123456789:;<=>?", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(0, y, "`abcdefghijklmnopqrstuvwxyz{|}~ ", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();

    UTF_SetFont(font_condensed59);
    UTF_DrawStringJustify(0, y, " -.0123456789", UTFT_getDisplayXSize(), UTF_CENTER); y+=UTF_Height();


}
