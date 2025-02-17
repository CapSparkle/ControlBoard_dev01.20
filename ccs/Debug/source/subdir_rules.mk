################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/ApFilter3.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/source/ApFilter3.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/interface.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/source/interface.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/main.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/source/main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/system_init.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/source/system_init.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


