#pragma once
#include <stdint.h>
#define NUM_SPACE 31

//return count of chars
//places - количество знаков после десятичной точки
//minwidth - минимальная ширина, если меньше минимальной ширины, то добавляются пробелы
//outstr_size - максимальное количество символов, которые можно записать в outstr
//return количество символов записанное в outstr, ИСКЛЮЧАЯ завершающий 0
int floatToString(char * outstr, int outstr_size, float value, int places, int minwidth, bool rightjustify);
//return количество символов записанное в outstr (завершающего ноля не пишется)
int floatToStringWithoutZero(char * outstr, int outstr_size, float value, int places, int minwidth, bool rightjustify);

void intToString(char st[27], int32_t num, int length, char filler);

//Функции для дебага (частоупотребительные)
//Предполагают, что в строке достаточно места, чтобы туда вместились все символы.
//Добавляет целое число в конец строки.
void catInt(char* st, int32_t num);
//Добавляет вещественное число в конец строки.
void catFloat(char* st, float value, int places);
