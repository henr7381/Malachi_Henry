################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Repo/Cheka_adc.cpp \
../Core/Repo/DataStore.cpp \
../Core/Repo/Display.cpp \
../Core/Repo/Edgedetector.cpp \
../Core/Repo/KnobFSM.cpp \
../Core/Repo/Mal_queue.cpp \
../Core/Repo/PeriodUpdate.cpp \
../Core/Repo/Ram_Health.cpp \
../Core/Repo/RawToPixel.cpp \
../Core/Repo/Sean_queue.cpp \
../Core/Repo/TriggerUpdate.cpp \
../Core/Repo/cpp_main.cpp 

OBJS += \
./Core/Repo/Cheka_adc.o \
./Core/Repo/DataStore.o \
./Core/Repo/Display.o \
./Core/Repo/Edgedetector.o \
./Core/Repo/KnobFSM.o \
./Core/Repo/Mal_queue.o \
./Core/Repo/PeriodUpdate.o \
./Core/Repo/Ram_Health.o \
./Core/Repo/RawToPixel.o \
./Core/Repo/Sean_queue.o \
./Core/Repo/TriggerUpdate.o \
./Core/Repo/cpp_main.o 

CPP_DEPS += \
./Core/Repo/Cheka_adc.d \
./Core/Repo/DataStore.d \
./Core/Repo/Display.d \
./Core/Repo/Edgedetector.d \
./Core/Repo/KnobFSM.d \
./Core/Repo/Mal_queue.d \
./Core/Repo/PeriodUpdate.d \
./Core/Repo/Ram_Health.d \
./Core/Repo/RawToPixel.d \
./Core/Repo/Sean_queue.d \
./Core/Repo/TriggerUpdate.d \
./Core/Repo/cpp_main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Repo/%.o Core/Repo/%.su Core/Repo/%.cyclo: ../Core/Repo/%.cpp Core/Repo/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=c++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Repo

clean-Core-2f-Repo:
	-$(RM) ./Core/Repo/Cheka_adc.cyclo ./Core/Repo/Cheka_adc.d ./Core/Repo/Cheka_adc.o ./Core/Repo/Cheka_adc.su ./Core/Repo/DataStore.cyclo ./Core/Repo/DataStore.d ./Core/Repo/DataStore.o ./Core/Repo/DataStore.su ./Core/Repo/Display.cyclo ./Core/Repo/Display.d ./Core/Repo/Display.o ./Core/Repo/Display.su ./Core/Repo/Edgedetector.cyclo ./Core/Repo/Edgedetector.d ./Core/Repo/Edgedetector.o ./Core/Repo/Edgedetector.su ./Core/Repo/KnobFSM.cyclo ./Core/Repo/KnobFSM.d ./Core/Repo/KnobFSM.o ./Core/Repo/KnobFSM.su ./Core/Repo/Mal_queue.cyclo ./Core/Repo/Mal_queue.d ./Core/Repo/Mal_queue.o ./Core/Repo/Mal_queue.su ./Core/Repo/PeriodUpdate.cyclo ./Core/Repo/PeriodUpdate.d ./Core/Repo/PeriodUpdate.o ./Core/Repo/PeriodUpdate.su ./Core/Repo/Ram_Health.cyclo ./Core/Repo/Ram_Health.d ./Core/Repo/Ram_Health.o ./Core/Repo/Ram_Health.su ./Core/Repo/RawToPixel.cyclo ./Core/Repo/RawToPixel.d ./Core/Repo/RawToPixel.o ./Core/Repo/RawToPixel.su ./Core/Repo/Sean_queue.cyclo ./Core/Repo/Sean_queue.d ./Core/Repo/Sean_queue.o ./Core/Repo/Sean_queue.su ./Core/Repo/TriggerUpdate.cyclo ./Core/Repo/TriggerUpdate.d ./Core/Repo/TriggerUpdate.o ./Core/Repo/TriggerUpdate.su ./Core/Repo/cpp_main.cyclo ./Core/Repo/cpp_main.d ./Core/Repo/cpp_main.o ./Core/Repo/cpp_main.su

.PHONY: clean-Core-2f-Repo

