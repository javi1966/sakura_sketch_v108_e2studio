################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include src/gr_sakura_libs/subdir.mk
-include src/gr_common/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_OUTPUT_OUTPUTS += \
sakura_sketch_v108_e2studio.x \


# All Target
# Main-build Target
all: sakura_sketch_v108_e2studio.mot
	@echo 'Build complete.'

# Tool invocations
sakura_sketch_v108_e2studio.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Objcopy'
	rx-elf-objcopy -O srec -I elf32-rx-be-ns  $(LINKER_OUTPUT_OUTPUTS)"sakura_sketch_v108_e2studio.mot"
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

sakura_sketch_v108_e2studio.x: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS)
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rx-elf-ld -o "sakura_sketch_v108_e2studio.x" -T"D:/DESARROLLOS/sakura_sketch_v108_e2studio/sakura_sketch_v108_e2studio\Sketch\LinkerSubCommand.tmp" -T"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\gr_sakura.gsi" $(USER_OBJS) $(LIBS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) -M=sakura_sketch_v108_e2studio.map -L"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\lib" -L"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_sakura_libs" -L"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/rx-elf/lib" -L"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/lib/gcc/rx-elf//4.8-GNURX_v14.03" -L"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/lib/gcc/rx-elf/4.8-GNURX_v14.03" --start-group -lrxduino -lstdc++ -lsupc++ -lc -lsim -lgcc -lm -ltkdnhal -leeprom -lethernet -ltkdnip -lliquidcrystal -lsdmmc -lservo -lspi -lstepper -lusbhost -lwire --end-group --no-flag-mismatch-warnings
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS)$(OBJCOPY_OUTPUTTYPE_OUTPUTS)$(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)
	rm -rf ./"src"/*.o ./"src"/*.d 
	rm -rf ./"src/gr_sakura_libs"/*.o ./"src/gr_sakura_libs"/*.d 
	rm -rf ./"src/gr_common"/*.o ./"src/gr_common"/*.d  sakura_sketch_v108_e2studio.mot
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-rx-elf-objcopy -O binary "D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\Sketch\sakura_sketch_v108_e2studio.x"  sketch.bin
	@echo.

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
