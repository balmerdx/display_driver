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
    MR_PLOT,
    MR_STRING_JUSTIFY,
};

static int last_menu_index = 0;

void MenuRootStart()
{
    MenuReset2("Testing graph libraty");
    MenuAdd("Fonts", MR_FONTS);
    MenuAdd("Images", MR_IMAGES);
    MenuAdd("Primitives", MR_PRIMITIVES);
    MenuAdd("Progressbar", MR_PROGRESSBAR);
    MenuAdd("Plot", MR_PLOT);
    MenuAdd("String justify", MR_STRING_JUSTIFY);

    MenuSetIndex(last_menu_index);
    MenuRedraw();

    InterfaceGoto(MenuRootQuant);
}

void MenuRootQuant()
{
    MenuQuant();
    if(!EncButtonPressed())
        return;

    last_menu_index = MenuIndex();

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

    if(MenuData()==MR_PLOT)
    {
        ScenePlotStart();
        return;
    }

    if(MenuData()==MR_STRING_JUSTIFY)
    {
        SceneStringJustifyStart();
        return;
    }

}
