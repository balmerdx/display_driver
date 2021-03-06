
#ifdef DISPLAY_ILI9481
#include "hw_ili9481.h"

#include "delay.h"

#define TFT_PORT_RST  GPIOC
#define PIN_RST    GPIO_PIN_6

#define TFT_PORT_DC  GPIOC
#define PIN_DC    GPIO_PIN_9

#define TFT_PORT_CS  GPIOC
#define PIN_CS    GPIO_PIN_7

void HwLcdInit()
{
    GPIO_InitTypeDef gpio = {};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    gpio.Pull      = GPIO_NOPULL;
    gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Mode      = GPIO_MODE_OUTPUT_PP;

    gpio.Pin = PIN_WR;
    HAL_GPIO_Init(TFT_PORT_WR, &gpio);

    gpio.Pin = PIN_DC;
    HAL_GPIO_Init(TFT_PORT_DC, &gpio);

    gpio.Pin = PIN_RST;
    HAL_GPIO_Init(TFT_PORT_RST, &gpio);

    gpio.Pin = PIN_CS;
    HAL_GPIO_Init(TFT_PORT_CS, &gpio);

    //all 16 bit data
    gpio.Pin = 0xFFFF;
    HAL_GPIO_Init(TFT_DATA_PORT, &gpio);

    HAL_GPIO_WritePin(TFT_PORT_WR, PIN_WR, 1);
}

void DelaySome()
{
    DelayUs(5000);
}

void HwLcdPinCE(uint8_t on)
{
    HAL_GPIO_WritePin(TFT_PORT_CS, PIN_CS, on);
}

void HwLcdPinDC(uint8_t on)
{
    HAL_GPIO_WritePin(TFT_PORT_DC, PIN_DC, on);
}

void HwLcdPinRst(uint8_t on)
{
    HAL_GPIO_WritePin(TFT_PORT_RST, PIN_RST, on);
}

void HwLcdPinLed(uint8_t on)
{

}

void HwLcdSend(uint8_t data)
{
    HwLcdSend16NoWait(data);
}

#endif//DISPLAY_ILI9481
