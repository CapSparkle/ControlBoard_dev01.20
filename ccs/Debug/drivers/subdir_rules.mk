################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/ads1256.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/ads1256.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/adt75.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/adt75.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/drv_at24x.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/drv_at24x.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/lir_da158a_02.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/lir_da158a_02.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/netcomm.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/netcomm.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/netcrc.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/netcrc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/netwrapper.obj: C:/Users/Fesko/source/ControlBoard_dev01.20/drivers/netwrapper.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt -Ooff --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="../../f2802x_common/include" --include_path="../../f2802x_headers/include" --include_path="../../drivers" --include_path="../../source" --advice:performance=all --define=SYSCLK=15000000 --define=CLKIN=30000000 --define=UPD_FREQ=250 --define=RS_SPEED=115200 --define=LARGE_MODEL --define=FLASH_PROJ -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


