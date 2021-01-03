#
# "base" - base directory
# "dirs" - directiry with sources, all source files in this directory added (without recursion)
# "files" - raw list of source files
# "output" - output path prefix

import sys
sys.path.insert(0, '/home/balmer/radio/stm32/projects/BalmerVNA/make_py')
import make_sources
import copy

QT_PROJECT_NAME = "test_display"

sources = [
{
	"base" : ".",
	"output" : "base",
	"dirs" : [
		"../../display",
		"../../display/fonts",
		"../../display/interface",
		"../tests",
		"Src",
		"Src/hardware",
		"USB_DEVICE/App",
		"USB_DEVICE/Target"
		],
	"files" : [
		"startup_stm32h750xx.s"
		]
},
{
	"base" : "Middlewares/ST/STM32_USB_Device_Library/Core/Src",
	"output" : "usb",
	"files" : [
		"usbd_core.c",
		"usbd_ctlreq.c",
		"usbd_ioreq.c",
		]

},
{
	"base" : "Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src",
	"output" : "usb_cdc",
	"files" : [
		"usbd_cdc.c",
		]

},
{
	"base" : "Drivers/STM32H7xx_HAL_Driver/Src",
	"output" : "hal",
	"files" : [
		"stm32h7xx_hal_pcd.c",
		"stm32h7xx_hal_pcd_ex.c",
		"stm32h7xx_ll_usb.c",
		"stm32h7xx_hal_rcc.c",
		"stm32h7xx_hal_rcc_ex.c",
		"stm32h7xx_hal_gpio.c",
		"stm32h7xx_hal_hsem.c",
		"stm32h7xx_hal_pwr.c",
		"stm32h7xx_hal_pwr_ex.c",
		"stm32h7xx_hal_cortex.c",
		"stm32h7xx_hal.c",
		"stm32h7xx_hal_exti.c",
		"stm32h7xx_hal_spi.c",
		"stm32h7xx_hal_tim.c",
		"stm32h7xx_hal_tim_ex.c",
		]

},
{
	"base" : "Drivers/STM32H7xx_HAL_Driver",
	"output" : "hal",
	"dirs" : [
		"Inc"
	]
},

]

if __name__ == "__main__":
	make_sources.makeProject(sources, QT_PROJECT_NAME)
