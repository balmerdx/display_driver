#include "menu_root.h"
#include "interface/interface.h"
#include "interface/statusbar.h"
#include "interface/plot.h"
#include "float_to_string.h"
#include "hardware/delay.h"
#include <math.h>
#include <string.h>

static void ScenePlotQuant();

int cur_point_idx = 0;
Point points[PLOT_MAX_POINTS];
static uint32_t prev_ms = 0;

void ScenePlotStart()
{
    HeaderSetTextAndRedraw("Test plot graphs");
    StatusbarSetTextAndRedraw("");

    PlotInit(0, HeaderYEnd(), UTFT_getDisplayXSize(), StatusbarYMin()-HeaderYEnd());

    float xmin = -4, xmax = +4,
          ymin = -1.2f, ymax = +1.2f;
    PlotSetAxis(xmin, xmax, ymin, ymax);

    float dx = (xmax-xmin)/(PLOT_MAX_POINTS-1);
    for(int i=0; i<PLOT_MAX_POINTS; i++)
    {
        points[i].x = xmin + dx*i;
        points[i].y = sinf(points[i].x);
    }
    PlotDrawGraph(0, points, PLOT_MAX_POINTS, VGA_RED);

    for(int i=0; i<PLOT_MAX_POINTS; i++)
    {
        points[i].x = xmin + dx*i;
        points[i].y = cosf(points[i].x);
    }
    PlotDrawGraph(1, points, PLOT_MAX_POINTS, VGA_GREEN);

    InterfaceGoto(ScenePlotQuant);
}

void ScenePlotQuant()
{
    uint32_t cur_ms = TimeMs();
    uint32_t dt = cur_ms - prev_ms;
    if(PlotLineVisible() && dt>5000)
    {
        PlotLineSetVisible(false);
    }

    if(EncButtonPressed())
    {
        MenuRootStart();
        return;
    }

    if(EncValueChanged())
    {
        prev_ms = cur_ms;
        AddSaturated(&cur_point_idx, EncValueDelta(), PLOT_MAX_POINTS);
        PlotLineSetPosX(points[cur_point_idx].x);
        PlotLineSetVisible(true);

        //Update statusbar
        char text[STATUSBAR_STR_LEN];
        strcpy(text, "x = ");
        floatToString(text+strlen(text), sizeof(text)-strlen(text), points[cur_point_idx].x, 2, 4, false);
        strcat(text, " y = ");
        floatToString(text+strlen(text), sizeof(text)-strlen(text), points[cur_point_idx].y, 3, 4, false);

        StatusbarSetTextAndRedraw(text);
    }
}
