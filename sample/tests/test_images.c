#include "UTFT.h"
#include "interface/interface.h"
#include "menu_root.h"
#include "interface/statusbar.h"

#include "test_images/books_16.h"
#include "test_images/books_4.h"
#include "test_images/components_16.h"
#include "test_images/components_4.h"
#include "test_images/csound_16.h"
#include "test_images/csound_4.h"

static void SceneImagesQuant();

void PrintImages()
{
    HeaderSetTextAndRedraw("Images");
    UTFT_setBackColor(VGA_BLACK);
    UTFT_fillRectBack(0, HeaderYEnd(), UTFT_getDisplayXSize(), UTFT_getDisplayYSize());
    UTFT_drawBitmap(10, 40, &books_16_img);
    UTFT_drawBitmap4(10, 100, &books_4_img);

    UTFT_drawBitmap(70, 40, &components_16_img);
    UTFT_drawBitmap4(70, 100, &components_4_img);

    UTFT_drawBitmap(130, 40, &csound_16_img);
    UTFT_drawBitmap4(130, 100, &csound_4_img);

    UTFT_drawBitmapS(210, 40, &components_16_img, 2);
}

void SceneImagesStart()
{
    PrintImages();
    InterfaceGoto(SceneImagesQuant);
}

void SceneImagesQuant()
{
    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }
}
