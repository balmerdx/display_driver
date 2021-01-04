#include "menu_root.h"
#include "interface/interface.h"
#include "interface/menu.h"
#include "fonts/font_condensed30.h"

static void MenuRootQuant();

enum
{
    MR_FONTS,
    MR_IMAGES,
    MR_PRIMITIVES,
    MR_PROGRESSBAR,
};


void MenuRootStart()
{
    g_default_font = font_condensed30;

    MenuReset("Testing graph libraty");
    MenuAdd("Fonts", MR_FONTS);
    MenuAdd("Images", MR_IMAGES);
    MenuAdd("Primitives", MR_PRIMITIVES);
    MenuAdd("Progressbar", MR_PROGRESSBAR);
    MenuRedraw();

    InterfaceGoto(MenuRootQuant);
}

void MenuRootQuant()
{
    MenuQuant();
    if(!EncButtonPressed())
        return;

    if(MenuData()==MR_FONTS)
    {
        SceneFontsStart();
        return;
    }

    if(MenuData()==MR_IMAGES)
    {
        SceneImagesStart();
        return;
    }

    if(MenuData()==MR_PRIMITIVES)
    {
        ScenePrimitivesStart();
        return;
    }

    if(MenuData()==MR_PROGRESSBAR)
    {
        SceneProgressbarStart();
        return;
    }
}
