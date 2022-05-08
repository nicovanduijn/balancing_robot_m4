cmake_minimum_required(VERSION 3.22)

project(stm32mp1_hal)
add_library(stm32mp1_hal INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32mp1_hal INTERFACE 
    CORE_CM4
	USE_HAL_DRIVER 
    STM32MP157Fxx
	STM32_THREAD_SAFE_STRATEGY=5
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32mp1_hal INTERFACE
    ../../generated/CM4/Inc
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Inc
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy
    ../../generated/Drivers/CMSIS/Device/ST/STM32MP1xx/Include
    ../../generated/Drivers/CMSIS/Include
)

target_sources(stm32mp1_hal INTERFACE
    ../../generated/CM4/Src/main.c
    ../../generated/CM4/Src/gpio.c
    ../../generated/CM4/Src/stm32mp1xx_it.c
    ../../generated/CM4/Src/stm32mp1xx_hal_msp.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_cortex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_dma_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_dma.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_exti.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_gpio.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_hsem.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_mdma.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_pwr_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_pwr.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_rcc_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_rcc.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_tim_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_tim.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal.c
    ../../generated/Common/System/system_stm32mp1xx.c
    ../../generated/CM4/Src/sysmem.c
    ../../generated/CM4/Src/syscalls.c
    ../../generated/CM4/Startup/startup_stm32mp157facx.s
)

target_link_directories(stm32mp1_hal INTERFACE
)

target_link_libraries(stm32mp1_hal INTERFACE
)

# Validate that STM32mp1_hal code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


