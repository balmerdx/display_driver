#include "UTFT.h"
#include "utf_font.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "menu_root.h"
#include "fonts/font_condensed30.h"

static void SceneStringJustifyQuant();

static void DrawStringJustify()
{
    HeaderSetTextAndRedraw("String justify");
    StatusbarSetTextAndRedraw("Test end clamp");

    UTFT_setBackColor(VGA_BLACK);
    UTFT_fillRectBack(0, HeaderYEnd(), UTFT_getDisplayXSize(), StatusbarYMin()-1);

    UTF_SetFont(font_condensed30);
    UTFT_setBackColor(VGA_TEAL);
    UTFT_setColor(VGA_WHITE);
    int y = HeaderYEnd();
    int xmin = UTFT_getDisplayXSize()-60;
    UTF_DrawString(xmin, y, "Hello"); y+=UTF_Height();
    UTF_DrawString(xmin, y, "Hellolen"); y+=UTF_Height();

    xmin = 40;
    int xmax = 120;
    y = HeaderYEnd();
    UTF_DrawStringJustify(xmin, y, "60 px", xmax-xmin, UTF_LEFT); y+=UTF_Height();
    UTF_DrawStringJustify(xmin, y, "60 px", xmax-xmin, UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(xmin, y, "60 px", xmax-xmin, UTF_RIGHT); y+=UTF_Height();

    UTF_DrawStringJustify(xmin, y, "LONGTEXT", xmax-xmin, UTF_LEFT); y+=UTF_Height();
    UTF_DrawStringJustify(xmin, y, "LONGTEXT", xmax-xmin, UTF_CENTER); y+=UTF_Height();
    UTF_DrawStringJustify(xmin, y, "LONGTEXT", xmax-xmin, UTF_RIGHT); y+=UTF_Height();

}

void SceneStringJustifyStart()
{
    DrawStringJustify();

    InterfaceGoto(SceneStringJustifyQuant);
}

void SceneStringJustifyQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }

}
