################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/portable/CCS/ARM_CM4F/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O3 --opt_for_speed=0 --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/TivaWARE" --include_path="E:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/include" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/portable/MemMang" --include_path="E:/SHELL/Shell_ECO_2020/Electrical_control_CCS_Template - Copy" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/portable/CCS/ARM_CM4F/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O3 --opt_for_speed=0 --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/TivaWARE" --include_path="E:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/include" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="E:/SHELL/Shell_ECO_2020/STEERING_TEMPLATE/FreeRTOS/portable/MemMang" --include_path="E:/SHELL/Shell_ECO_2020/Electrical_control_CCS_Template - Copy" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


