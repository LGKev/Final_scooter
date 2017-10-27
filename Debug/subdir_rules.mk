################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.obj: ../Clock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Clock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Final_scooter.obj: ../Final_scooter.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Final_scooter.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

GPIO.obj: ../GPIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="GPIO.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Timer.obj: ../Timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Timer.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UART.obj: ../UART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="UART.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

adc_driver.obj: ../adc_driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="adc_driver.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

circ_buffer_basic.obj: ../circ_buffer_basic.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="circ_buffer_basic.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432p401r_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" --include_path="C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/kwat1/workspace_v7/Final_scooter" --include_path="C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432p401r.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


