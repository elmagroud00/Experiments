################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: tvplayer

dependents:
	-cd /home/sijiewang/MyDisk/Projects/eclipse-workspace/mx_cane/Debug && $(MAKE) clean all
	-cd /home/sijiewang/MyDisk/Projects/eclipse-workspace/mxcommon/Debug && $(MAKE) clean all

# Tool invocations
tvplayer: $(OBJS) $(USER_OBJS) /home/sijiewang/MyDisk/Projects/eclipse-workspace/mx_cane/Debug/libmx_cane.so /home/sijiewang/MyDisk/Projects/eclipse-workspace/mxcommon/Debug/libmxcommon.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/sijiewang/MyDisk/Projects/eclipse-workspace/mxcommon/Debug" -L"/home/sijiewang/MyDisk/Projects/eclipse-workspace/mx_cane/Debug" -o "tvplayer" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) tvplayer
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/sijiewang/MyDisk/Projects/eclipse-workspace/mx_cane/Debug/libmx_cane.so:
/home/sijiewang/MyDisk/Projects/eclipse-workspace/mxcommon/Debug/libmxcommon.so:

-include ../makefile.targets
