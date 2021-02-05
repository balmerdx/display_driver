#include "rect_utils.h"

RectA R_DisplaySize()
{
    RectA r = {
        .x = 0,
        .y = 0,
        .width = UTFT_getDisplayXSize(),
        .height = UTFT_getDisplayYSize(),
        .ascent = 0,
        .back_color = VGA_BLACK
        };

    return r;
}

void R_SplitX1(const RectA *in, int width1, RectA *out1, RectA *out2)
{
    RectA r1, r2;
    r1.x = in->x;
    r1.y = in->y;
    r1.width = width1;
    r1.height = in->height;
    r1.ascent = in->ascent;
    r1.back_color = in->back_color;

    r2.x = in->x + r1.width;
    r2.y = in->y;
    r2.width = in->width - width1;
    r2.height = in->height;
    r2.ascent = in->ascent;
    r2.back_color = in->back_color;

    *out1 = r1;
    *out2 = r2;
}

void R_SplitX2(const RectA *in, int width2, RectA *out1, RectA *out2)
{
    RectA r1, r2;

    r1.x = in->x;
    r1.y = in->y;
    r1.width = in->width - width2;
    r1.height = in->height;
    r1.ascent = in->ascent;
    r1.back_color = in->back_color;

    r2.x = in->x + r1.width;
    r2.y = in->y;
    r2.width = width2;
    r2.height = in->height;
    r2.ascent = in->ascent;
    r2.back_color = in->back_color;

    *out1 = r1;
    *out2 = r2;
}

static void R_UpdateAscent(RectA* in)
{
    int sub_ascent = UTF_Height() - UTF_Ascent();
    in->ascent = in->y + in->height - sub_ascent;
}

void R_SplitY1(const RectA* in, int height1, RectA* out1, RectA* out2)
{
    RectA r1, r2;

    r1.x = in->x;
    r1.y = in->y;
    r1.width = in->width;
    r1.height = height1;
    r1.back_color = in->back_color;
    R_UpdateAscent(&r1);

    r2.x = in->x;
    r2.y = in->y + r1.height;
    r2.width = in->width;
    r2.height = in->height - height1;
    r2.back_color = in->back_color;
    R_UpdateAscent(&r2);

    *out1 = r1;
    *out2 = r2;
}

void R_SplitY2(const RectA* in, int height2, RectA* out1, RectA* out2)
{
    RectA r1, r2;

    r1.x = in->x;
    r1.y = in->y;
    r1.width = in->width;
    r1.height = in->height - height2;
    r1.back_color = in->back_color;
    R_UpdateAscent(&r1);

    r2.x = in->x;
    r2.y = in->y + r1.height;
    r2.width = in->width;
    r2.height = height2;
    r2.back_color = in->back_color;
    R_UpdateAscent(&r2);

    *out1 = r1;
    *out2 = r2;
}

void R_FillRectBack(const RectA* in)
{
    UTFT_setBackColor(in->back_color);
    UTFT_fillRectBack(in->x, in->y,
                      in->x+in->width-1, in->y+in->height-1);
}

void R_DrawStringJustify(const RectA* in, const char* str, UTF_JUSTIFY justify)
{
    UTFT_setBackColor(in->back_color);
    //in->ascent = in->y + in->width - UTF_Height() + UTF_Ascent();
    int y = in->ascent - UTF_Ascent();
    if(in->y < y)
        UTFT_fillRectBack(in->x, in->y, in->x+in->width-1, y-1);

    UTF_DrawStringJustify(in->x, y, str, in->width, justify);

    int ymax = y + UTF_Height();
    if(ymax < in->y+in->height)
        UTFT_fillRectBack(in->x, ymax,
                          in->x+in->width-1, in->y+in->height-1);
}
