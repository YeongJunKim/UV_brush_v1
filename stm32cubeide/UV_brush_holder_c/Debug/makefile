################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
UV_brush_holder_c.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
UV_brush_holder_c.list \


# All Target
all: UV_brush_holder_c.elf secondary-outputs

# Tool invocations
UV_brush_holder_c.elf: $(OBJS) $(USER_OBJS) C:\Users\colson\Desktop\workspace\UV_brush_v1\stm32cubeide\UV_brush_holder_c\STM32L031F4PX_FLASH.ld
	arm-none-eabi-gcc -o "UV_brush_holder_c.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\colson\Desktop\workspace\UV_brush_v1\stm32cubeide\UV_brush_holder_c\STM32L031F4PX_FLASH.ld" --specs=nosys.specs -Wl,-Map="UV_brush_holder_c.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

UV_brush_holder_c.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "UV_brush_holder_c.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
