################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
f2802x_common/f2802x_adc.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_adc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_codestartbranch.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_codestartbranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_cputimers.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_cputimers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_defaultisr.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_defaultisr.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_gpio.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_gpio.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_i2c.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_i2c.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_piectrl.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_piectrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_pievect.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_pievect.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_sci.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_sci.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_spi.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_spi.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_sysctrl.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_sysctrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_tempsensorconv.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_tempsensorconv.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f2802x_common/f2802x_usdelay.obj: C:/Users/Public/Desktop/ISS/ControlBoard_dev01.20/f2802x_common/source/f2802x_usdelay.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=90000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="f2802x_common/$(basename $(<F)).d_raw" --obj_directory="f2802x_common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


