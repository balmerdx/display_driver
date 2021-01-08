#include "menu_root.h"

#include "UTFT.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "interface/rect_utils.h"
#include "fonts/font_condensed59.h"


static void SceneRectUtilsQuant();

void DrawRestangles()
{
    UTFT_setColor(VGA_WHITE);
    UTF_SetFont(g_default_font);

    RectA r_top;
    RectA r_top1, r_top2;
    RectA r_bottom;
    RectA r_bottom0, r_bottom1, r_bottom2;
    RectA r_center_up;
    RectA r_center_up0, r_center_up1, r_center_up2, r_center_up3;

    RectA r_tmp = R_DisplaySize();

    R_SplitY1(&r_tmp, UTF_Height(), &r_top, &r_tmp);

    UTF_SetFont(font_condensed59);
    R_SplitY2(&r_tmp, UTF_Height(), &r_tmp, &r_bottom);
    R_SplitY1(&r_tmp, UTF_Height(), &r_center_up, &r_tmp);

    R_SplitX1(&r_top, r_top.width/3, &r_top1, &r_top2);

    R_SplitX2(&r_bottom, r_top.width/3, &r_bottom1, &r_bottom2);
    R_SplitX2(&r_bottom1, UTF_StringWidth("-9.999"), &r_bottom0, &r_bottom1);

    R_SplitX1(&r_center_up, 50, &r_center_up0, &r_center_up);
    R_SplitX2(&r_center_up, 50, &r_center_up, &r_center_up3);

    R_SplitX1(&r_center_up, UTF_StringWidth("-99.999"), &r_center_up1, &r_center_up2);



    UTF_SetFont(g_default_font);
    UTFT_setBackColor(VGA_GREEN);
    R_DrawStringJustify(&r_top1, "Top1", UTF_CENTER);
    UTFT_setBackColor(VGA_RED);
    R_DrawStringJustify(&r_top2, "Top2", UTF_CENTER);



    UTFT_setBackColor(VGA_NAVY);
    R_FillRectBack(&r_bottom0);

    UTFT_setBackColor(VGA_FUCHSIA);
    UTF_SetFont(font_condensed59);
    R_DrawStringJustify(&r_bottom1, "0.123", UTF_RIGHT);

    UTFT_setBackColor(VGA_NAVY);
    UTF_SetFont(g_default_font);
    R_DrawStringJustify(&r_bottom2, "Bottom2", UTF_LEFT);

    UTFT_setBackColor(VGA_BLUE);
    UTF_SetFont(font_condensed59);
    R_DrawStringJustify(&r_center_up1, "-12.323", UTF_RIGHT);
    UTFT_setBackColor(VGA_LIME);
    UTF_SetFont(g_default_font);
    R_DrawStringJustify(&r_center_up2, " % def val", UTF_LEFT);

    UTFT_setBackColor(VGA_FUCHSIA);
    R_FillRectBack(&r_tmp);

    UTFT_setBackColor(VGA_NAVY);
    R_FillRectBack(&r_center_up0);
    R_FillRectBack(&r_center_up3);

}

void SceneRectUtilsStart()
{
    DrawRestangles();
    InterfaceGoto(SceneRectUtilsQuant);
}

void SceneRectUtilsQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }
}
