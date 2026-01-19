################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/lcd.c \
../drivers/src/stm32f446xx_gpio_driver.c \
../drivers/src/stm32f446xx_rcc_driver.c 

OBJS += \
./drivers/src/lcd.o \
./drivers/src/stm32f446xx_gpio_driver.o \
./drivers/src/stm32f446xx_rcc_driver.o 

C_DEPS += \
./drivers/src/lcd.d \
./drivers/src/stm32f446xx_gpio_driver.d \
./drivers/src/stm32f446xx_rcc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/embeddedSystem/stm32Barematel/SLOTCAR/SLOTCARR/drivers/inc" -I"C:/embeddedSystem/stm32Barematel/SLOTCAR/SLOTCARR/drivers/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/lcd.cyclo ./drivers/src/lcd.d ./drivers/src/lcd.o ./drivers/src/lcd.su ./drivers/src/stm32f446xx_gpio_driver.cyclo ./drivers/src/stm32f446xx_gpio_driver.d ./drivers/src/stm32f446xx_gpio_driver.o ./drivers/src/stm32f446xx_gpio_driver.su ./drivers/src/stm32f446xx_rcc_driver.cyclo ./drivers/src/stm32f446xx_rcc_driver.d ./drivers/src/stm32f446xx_rcc_driver.o ./drivers/src/stm32f446xx_rcc_driver.su

.PHONY: clean-drivers-2f-src

