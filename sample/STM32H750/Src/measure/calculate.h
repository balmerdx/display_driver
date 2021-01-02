#pragma once

typedef struct
{
    float Vcurrent;
    float current;
    float resistance;
    bool infinity_resistance;
} CalcResult;

void calculate(int32_t measureASD1251, float Vout, float Rshunt, CalcResult* calc_result);
