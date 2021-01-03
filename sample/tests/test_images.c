#include "UTFT.h"
#include "test_images/books_16.h"
#include "test_images/books_4.h"
#include "test_images/components_16.h"
#include "test_images/components_4.h"
#include "test_images/csound_16.h"
#include "test_images/csound_4.h"

void PrintImages()
{
    UTFT_fillScr(VGA_BLACK);
    UTFT_drawBitmap(10, 10, &books_16_img);
    UTFT_drawBitmap4(10, 70, &books_4_img);

    UTFT_drawBitmap(70, 10, &components_16_img);
    UTFT_drawBitmap4(70, 70, &components_4_img);

    UTFT_drawBitmap(130, 10, &csound_16_img);
    UTFT_drawBitmap4(130, 70, &csound_4_img);

    UTFT_drawBitmapS(210, 10, &components_16_img, 2);
}
