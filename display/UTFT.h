#pragma once

#include "utf_font.h"

#define UTFT_PORTRAIT 0
#define UTFT_LANDSCAPE 1
//rotate display to 180 degrees
#define UTFT_LANDSCAPE2 2

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x07E0
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010

#define UTFT_COLOR(r, g, b) ((((uint16_t)r)&248)<<8 | (((uint16_t)g)&252)<<3 | (((uint16_t)b)&248)>>3)
#define UTFT_RED(color) (((uint16_t)color>>8)&248)
#define UTFT_GREEN(color) (((uint16_t)color>>3)&252)
#define UTFT_BLUE(color) (((uint16_t)color<<3)&248)

typedef struct Bitmap16bit
{
    uint16_t width;
    uint16_t height;
    uint16_t colors[];
} Bitmap16bit;

typedef struct Bitmap4bit
{
    uint16_t width;
    uint16_t height;
    uint16_t palette[16];
    uint8_t colors[];
} Bitmap4bit;

//orientation - UTFT_PORTRAIT, UTFT_LANDSCAPE, UTFT_LANDSCAPE2
void UTFT_InitLCD(uint8_t orientation);
void UTFT_drawPixel(int x, int y);
void UTFT_drawLine(int x1, int y1, int x2, int y2);
void UTFT_fillScr(uint16_t color);
void UTFT_drawRect(int x1, int y1, int x2, int y2);
void UTFT_drawRoundRect(int x1, int y1, int x2, int y2);
void UTFT_fillRect(int x1, int y1, int x2, int y2);    //use foreground color
void UTFT_fillRectBack(int x1, int y1, int x2, int y2);//use background color
void UTFT_fillRoundRect(int x1, int y1, int x2, int y2);
void UTFT_drawCircle(int x, int y, int radius);
void UTFT_fillCircle(int x, int y, int radius);

//R,G,B to hi color
uint16_t UTFT_color(uint8_t r, uint8_t g, uint8_t b);

void UTFT_setColor(uint16_t color);
uint16_t UTFT_getColor();
void UTFT_setBackColor(uint32_t color);
uint16_t UTFT_getBackColor();

void UTFT_drawBitmap(int x, int y, const Bitmap16bit* bitmap);
void UTFT_drawBitmap4(int x, int y, const Bitmap4bit* bitmap);

//scaled image
void UTFT_drawBitmapS(int x, int y, const Bitmap16bit* bitmap, int scale);

//start unused function
void UTFT_lcdOff();
void UTFT_lcdOn();
void UTFT_setContrast(char c);
//end unused function

//Выдаёт ширину/высоту экрана 320x240 или 480x320
int  UTFT_getDisplayXSize();
int	 UTFT_getDisplayYSize();

//topFixedArea + verticalScrollArea + bottomFixedArea == 320
//default (0,320,0)
void UTFT_verticalScrollDefinition(uint16_t topFixedArea, uint16_t verticalScrollArea, uint16_t bottomFixedArea);
void UTFT_verticalScroll(uint16_t vsp);

