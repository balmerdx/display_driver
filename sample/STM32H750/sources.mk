################################################################################
# Automatically-generated file. Do not edit!
################################################################################


DEPS += \
	output/base/Src/main.d \
	output/base/Src/stm32h7xx_hal_msp.d \
	output/base/Src/stm32h7xx_it.d \
	output/base/Src/system_stm32h7xx.d \
	output/base/Src/hardware/delay.d \
	output/base/Src/hardware/hw_ili9341.d \
	output/base/Src/hardware/hw_ili9481.d \
	output/base/Src/hardware/quadrature_encoder.d \
	output/base/__/__/display/UTFT.d \
	output/base/__/__/display/float_to_string.d \
	output/base/__/__/display/utf_font.d \
	output/base/__/__/display/fonts/DefaultFonts.d \
	output/base/__/__/display/fonts/font_condensed30.d \
	output/base/__/__/display/fonts/font_condensed59.d \
	output/base/USB_DEVICE/App/usb_device.d \
	output/base/USB_DEVICE/App/usbd_cdc_if.d \
	output/base/USB_DEVICE/App/usbd_desc.d \
	output/base/USB_DEVICE/Target/usbd_conf.d \
	output/base/startup_stm32h750xx.d \
	output/usb/usbd_core.d \
	output/usb/usbd_ctlreq.d \
	output/usb/usbd_ioreq.d \
	output/usb_cdc/usbd_cdc.d \
	output/hal/stm32h7xx_hal_pcd.d \
	output/hal/stm32h7xx_hal_pcd_ex.d \
	output/hal/stm32h7xx_ll_usb.d \
	output/hal/stm32h7xx_hal_rcc.d \
	output/hal/stm32h7xx_hal_rcc_ex.d \
	output/hal/stm32h7xx_hal_gpio.d \
	output/hal/stm32h7xx_hal_hsem.d \
	output/hal/stm32h7xx_hal_pwr.d \
	output/hal/stm32h7xx_hal_pwr_ex.d \
	output/hal/stm32h7xx_hal_cortex.d \
	output/hal/stm32h7xx_hal.d \
	output/hal/stm32h7xx_hal_exti.d \
	output/hal/stm32h7xx_hal_tim.d \
	output/hal/stm32h7xx_hal_tim_ex.d \


OBJS += \
	output/base/Src/main.o \
	output/base/Src/stm32h7xx_hal_msp.o \
	output/base/Src/stm32h7xx_it.o \
	output/base/Src/system_stm32h7xx.o \
	output/base/Src/hardware/delay.o \
	output/base/Src/hardware/hw_ili9341.o \
	output/base/Src/hardware/hw_ili9481.o \
	output/base/Src/hardware/quadrature_encoder.o \
	output/base/__/__/display/UTFT.o \
	output/base/__/__/display/float_to_string.o \
	output/base/__/__/display/utf_font.o \
	output/base/__/__/display/fonts/DefaultFonts.o \
	output/base/__/__/display/fonts/font_condensed30.o \
	output/base/__/__/display/fonts/font_condensed59.o \
	output/base/USB_DEVICE/App/usb_device.o \
	output/base/USB_DEVICE/App/usbd_cdc_if.o \
	output/base/USB_DEVICE/App/usbd_desc.o \
	output/base/USB_DEVICE/Target/usbd_conf.o \
	output/base/startup_stm32h750xx.o \
	output/usb/usbd_core.o \
	output/usb/usbd_ctlreq.o \
	output/usb/usbd_ioreq.o \
	output/usb_cdc/usbd_cdc.o \
	output/hal/stm32h7xx_hal_pcd.o \
	output/hal/stm32h7xx_hal_pcd_ex.o \
	output/hal/stm32h7xx_ll_usb.o \
	output/hal/stm32h7xx_hal_rcc.o \
	output/hal/stm32h7xx_hal_rcc_ex.o \
	output/hal/stm32h7xx_hal_gpio.o \
	output/hal/stm32h7xx_hal_hsem.o \
	output/hal/stm32h7xx_hal_pwr.o \
	output/hal/stm32h7xx_hal_pwr_ex.o \
	output/hal/stm32h7xx_hal_cortex.o \
	output/hal/stm32h7xx_hal.o \
	output/hal/stm32h7xx_hal_exti.o \
	output/hal/stm32h7xx_hal_tim.o \
	output/hal/stm32h7xx_hal_tim_ex.o \


output/base/Src/main.o: ./Src/main.c
	@echo 'Building target: main.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/stm32h7xx_hal_msp.o: ./Src/stm32h7xx_hal_msp.c
	@echo 'Building target: stm32h7xx_hal_msp.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/stm32h7xx_it.o: ./Src/stm32h7xx_it.c
	@echo 'Building target: stm32h7xx_it.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/system_stm32h7xx.o: ./Src/system_stm32h7xx.c
	@echo 'Building target: system_stm32h7xx.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/hardware/delay.o: ./Src/hardware/delay.c
	@echo 'Building target: delay.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/hardware/hw_ili9341.o: ./Src/hardware/hw_ili9341.c
	@echo 'Building target: hw_ili9341.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/hardware/hw_ili9481.o: ./Src/hardware/hw_ili9481.c
	@echo 'Building target: hw_ili9481.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/Src/hardware/quadrature_encoder.o: ./Src/hardware/quadrature_encoder.c
	@echo 'Building target: quadrature_encoder.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/UTFT.o: ./../../display/UTFT.c
	@echo 'Building target: UTFT.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/float_to_string.o: ./../../display/float_to_string.c
	@echo 'Building target: float_to_string.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/utf_font.o: ./../../display/utf_font.c
	@echo 'Building target: utf_font.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/fonts/DefaultFonts.o: ./../../display/fonts/DefaultFonts.c
	@echo 'Building target: DefaultFonts.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/fonts/font_condensed30.o: ./../../display/fonts/font_condensed30.c
	@echo 'Building target: font_condensed30.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/__/__/display/fonts/font_condensed59.o: ./../../display/fonts/font_condensed59.c
	@echo 'Building target: font_condensed59.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/USB_DEVICE/App/usb_device.o: ./USB_DEVICE/App/usb_device.c
	@echo 'Building target: usb_device.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/USB_DEVICE/App/usbd_cdc_if.o: ./USB_DEVICE/App/usbd_cdc_if.c
	@echo 'Building target: usbd_cdc_if.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/USB_DEVICE/App/usbd_desc.o: ./USB_DEVICE/App/usbd_desc.c
	@echo 'Building target: usbd_desc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/USB_DEVICE/Target/usbd_conf.o: ./USB_DEVICE/Target/usbd_conf.c
	@echo 'Building target: usbd_conf.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/startup_stm32h750xx.o: ./startup_stm32h750xx.s
	@echo 'Building target: startup_stm32h750xx.s'
	@$(CC) $(ASM_FLAGS) -o "$@" "$<"

output/usb/usbd_core.o: Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
	@echo 'Building target: usbd_core.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/usbd_ctlreq.o: Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
	@echo 'Building target: usbd_ctlreq.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/usbd_ioreq.o: Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
	@echo 'Building target: usbd_ioreq.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb_cdc/usbd_cdc.o: Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
	@echo 'Building target: usbd_cdc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_pcd.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c
	@echo 'Building target: stm32h7xx_hal_pcd.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_pcd_ex.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c
	@echo 'Building target: stm32h7xx_hal_pcd_ex.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_ll_usb.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
	@echo 'Building target: stm32h7xx_ll_usb.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_rcc.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
	@echo 'Building target: stm32h7xx_hal_rcc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_rcc_ex.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
	@echo 'Building target: stm32h7xx_hal_rcc_ex.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_gpio.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
	@echo 'Building target: stm32h7xx_hal_gpio.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_hsem.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
	@echo 'Building target: stm32h7xx_hal_hsem.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_pwr.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
	@echo 'Building target: stm32h7xx_hal_pwr.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_pwr_ex.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
	@echo 'Building target: stm32h7xx_hal_pwr_ex.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_cortex.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
	@echo 'Building target: stm32h7xx_hal_cortex.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
	@echo 'Building target: stm32h7xx_hal.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_exti.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
	@echo 'Building target: stm32h7xx_hal_exti.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_tim.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
	@echo 'Building target: stm32h7xx_hal_tim.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/hal/stm32h7xx_hal_tim_ex.o: Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
	@echo 'Building target: stm32h7xx_hal_tim_ex.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"



