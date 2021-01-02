#include "main.h"
#include "calculate.h"

static float VoltageADS1251(int32_t measureASD1251)
{
    //float kuINA240A1 = 20;
    float ku = 19;//AD8606 27k 1.5k
    return measureASD1251*4.096/(1<<23)/ku;
}


void calculate(int32_t measureASD1251, float Vout, float Rshunt, CalcResult* calc_result)
{
    float Vcurrent = VoltageADS1251(measureASD1251);
    Vcurrent -= 0.066e-3f;
    calc_result->Vcurrent = Vcurrent;
    float current = Vcurrent/Rshunt;

    calc_result->current = current;

    float resistance = 1e9;
    calc_result->infinity_resistance = true;
    if(current>1e-10)
    {
        calc_result->infinity_resistance = false;
        resistance = Vout/current;
    }

    calc_result->resistance = resistance;
}
