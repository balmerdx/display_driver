/*
  Original library you can find at http://electronics.henningkarlsen.com/ 2010-2013 Henning Karlsen

  2014-2021 - Balmer code
    Fully reworked
    Ported to STM32
    Backported from C++ to C
    Added ILI9481
    Speed up
*/

uint32_t* utf_current_font = 0;

#ifdef DISPLAY_ILI9481
#include "hardware/hw_ili9481.h"

enum ENUM_ILI9481
{
    ENTER_SLEEP_MODE = 0x10,
    EXIT_SLEEP_MODE = 0x11,
    ENTER_NORMAL_MODE = 0x13,

    EXIT_INVERT_MODE = 0x20,
    ENTER_INVERT_MODE = 0x21,
    SET_DISPLAY_ON = 0x29,

    SET_COLUMN_ADDRESS = 0x2a,
    SET_PAGE_ADDRESS   = 0x2b,

    WRITE_MEMORY_START = 0x2c,

    SET_SCROLL_AREA = 0x33,
    SET_ADDRESS_MODE = 0x36,
    SET_SCROLL_START = 0x37,
    SET_PIXEL_FORMAT = 0x3a,

    FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING = 0xb3,

    PANEL_DRIVING = 0xc0,
    DISPLAY_TIMING_SETTING_NORMAL_MODE = 0xc1,
    DISPLAY_TIMING_SETTING_IDLE_MODE = 0xc3,
    FRAME_RATE_AND_INVERSION_CONTROL = 0xc5,
    INTERFACE_CONTROL = 0xc6,

    GAMMA_SETTING = 0xc8,

    POWER_SETTING = 0xd0,
    VCOM = 0xd1,
    POWER_SETTING_NORMAL_MODE = 0xd2,

    // SET_ADDRESS_MODE bits
    VERTICAL_FLIP         = 1,
    HORIZONTAL_FLIP       = 1 << 1,
    BGR                   = 1 << 3,
    VERTICAL_ORDER        = 1 << 4,
    PAGECOL_SELECTION     = 1 << 5,
    COLUMN_ADDRESS_ORDER  = 1 << 6,
    PAGE_ADDRESS_ORDER    = 1 << 7,

    // POWER_SETTING bits

    VC_095=0, VC_090=1, VC_085=2, VC_080=3, VC_075=4, VC_070=5, VC_DISABLE=6, VC_100=7,
    BT_6_5=0, BT_6_4=1, BT_6_3=2, BT_5_5=3, BT_5_4=4, BT_5_3=5, BT_4_4=6, BT_4_3=7,
    VCIRE=1 << 7,

    // INTERFACE_CONTROL bits

    DPL=1, EPL=1 << 1, HSPL=1 << 3, VSPL=1 << 4, SDA_EN=1 << 7,

    // SET_COLOUR_MODE bits

    COLOURS_8=0x11,
    COLOURS_64K=0x55,
    COLOURS_262K=0x66
};

static int disp_x_size=320-1, disp_y_size=480-1;

#else
#include "hardware/hw_ili9341.h"

enum ENUM_ILI9341
{
    ENTER_SLEEP_MODE = 0x10,
    EXIT_SLEEP_MODE = 0x11,
    ENTER_NORMAL_MODE = 0x13,

    EXIT_INVERT_MODE = 0x20,
    ENTER_INVERT_MODE = 0x21,
    SET_DISPLAY_ON = 0x29,

    SET_COLUMN_ADDRESS = 0x2a,
    SET_PAGE_ADDRESS   = 0x2b,

    WRITE_MEMORY_START = 0x2c,

    SET_SCROLL_AREA = 0x33,
    SET_ADDRESS_MODE = 0x36,
    SET_SCROLL_START = 0x37,
    SET_PIXEL_FORMAT = 0x3a,

    // SET_ADDRESS_MODE bits
    BGR                   = 1 << 3,
    VERTICAL_ORDER        = 1 << 4,
    PAGECOL_SELECTION     = 1 << 5,
    COLUMN_ADDRESS_ORDER  = 1 << 6,
    PAGE_ADDRESS_ORDER    = 1 << 7,

    // SET_COLOUR_MODE bits
    COLOURS_64K=0x55,
};

static int disp_x_size=239, disp_y_size=319;

#endif
#include "UTFT.h"

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define ARG(...) { __VA_ARGS__ }
#define CMD(cmd, data) { \
    static uint8_t data_arr[] =  data;  \
    sendCMDandData(cmd, data_arr, sizeof(data_arr)); \
    }

/*
	The functions and variables below should not normally be used.
	They have been left publicly available for use in add-on libraries
	that might need access to the lower level functions of UTFT.

	Please note that these functions and variables are not documented
	and I do not provide support on how to use them.
*/
static uint16_t front_color;
static uint16_t back_color;

void UTFT_drawHLine(int x, int y, int l);
void UTFT_drawVLine(int x, int y, int l);

void delay(uint32_t nTime)
{
	if(nTime==0)
		nTime = 1;
    HAL_Delay(nTime);
}

static void sendCMD(uint8_t index)
{
    HwLcdPinDC(0);
    HwLcdPinCE(0);
    HwLcdSend(index);
    HwLcdPinCE(1);
}

//Использовать только для записи данных в команду
static void LCD_WriteCommand_DATA16(uint16_t data)
{
#ifdef DISPLAY_SPI
    HwLcdPinDC(1);
    HwLcdPinCE(0);
    HwLcdSend16NoWait(data);
    HwLcdWait();
    HwLcdPinCE(1);
#else
    HwLcdPinDC(1);
    HwLcdPinCE(0);
    HwLcdSend16NoWait(data>>8);
    HwLcdSend16NoWait(data&0xFF);
    HwLcdWait();
    HwLcdPinCE(1);
#endif
}

void TFTBeginData()
{
    HwLcdPinDC(1);
    HwLcdPinCE(0);
}

#define TFTWriteData(data) HwLcdSend16NoWait(data)

void TFTEndData()
{
	HwLcdWait();
    HwLcdPinCE(1);
}

static void sendCMDandData(uint8_t cmd, uint8_t* data, int data_size)
{
    sendCMD(cmd);
    HwLcdPinDC(1);
    HwLcdPinCE(0);
    for(int i=0; i<data_size; i++)
        HwLcdSend(data[i]);
    HwLcdPinCE(1);
}


void UTFT_InitLCD(uint8_t orientation)
{
    uint8_t orient;
    HwLcdInit();
    HwLcdPinLed(1);
    HwLcdPinCE(1);
    HwLcdPinDC(1);

    HwLcdPinRst(0);
    delay(50);
    HwLcdPinRst(1);

    orient=orientation;
    if (orient==UTFT_LANDSCAPE || orient==UTFT_LANDSCAPE2)
    {
        swap(int, disp_x_size, disp_y_size);
    }

/*
    for(uint8_t i=0; i<3; i++)
    {
        uint8_t TFTDriver = UTFT_readID();
    }
*/
    delay(1);

#ifdef DISPLAY_ILI9481
    sendCMD(EXIT_SLEEP_MODE);
    delay(50);
    sendCMD(ENTER_NORMAL_MODE);

    // power setting
    CMD(POWER_SETTING, ARG(7,
                           (1 << 6) | 3,
                           5 | (1 << 4)));

    // VCom (more power settings)
    // register D1 for setting VCom
    CMD(VCOM, ARG(0, 0, 0));

    // power setting for normal mode

    CMD(POWER_SETTING_NORMAL_MODE, ARG(
            1, // drivers on
            2  // fosc ratios
            ));

    // panel driving setting

    CMD(PANEL_DRIVING, ARG(0, 0x3b, 0, 2, 1 | (1 << 4)));

    // display timing (c1)

    CMD(DISPLAY_TIMING_SETTING_NORMAL_MODE, ARG(
            1 << 4,         // line inversion, 1:1 internal clock
            16,             // 1 line = 16 clocks
            (8 << 4) | 8
            ));

    // display timing idle (c3)
    CMD(DISPLAY_TIMING_SETTING_IDLE_MODE, ARG(1 << 4, 0x20, 8));

    // frame rate = 72Hz
    CMD(FRAME_RATE_AND_INVERSION_CONTROL, ARG(3));

    // interface control
    CMD(INTERFACE_CONTROL, ARG(1 | (1 << 1)| (1 << 3) | (1 << 4)));

    // frame memory access (set DFM for 2 transfers/1 pixel in 18-bit mode)
    CMD(FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING, ARG(0, 0, 0, 1/*DFM*/));

    // set the colour depth and orientation
    CMD(SET_PIXEL_FORMAT, ARG(COLOURS_64K));

    if(orient==UTFT_LANDSCAPE2)
        CMD(SET_ADDRESS_MODE, ARG(PAGECOL_SELECTION | BGR)) //landscape2
    else if (orient==UTFT_LANDSCAPE)
        CMD(SET_ADDRESS_MODE, ARG(PAGECOL_SELECTION | HORIZONTAL_FLIP |VERTICAL_FLIP | BGR)) //landscape
    else
        CMD(SET_ADDRESS_MODE, ARG(HORIZONTAL_FLIP | BGR))    //portrait BGR

    //gamma
    //CMD(GAMMA_SETTING, ARG(0,0xf3,0,0xbc,0x50,0x1f,0,7,0x7f,0x7,0xf,0));

    // display on
    delay(100);
    sendCMD(SET_DISPLAY_ON);

    //sendCMD(EXIT_INVERT_MODE);
    sendCMD(ENTER_INVERT_MODE);
#endif

#ifdef DISPLAY_ILI9341
    CMD(0xCB, ARG(0x39,0x2C,0x00,0x34,0x02)); //Power control A
    CMD(0xCF, ARG(0x00, 0XC1, 0X30)); //Power control B
    CMD(0xE8, ARG(0x85, 0x00, 0x78)); //Driver timing control A
    CMD(0xEA, ARG(0x00,0x00)); //Driver timing control B
    CMD(0xED, ARG(0x64, 0x03, 0X12, 0X81)); //Power on sequence control
    CMD(0xF7, ARG(0x20)); //Pump ratio control
    CMD(0xC0, ARG(0x23 /*VRH[5:0]*/));    	//Power control
    CMD(0xC1, ARG(0x10 /*SAP[2:0];BT[3:0]*/));    	//Power control
    CMD(0xC5, ARG(0x3e/*Contrast*/, 0x28));    	//VCM control
    CMD(0xC7, ARG(0x86));    	//VCM control2
    

    // Memory Access Control
    if (orient==UTFT_LANDSCAPE)
        CMD(SET_ADDRESS_MODE, ARG(PAGECOL_SELECTION | COLUMN_ADDRESS_ORDER | PAGE_ADDRESS_ORDER | BGR)) //landscape
    else if(orient==UTFT_LANDSCAPE2)
        CMD(SET_ADDRESS_MODE, ARG(PAGECOL_SELECTION | BGR)) //landscape
    else
        CMD(SET_ADDRESS_MODE, ARG(COLUMN_ADDRESS_ORDER | BGR)) //Portrait
    
    CMD(SET_PIXEL_FORMAT, ARG(0x55/*DBI = 101 DPI=101*/));      //Pixel Format Set
    CMD(0xB1, ARG(0x00, 0x18));       //Frame Rate Control
    CMD(0xB6, ARG(0x08, 0x82, 0x27)); // Display Function Control
    CMD(0xF2, ARG(0x00));    	// 3Gamma Function Disable
    
    CMD(0x26, ARG(0x01));    	//Gamma curve selected
    
    CMD(0xE0, ARG(0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00)); //Set Gamma
    CMD(0XE1, ARG(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F)); //Set Gamma
    
    sendCMD(EXIT_SLEEP_MODE);    	//Exit Sleep
	delay(120); 
    
    sendCMD(SET_DISPLAY_ON);    //Display on
	delay(120);
#endif
}

//Установить прямоугольную область и начать записть в видеопамять
void UTFT_setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
#ifdef DISPLAY_SPI
    sendCMD(SET_COLUMN_ADDRESS);
	TFTBeginData();
	TFTWriteData(x1);
	TFTWriteData(x2);
	TFTEndData();
    sendCMD(SET_PAGE_ADDRESS);
	TFTBeginData();
	TFTWriteData(y1);
	TFTWriteData(y2);
	TFTEndData();
#else
    //Только 8 младших бит используются в команде
    sendCMD(SET_COLUMN_ADDRESS);
    TFTBeginData();
    TFTWriteData(x1>>8);
    TFTWriteData(x1&0xFF);
    TFTWriteData(x2>>8);
    TFTWriteData(x2&0xFF);
    TFTEndData();
    sendCMD(SET_PAGE_ADDRESS);
    TFTBeginData();
    TFTWriteData(y1>>8);
    TFTWriteData(y1&0xFF);
    TFTWriteData(y2>>8);
    TFTWriteData(y2&0xFF);
    TFTEndData();
#endif

    //memory write command
    sendCMD(WRITE_MEMORY_START);
}

void UTFT_drawRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

    UTFT_drawHLine(x1, y1, x2-x1);
    UTFT_drawHLine(x1, y2, x2-x1);
    UTFT_drawVLine(x1, y1, y2-y1);
    UTFT_drawVLine(x2, y1, y2-y1);
}

void UTFT_drawRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		UTFT_drawPixel(x1+1,y1+1);
		UTFT_drawPixel(x2-1,y1+1);
		UTFT_drawPixel(x1+1,y2-1);
		UTFT_drawPixel(x2-1,y2-1);
		UTFT_drawHLine(x1+2, y1, x2-x1-4);
		UTFT_drawHLine(x1+2, y2, x2-x1-4);
		UTFT_drawVLine(x1, y1+2, y2-y1-4);
		UTFT_drawVLine(x2, y1+2, y2-y1-4);
	}
}

void UTFT_fillRect(int x1, int y1, int x2, int y2)
{
    if (x1>x2)
    {
        swap(int, x1, x2);
    }
    if (y1>y2)
    {
        swap(int, y1, y2);
    }

    UTFT_setXY(x1, y1, x2, y2);

    TFTBeginData();
    int size = (x2-x1+1)*(y2-y1+1);
    for (int i=0; i<size; i++)
    {
        TFTWriteData(front_color);
    }
    TFTEndData();
}

void UTFT_fillRectBack(int x1, int y1, int x2, int y2)
{
    uint16_t old_color = UTFT_getColor();
    UTFT_setColor(UTFT_getBackColor());
    UTFT_fillRect(x1, y1, x2, y2);
    UTFT_setColor(old_color);
}


void UTFT_fillRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				UTFT_drawHLine(x1+2, y1+i, x2-x1-4);
				UTFT_drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				UTFT_drawHLine(x1+1, y1+i, x2-x1-2);
				UTFT_drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				UTFT_drawHLine(x1, y1+i, x2-x1);
				UTFT_drawHLine(x1, y2-i, x2-x1);
			}
		}
	}
}

void UTFT_drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
 
    UTFT_drawPixel(x, y + radius);
    UTFT_drawPixel(x, y - radius);
    UTFT_drawPixel(x + radius, y);
    UTFT_drawPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
        UTFT_drawPixel(x + x1, y + y1);
        UTFT_drawPixel(x - x1, y + y1);
        UTFT_drawPixel(x + x1, y - y1);
        UTFT_drawPixel(x - x1, y - y1);
        UTFT_drawPixel(x + y1, y + x1);
        UTFT_drawPixel(x - y1, y + x1);
        UTFT_drawPixel(x + y1, y - x1);
        UTFT_drawPixel(x - y1, y - x1);
	}
}

void UTFT_fillCircle(int x, int y, int radius)
{
	for(int y1=-radius; y1<=0; y1++) 
		for(int x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius) 
			{
                UTFT_drawHLine(x+x1, y+y1, 2*(-x1));
                UTFT_drawHLine(x+x1, y-y1, 2*(-x1));
				break;
			}
}

uint16_t UTFT_color(uint8_t r, uint8_t g, uint8_t b)
{
    return UTFT_COLOR(r,g,b);
}

void UTFT_fillScr(uint16_t color)
{	
    UTFT_setXY(0,0,disp_x_size,disp_y_size);
    TFTBeginData();
    for (int i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
    {
    	TFTWriteData(color);
    }
    TFTEndData();
}

void UTFT_setColor(uint16_t color)
{
    front_color = color;
}

uint16_t UTFT_getColor()
{
    return front_color;
}

void UTFT_setBackColor(uint32_t color)
{
    back_color = (uint16_t)color;
}

uint16_t UTFT_getBackColor()
{
    return back_color;
}

void UTFT_drawPixel(int x, int y)
{
	UTFT_setXY(x, y, x, y);
    TFTBeginData();
    TFTWriteData(front_color);
    TFTEndData();

}

void UTFT_drawLine(int x1, int y1, int x2, int y2)
{
	if (y1==y2)
		UTFT_drawHLine(x1, y1, x2-x1);
	else if (x1==x2)
		UTFT_drawVLine(x1, y1, y2-y1);
	else
	{
		unsigned int	dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		short			xstep =  x2 > x1 ? 1 : -1;
		unsigned int	dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		short			ystep =  y2 > y1 ? 1 : -1;
		int				col = x1, row = y1;

		if (dx < dy)
		{
			int t = - (dy >> 1);
			while (true)
			{
                UTFT_drawPixel(col, row);
				if (row == y2)
					break;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
			int t = - (dx >> 1);
			while (true)
			{
                UTFT_drawPixel(col, row);
				if (col == x2)
					break;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}
	}
}

void UTFT_drawHLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		x -= l;
	}
	UTFT_setXY(x, y, x+l, y);
	
	TFTBeginData();
	for (int i=0; i<l+1; i++)
	{
		TFTWriteData(front_color);
	}
	TFTEndData();
}

void UTFT_drawVLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		y -= l;
	}

	UTFT_setXY(x, y, x, y+l);

	TFTBeginData();
	for (int i=0; i<l+1; i++)
	{
		TFTWriteData(front_color);
	}
	TFTEndData();
}

void UTFT_drawBitmap(int x, int y, const Bitmap16bit* bitmap)
{
    int sx = bitmap->width;
    int sy = bitmap->height;
    const uint16_t* data = bitmap->colors;

    UTFT_setXY(x, y, x+sx-1, y+sy-1);
    TFTBeginData();
    int sxy = sx*sy;
    for (int tc=0; tc<sxy; tc++)
    {
        uint16_t col=data[tc];
        TFTWriteData(col);
    }
    TFTEndData();
}

void UTFT_drawBitmapS(int x, int y, const Bitmap16bit* bitmap, int scale)
{
    if (scale==1)
    {
        UTFT_drawBitmap(x, y, bitmap);
        return;
    }

    int sx = bitmap->width;
    int sy = bitmap->height;
    const uint16_t* data = bitmap->colors;

    int tx, ty, tsx, tsy;

    for (ty=0; ty<sy; ty++)
    {
        UTFT_setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
        TFTBeginData();
        for (tsy=0; tsy<scale; tsy++)
            for (tx=0; tx<sx; tx++)
            {
                uint16_t col=data[(ty*sx)+tx];
                for (tsx=0; tsx<scale; tsx++)
                    TFTWriteData(col);
            }
        TFTEndData();
    }
}

void UTFT_lcdOff()
{
    HwLcdPinLed(0);
}

void UTFT_lcdOn()
{
    HwLcdPinLed(1);
}

void UTFT_setContrast(char c)
{

}

int UTFT_getDisplayXSize()
{
    return disp_x_size+1;
}

int UTFT_getDisplayYSize()
{
    return disp_y_size+1;
}

void UTFT_verticalScrollDefinition(uint16_t topFixedArea, uint16_t verticalScrollArea, uint16_t bottomFixedArea)
{
    sendCMD(SET_SCROLL_AREA); //VSCRDEF (Vertical Scrolling Definition)
    LCD_WriteCommand_DATA16(topFixedArea);
    LCD_WriteCommand_DATA16(verticalScrollArea);
    LCD_WriteCommand_DATA16(bottomFixedArea);
}

void UTFT_verticalScroll(uint16_t vsp)
{
    sendCMD(SET_SCROLL_START);
    LCD_WriteCommand_DATA16(vsp);
}

uint16_t UTFT_getColor4(int x, int y, const Bitmap4bit* bitmap)
{
    int offset = (bitmap->width+1)/2*y+x/2;
    uint8_t data = bitmap->colors[offset];
    if(x&1)
        data = data>>4;
    else
        data = data&0xf;

    return bitmap->palette[data];
}

void UTFT_drawBitmap4(int x, int y, const Bitmap4bit* bitmap)
{
    int sx = bitmap->width;
    int sy = bitmap->height;

    UTFT_setXY(x, y, x+sx-1, y+sy-1);
    TFTBeginData();
    for (int ty=0; ty<sy; ty++)
    for (int tx=0; tx<sx; tx++)
    {
        uint16_t col=UTFT_getColor4(tx, ty, bitmap);
        TFTWriteData(col);
    }
    TFTEndData();
}

void UTFT_drawUtfChar1bit(int x, int y, int char_width, int char_height, uint32_t* data, int top_space, int bottom_space)
{
    UTFT_setXY(x, y, x+char_width-1, y+char_height+top_space+bottom_space-1);
    TFTBeginData();
    int sz_top = top_space*char_width;
    for(int i=0; i<sz_top; i++)
        TFTWriteData(back_color);

    int pixels = char_width*char_height;
    int size32 = pixels/32;
    int reminder32 = pixels%32;
    for(int sz=0; sz<size32; sz++)
    {
        uint32_t d = *data++;
        for(int i=0; i<32; i++)
            TFTWriteData((d&(1u<<i))?front_color:back_color);
    }

    uint32_t d = *data++;
    for(int i=0; i<reminder32; i++)
        TFTWriteData((d&(1u<<i))?front_color:back_color);

    int sz_bottom = bottom_space*char_width;
    for(int i=0; i<sz_bottom; i++)
        TFTWriteData(back_color);

    TFTEndData();
}


void UTFT_drawUtfChar2bit(int x, int y, int char_width, int char_height, uint32_t* data, int top_space, int bottom_space, uint16_t palette[4])
{
    UTFT_setXY(x, y, x+char_width-1, y+char_height+top_space+bottom_space-1);
    TFTBeginData();
    int sz_top = top_space*char_width;
    for(int i=0; i<sz_top; i++)
        TFTWriteData(back_color);

    int pixels = char_width*char_height;
    int size32 = pixels/16;
    int reminder32 = (pixels%16)*2;
    for(int sz=0; sz<size32; sz++)
    {
        uint32_t d = *data++;
        for(int i=0; i<32; i+=2)
        {
            TFTWriteData(palette[(d>>i)&3]);
        }
    }

    uint32_t d = *data++;
    for(int i=0; i<reminder32; i+=2)
        TFTWriteData(palette[(d>>i)&3]);

    int sz_bottom = bottom_space*char_width;
    for(int i=0; i<sz_bottom; i++)
        TFTWriteData(back_color);

    TFTEndData();
}
