# Драйвер для дисплеев на контроллерах ILI9481 и ILI9341

Весь код написан на С (без плюсов). На ILI9481 (480x320) с параллельным интерфейсом позволяет достичь полной перерисовки экрана менее, чем за 14 милисекунд.
ILI9341 (320x240) c SPI интерфейсом полная перерисовка экрана занимает порядка 100 милисекунд.

Позволяет выводить:
 * примитивы: линии, прямоугольники, круги.
 * текст: в том числе с разной шириной символов и антиалиасингом на границах букв
 * изображения: 16-ти битные и 4-х битные

Интерфейсная часть использует один quadrature encoder с кнопкой как устройство ввода.
Основные интерфейсные элементы это:
 * меню
 * progress bar
 * отрисовка графиков

Пару картинок железок сделанных на её основе
![RLC Meter H750](https://github.com/balmerdx/RLCMeterH750/blob/master/misc/img/device.jpg)
![BalmerDX VNA](https://raw.githubusercontent.com/balmerdx/BalmerDX_VNA/master/doc/wiki_img/home/vna_front.JPG)



Ниже приведу копирайты оригинальной библиотеки, от которой осталось в моем коде ооочень-очень мало.
Мало осталось, потому как сначала код был портирован с С++ на С (без плюсов).
Потом библиотека кардинально была ускоренна.
Потом полностью заменил вывод изображений и текста на свой код.
Потом выкинул все функции, которыми не пользовался.


Original library
 ILI9341 2.2 TFT SPI library
 based on UTFT.cpp - Arduino/chipKit library support for Color TFT LCD Boards
 Copyright (C)2010-2013 Henning Karlsen. All right reserved
 
 Compatible with other UTFT libraries.
 
 Original library you can find at http://electronics.henningkarlsen.com/
  
 This library is free software; you can redistribute it and/or
 modify it under the terms of the CC BY-NC-SA 3.0 license.
 Please see the included documents for further information.

