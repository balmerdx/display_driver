#pragma once

#include "UTFT.h"

//Фонт, которым рисуются menu/statusbar/
//Эту переменную надо инициализировать в самом начале программы, до того, как начал использоваться какой либо интерфейс.
extern const uint32_t* g_default_font;

typedef void (*SceneQuantHandler)();
typedef void (*SceneStartHandler)();

void InterfaceStart();
void InterfaceQuant();

//Очищает все нажатия, произошедшие до этого.
//Нужно вызывать после длительных операций, при которых не требуется пользовательский ввод.
void EncClear();

//R - right encoder
//L - left encoder
//Проверяет, что значение изменилось с предыдущего вызова EncRValueDelta()
bool EncValueChanged();
//На сколько изменилось положение энкодера
int EncValueDelta();

void InterfaceGoto(SceneQuantHandler handler);
bool InterfaceIsActive(SceneQuantHandler handler);

//Нажата ли кнопка?
//Возвращает true только при первом вызове.
//При последующих вызовах будет возвращать false,
//пока кнопка опять не отожмется и не нажмется заново.
bool EncButtonPressed();

//Складывает value+=add
//Значение после сложения помещается в интервал 0..max-1
void AddSaturated(int* value, int add, int max);

//Квант, который необходимо вызывать внутри диалогов
void DefaultQuant();
