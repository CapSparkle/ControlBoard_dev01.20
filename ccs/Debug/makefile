################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./drivers/ads1256.obj" \
"./drivers/adt75.obj" \
"./drivers/drv_at24x.obj" \
"./drivers/lir_da158a_02.obj" \
"./drivers/netcomm.obj" \
"./drivers/netcrc.obj" \
"./drivers/netwrapper.obj" \
"./f2802x_common/f2802x_adc.obj" \
"./f2802x_common/f2802x_codestartbranch.obj" \
"./f2802x_common/f2802x_cputimers.obj" \
"./f2802x_common/f2802x_defaultisr.obj" \
"./f2802x_common/f2802x_gpio.obj" \
"./f2802x_common/f2802x_i2c.obj" \
"./f2802x_common/f2802x_piectrl.obj" \
"./f2802x_common/f2802x_pievect.obj" \
"./f2802x_common/f2802x_sci.obj" \
"./f2802x_common/f2802x_spi.obj" \
"./f2802x_common/f2802x_sysctrl.obj" \
"./f2802x_common/f2802x_tempsensorconv.obj" \
"./f2802x_common/f2802x_usdelay.obj" \
"./f2802x_headers/F2802x_GlobalVariableDefs.obj" \
"./source/ApFilter3.obj" \
"./source/interface.obj" \
"./source/main.obj" \
"./source/system_init.obj" \
"C:/Users/Fesko/source/ControlBoard_dev01.20/f2802x_common/cmd/F28022_ControlBoard.cmd" \
"C:/Users/Fesko/source/ControlBoard_dev01.20/f2802x_headers/cmd/F2802x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-lIQmath.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include drivers/subdir_vars.mk
-include f2802x_common/subdir_vars.mk
-include f2802x_headers/subdir_vars.mk
-include source/subdir_vars.mk
-include drivers/subdir_rules.mk
-include f2802x_common/subdir_rules.mk
-include f2802x_headers/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ControlBoard.out \

EXE_OUTPUTS__QUOTED += \
"ControlBoard.out" \


# All Target
all: ControlBoard.out

# Tool invocations
ControlBoard.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi -z -m"ControlBoard.map" --heap_size=0x0 --stack_size=0x3B0 --warn_sections -i"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -i"../../lib" --reread_libs --diag_suppress=16002 --diag_wrap=off --display_error_number --xml_link_info="ControlBoard_linkInfo.xml" --rom_model -o "ControlBoard.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "drivers\ads1256.obj" "drivers\adt75.obj" "drivers\drv_at24x.obj" "drivers\lir_da158a_02.obj" "drivers\netcomm.obj" "drivers\netcrc.obj" "drivers\netwrapper.obj" "f2802x_common\f2802x_adc.obj" "f2802x_common\f2802x_codestartbranch.obj" "f2802x_common\f2802x_cputimers.obj" "f2802x_common\f2802x_defaultisr.obj" "f2802x_common\f2802x_gpio.obj" "f2802x_common\f2802x_i2c.obj" "f2802x_common\f2802x_piectrl.obj" "f2802x_common\f2802x_pievect.obj" "f2802x_common\f2802x_sci.obj" "f2802x_common\f2802x_spi.obj" "f2802x_common\f2802x_sysctrl.obj" "f2802x_common\f2802x_tempsensorconv.obj" "f2802x_common\f2802x_usdelay.obj" "f2802x_headers\F2802x_GlobalVariableDefs.obj" "source\ApFilter3.obj" "source\interface.obj" "source\main.obj" "source\system_init.obj" 
	-$(RM) "drivers\ads1256.d" "drivers\adt75.d" "drivers\drv_at24x.d" "drivers\lir_da158a_02.d" "drivers\netcomm.d" "drivers\netcrc.d" "drivers\netwrapper.d" "f2802x_common\f2802x_adc.d" "f2802x_common\f2802x_cputimers.d" "f2802x_common\f2802x_defaultisr.d" "f2802x_common\f2802x_gpio.d" "f2802x_common\f2802x_i2c.d" "f2802x_common\f2802x_piectrl.d" "f2802x_common\f2802x_pievect.d" "f2802x_common\f2802x_sci.d" "f2802x_common\f2802x_spi.d" "f2802x_common\f2802x_sysctrl.d" "f2802x_common\f2802x_tempsensorconv.d" "f2802x_headers\F2802x_GlobalVariableDefs.d" "source\ApFilter3.d" "source\interface.d" "source\main.d" "source\system_init.d" 
	-$(RM) "f2802x_common\f2802x_codestartbranch.d" "f2802x_common\f2802x_usdelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

