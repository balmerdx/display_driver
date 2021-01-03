#include "UTFT.h"

void DrawPrimitives()
{
    UTFT_setColorW(VGA_RED);
    UTFT_drawCircle(100, 50, 20);

    UTFT_setColorW(VGA_GREEN);
    UTFT_fillCircle(150, 50, 20);

    UTFT_setColorW(VGA_RED);
    UTFT_drawLine(10, 10, 30, 30);

    UTFT_setColorW(VGA_GREEN);
    UTFT_drawLine(30, 30, 70, 10);
}
