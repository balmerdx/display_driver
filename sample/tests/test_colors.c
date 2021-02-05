#include "menu_root.h"

#include "UTFT.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "fonts/font_condensed30.h"

typedef struct
{
    uint16_t color;
    const char* name;
} COLOR_NAMES;

COLOR_NAMES colors[] =
{
    {VGA_BLACK, "BLACK"},
    {VGA_WHITE, "WHITE"},
    {VGA_RED, "RED"},
    {VGA_GREEN, "GREEN"},
    {VGA_BLUE, "BLUE"},
    {VGA_SILVER, "SILVER"},
    {VGA_GRAY, "GRAY"},
    {VGA_MAROON, "MAROON"},
    {VGA_YELLOW, "YELLOW"},
    {VGA_OLIVE, "OLIVE"},
    {VGA_LIME, "LIME"},
    {VGA_AQUA, "AQUA"},
    {VGA_TEAL, "TEAL"},
    {VGA_NAVY, "NAVY"},
    {VGA_FUCHSIA, "FUCHSIA"},
    {VGA_PURPLE, "PURPLE"},
};

static void SceneColorsQuant();

static void DrawColors()
{
    UTF_SetFont(font_condensed30);
    int colors_count = sizeof(colors)/sizeof(colors[0]);
    int colors_count2 = colors_count/2;
    int width = UTFT_getDisplayXSize()/2;
    int height = UTFT_getDisplayYSize()/colors_count2;

    int text_addy = (height-UTF_Height())/2;

    for(int x=0; x<2; x++)
    {
        for(int y=0; y<colors_count/2; y++)
        {
            int idx = x*colors_count2+y;
            int xx = x*width;
            int yy = y*height;

            COLOR_NAMES* c = colors+idx;
            UTFT_setBackColor(c->color);
            UTFT_fillRectBack(xx, yy, xx+width-1, yy+height-1);

            UTFT_setColor(VGA_WHITE);
            xx += 20;
            xx = UTF_DrawString(xx, yy+text_addy, c->name);
            xx += 5;
            UTFT_setColor(VGA_BLACK);
            xx = UTF_DrawString(xx, yy+text_addy, c->name);
        }
    }
}

void SceneColorsStart()
{
    DrawColors();
    InterfaceGoto(SceneColorsQuant);
}

void SceneColorsQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }
}
