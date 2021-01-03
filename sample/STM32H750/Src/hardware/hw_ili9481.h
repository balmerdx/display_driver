#pragma once

#ifdef DISPLAY_ILI9481

#define TFT_DATA_PORT GPIOD
#define TFT_PORT_WR  GPIOC
#define PIN_WR    GPIO_PIN_8


void HwLcdInit();
//Подождать несколько милисекунд
void DelaySome();

//Управление пинами 0 - low, 1 - high
void HwLcdPinCE(uint8_t on);
void HwLcdPinDC(uint8_t on);
void HwLcdPinRst(uint8_t on);
void HwLcdPinLed(uint8_t on);
uint8_t HwLcdSend(uint8_t data); //send spi data

//void HwLcdSend16NoWait(uint16_t data);
void HwLcdWait();//Wait send complete


void HwLcdSend16NoWaitAsm(uint16_t data);
//#define HwLcdSend16NoWait(x) HwLcdSend16NoWaitAsm(x)

__attribute__((always_inline))
inline void HwLcdSend16NoWait(uint16_t data)
{
    TFT_DATA_PORT->ODR = data;
    TFT_PORT_WR->BSRR = (uint32_t)PIN_WR << 16;
    //__asm__ volatile("mov r0, r0");
    TFT_PORT_WR->BSRR = (uint32_t)PIN_WR;
}


#define  HwLcdWait() (void)0

#endif//DISPLAY_ILI9481
