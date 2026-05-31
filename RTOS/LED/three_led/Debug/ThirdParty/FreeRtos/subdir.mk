################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRtos/croutine.c \
../ThirdParty/FreeRtos/event_groups.c \
../ThirdParty/FreeRtos/list.c \
../ThirdParty/FreeRtos/queue.c \
../ThirdParty/FreeRtos/stream_buffer.c \
../ThirdParty/FreeRtos/tasks.c \
../ThirdParty/FreeRtos/timers.c 

OBJS += \
./ThirdParty/FreeRtos/croutine.o \
./ThirdParty/FreeRtos/event_groups.o \
./ThirdParty/FreeRtos/list.o \
./ThirdParty/FreeRtos/queue.o \
./ThirdParty/FreeRtos/stream_buffer.o \
./ThirdParty/FreeRtos/tasks.o \
./ThirdParty/FreeRtos/timers.o 

C_DEPS += \
./ThirdParty/FreeRtos/croutine.d \
./ThirdParty/FreeRtos/event_groups.d \
./ThirdParty/FreeRtos/list.d \
./ThirdParty/FreeRtos/queue.d \
./ThirdParty/FreeRtos/stream_buffer.d \
./ThirdParty/FreeRtos/tasks.d \
./ThirdParty/FreeRtos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRtos/%.o ThirdParty/FreeRtos/%.su ThirdParty/FreeRtos/%.cyclo: ../ThirdParty/FreeRtos/%.c ThirdParty/FreeRtos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/embeddedSystem/RTOS/LED/three_led/ThirdParty/FreeRtos" -I"C:/embeddedSystem/RTOS/LED/three_led/ThirdParty/FreeRtos/include" -I"C:/embeddedSystem/RTOS/LED/three_led/ThirdParty/FreeRtos/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-FreeRtos

clean-ThirdParty-2f-FreeRtos:
	-$(RM) ./ThirdParty/FreeRtos/croutine.cyclo ./ThirdParty/FreeRtos/croutine.d ./ThirdParty/FreeRtos/croutine.o ./ThirdParty/FreeRtos/croutine.su ./ThirdParty/FreeRtos/event_groups.cyclo ./ThirdParty/FreeRtos/event_groups.d ./ThirdParty/FreeRtos/event_groups.o ./ThirdParty/FreeRtos/event_groups.su ./ThirdParty/FreeRtos/list.cyclo ./ThirdParty/FreeRtos/list.d ./ThirdParty/FreeRtos/list.o ./ThirdParty/FreeRtos/list.su ./ThirdParty/FreeRtos/queue.cyclo ./ThirdParty/FreeRtos/queue.d ./ThirdParty/FreeRtos/queue.o ./ThirdParty/FreeRtos/queue.su ./ThirdParty/FreeRtos/stream_buffer.cyclo ./ThirdParty/FreeRtos/stream_buffer.d ./ThirdParty/FreeRtos/stream_buffer.o ./ThirdParty/FreeRtos/stream_buffer.su ./ThirdParty/FreeRtos/tasks.cyclo ./ThirdParty/FreeRtos/tasks.d ./ThirdParty/FreeRtos/tasks.o ./ThirdParty/FreeRtos/tasks.su ./ThirdParty/FreeRtos/timers.cyclo ./ThirdParty/FreeRtos/timers.d ./ThirdParty/FreeRtos/timers.o ./ThirdParty/FreeRtos/timers.su

.PHONY: clean-ThirdParty-2f-FreeRtos

