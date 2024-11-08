cmake_minimum_required(VERSION 3.22)

project(stm32mp1_hal)
add_library(stm32mp1_hal INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32mp1_hal INTERFACE 
    CORE_CM4
	USE_HAL_DRIVER 
    STM32MP157Fxx
    NO_ATOMIC_64_SUPPORT
    METAL_INTERNAL
    METAL_MAX_DEVICE_REGIONS=2
    VIRTIO_SLAVE_ONLY
	STM32_THREAD_SAFE_STRATEGY=5
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32mp1_hal INTERFACE
    ../../generated/CM4/Core/Inc
    ../../generated/CM4/OPENAMP
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Inc
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy
    ../../generated/Drivers/CMSIS/Device/ST/STM32MP1xx/Include
    ../../generated/Drivers/CMSIS/Include
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/include
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/include
)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../../generated/*.c")
list(FILTER SRCS EXCLUDE REGEX ".*/proxy/.*") # This file gets generated but not included in the build


target_sources(stm32mp1_hal INTERFACE
    ${SRCS}
    ../../generated/CM4/Core/Startup/startup_stm32mp157facx.s
)

target_link_directories(stm32mp1_hal INTERFACE
)

target_link_libraries(stm32mp1_hal INTERFACE )

# Validate that STM32mp1_hal code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


