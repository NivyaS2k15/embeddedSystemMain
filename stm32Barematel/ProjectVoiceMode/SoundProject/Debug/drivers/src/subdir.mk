################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/fonts.c \
../drivers/src/lcd.c \
../drivers/src/ssd1306.c \
../drivers/src/stm32f446xx_gpio_driver.c \
../drivers/src/stm32f446xx_i2c_driver.c \
../drivers/src/stm32f446xx_rcc_driver.c \
../drivers/src/stm32f446xx_spi_driver.c \
../drivers/src/stm32f446xx_usart_driver.c 

OBJS += \
./drivers/src/fonts.o \
./drivers/src/lcd.o \
./drivers/src/ssd1306.o \
./drivers/src/stm32f446xx_gpio_driver.o \
./drivers/src/stm32f446xx_i2c_driver.o \
./drivers/src/stm32f446xx_rcc_driver.o \
./drivers/src/stm32f446xx_spi_driver.o \
./drivers/src/stm32f446xx_usart_driver.o 

C_DEPS += \
./drivers/src/fonts.d \
./drivers/src/lcd.d \
./drivers/src/ssd1306.d \
./drivers/src/stm32f446xx_gpio_driver.d \
./drivers/src/stm32f446xx_i2c_driver.d \
./drivers/src/stm32f446xx_rcc_driver.d \
./drivers/src/stm32f446xx_spi_driver.d \
./drivers/src/stm32f446xx_usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/embeddedSystem/stm32Barematel/ProjectVoiceMode/SoundProject/drivers/inc" -I"C:/embeddedSystem/stm32Barematel/ProjectVoiceMode/SoundProject/drivers/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/fonts.cyclo ./drivers/src/fonts.d ./drivers/src/fonts.o ./drivers/src/fonts.su ./drivers/src/lcd.cyclo ./drivers/src/lcd.d ./drivers/src/lcd.o ./drivers/src/lcd.su ./drivers/src/ssd1306.cyclo ./drivers/src/ssd1306.d ./drivers/src/ssd1306.o ./drivers/src/ssd1306.su ./drivers/src/stm32f446xx_gpio_driver.cyclo ./drivers/src/stm32f446xx_gpio_driver.d ./drivers/src/stm32f446xx_gpio_driver.o ./drivers/src/stm32f446xx_gpio_driver.su ./drivers/src/stm32f446xx_i2c_driver.cyclo ./drivers/src/stm32f446xx_i2c_driver.d ./drivers/src/stm32f446xx_i2c_driver.o ./drivers/src/stm32f446xx_i2c_driver.su ./drivers/src/stm32f446xx_rcc_driver.cyclo ./drivers/src/stm32f446xx_rcc_driver.d ./drivers/src/stm32f446xx_rcc_driver.o ./drivers/src/stm32f446xx_rcc_driver.su ./drivers/src/stm32f446xx_spi_driver.cyclo ./drivers/src/stm32f446xx_spi_driver.d ./drivers/src/stm32f446xx_spi_driver.o ./drivers/src/stm32f446xx_spi_driver.su ./drivers/src/stm32f446xx_usart_driver.cyclo ./drivers/src/stm32f446xx_usart_driver.d ./drivers/src/stm32f446xx_usart_driver.o ./drivers/src/stm32f446xx_usart_driver.su

.PHONY: clean-drivers-2f-src

