################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/snake_game/board.c \
../Core/Src/snake_game/fruit.c \
../Core/Src/snake_game/snake.c 

OBJS += \
./Core/Src/snake_game/board.o \
./Core/Src/snake_game/fruit.o \
./Core/Src/snake_game/snake.o 

C_DEPS += \
./Core/Src/snake_game/board.d \
./Core/Src/snake_game/fruit.d \
./Core/Src/snake_game/snake.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/snake_game/%.o Core/Src/snake_game/%.su Core/Src/snake_game/%.cyclo: ../Core/Src/snake_game/%.c Core/Src/snake_game/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-snake_game

clean-Core-2f-Src-2f-snake_game:
	-$(RM) ./Core/Src/snake_game/board.cyclo ./Core/Src/snake_game/board.d ./Core/Src/snake_game/board.o ./Core/Src/snake_game/board.su ./Core/Src/snake_game/fruit.cyclo ./Core/Src/snake_game/fruit.d ./Core/Src/snake_game/fruit.o ./Core/Src/snake_game/fruit.su ./Core/Src/snake_game/snake.cyclo ./Core/Src/snake_game/snake.d ./Core/Src/snake_game/snake.o ./Core/Src/snake_game/snake.su

.PHONY: clean-Core-2f-Src-2f-snake_game

