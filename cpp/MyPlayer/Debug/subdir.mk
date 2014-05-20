################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DecoderThread.cpp \
../LoadImage.cpp \
../Thread.cpp \
../VdpauContext.cpp \
../VdpauDecoderContext.cpp \
../VdpauDisplayContext.cpp \
../main.cpp \
../util.cpp 

OBJS += \
./DecoderThread.o \
./LoadImage.o \
./Thread.o \
./VdpauContext.o \
./VdpauDecoderContext.o \
./VdpauDisplayContext.o \
./main.o \
./util.o 

CPP_DEPS += \
./DecoderThread.d \
./LoadImage.d \
./Thread.d \
./VdpauContext.d \
./VdpauDecoderContext.d \
./VdpauDisplayContext.d \
./main.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D__STDC_CONSTANT_MACROS -I/usr/local/include -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


