################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/gr_sakura_libs/InstWire.cpp 

OBJS += \
./src/gr_sakura_libs/InstWire.o 

CPP_DEPS += \
./src/gr_sakura_libs/InstWire.d 


# Each subdirectory must supply rules for building sources it contributes
src/gr_sakura_libs/%.o: ../src/gr_sakura_libs/%.cpp
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF ""$(@:%.o=%.d)"" -MT"$(@:%.o=%.o)" -MT""$(@:%.o=%.d)"" @"src/gr_sakura_libs/cpp.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -x c++  -w -Wno-analyze -nostdinc -fsigned-char -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\include\rxduino" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\include\tkdnhal" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_sakura_libs" -I"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/lib/gcc/rx-elf/4.8-GNURX_v14.03/include" -I"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/rx-elf/include" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common" -D__RX_LITTLE_ENDIAN__=1 -O2 -g2 -g -mlittle-endian-data -mcpu=rx600 "$<"
	@rx-elf-gcc  @"src/gr_sakura_libs/cpp.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c++  -w -Wno-analyze -nostdinc -fsigned-char -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\include\rxduino" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common\include\tkdnhal" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_sakura_libs" -I"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/lib/gcc/rx-elf/4.8-GNURX_v14.03/include" -I"C:\PROGRA~1\KPIT\GNURXV~1.03-\rx-ELF\rx-ELF/rx-elf/include" -I"D:\DESARROLLOS\sakura_sketch_v108_e2studio\sakura_sketch_v108_e2studio\src\gr_common" -D__RX_LITTLE_ENDIAN__=1 -O2 -g2 -g -mlittle-endian-data -mcpu=rx600 -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

