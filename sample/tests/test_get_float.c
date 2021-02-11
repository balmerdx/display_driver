#include "UTFT.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "interface/menu.h"
#include "interface/scene_get_float.h"
#include "float_to_string.h"
#include "menu_root.h"

#include <string.h>

static void SceneTestGetFloatQuant();

enum
{
    MF_RETURN,
    MF_FLOAT1,
    MF_FLOAT2,
};

static void UpdateFloat()
{
    char str[STATUSBAR_STR_LEN];
    strcpy(str, "float=");
    if(SceneGetFloatOk())
    {
        catFloat(str, SceneGetFloat(), 5);
    }
    StatusbarSetTextAndRedraw(str);
}


void SceneTestGetFloatStart()
{
    MenuReset("Test progressbar");
    MenuAdd("..", MF_RETURN);
    MenuAdd("Float 0..9", MF_FLOAT1);
    MenuAdd("Float 1..2", MF_FLOAT2);
    MenuRedraw();

    UpdateFloat();
    InterfaceGoto(SceneTestGetFloatQuant);
}

void SceneTestGetFloatQuant()
{
    MenuQuant();
    if(!EncButtonPressed())
        return;

    if(MenuData()==MF_RETURN)
    {
        MenuRootStart();
        return;
    }

    if(MenuData()==MF_FLOAT1)
    {
        SceneGetFloatStart("Get float 1", 0, 9, 3, 1, SceneTestGetFloatStart);
        return;
    }

    if(MenuData()==MF_FLOAT2)
    {
        SceneGetFloatStart("Get float 1", 1, 2, 2, 0, SceneTestGetFloatStart);
        return;
    }
}
