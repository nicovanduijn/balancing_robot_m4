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

target_sources(stm32mp1_hal INTERFACE
    ../../generated/CM4/Src/dma.c    
    ../../generated/CM4/Src/gpio.c
    ../../generated/CM4/Src/main.c
    ../../generated/CM4/Src/ipcc.c
    ../../generated/CM4/Src/mbox_ipcc.c
    ../../generated/CM4/Src/openamp_log.c
    ../../generated/CM4/Src/openamp.c
    ../../generated/CM4/Src/rsc_table.c
    ../../generated/CM4/Src/stm32mp1xx_hal_msp.c
    ../../generated/CM4/Src/stm32mp1xx_it.c
    ../../generated/CM4/Src/syscalls.c
    ../../generated/CM4/Src/sysmem.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_cortex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_dma_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_dma.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_exti.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_gpio.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_hsem.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_ipcc.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_mdma.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_pwr_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_pwr.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_rcc_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_rcc.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_tim_ex.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal_tim.c
    ../../generated/Drivers/STM32MP1xx_HAL_Driver/Src/stm32mp1xx_hal.c
    ../../generated/Common/System/system_stm32mp1xx.c
    ../../generated/CM4/Startup/startup_stm32mp157facx.s
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.c
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/remoteproc/remoteproc_virtio.c
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg/rpmsg_virtio.c
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg/rpmsg.c
    ../../generated/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/generic_io.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/template/sys.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/device.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/init.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/io.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/log.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/shmem.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/condition.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/generic_device.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/generic_init.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/generic_io.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/generic_shmem.c
    ../../generated/Middlewares/Third_Party/OpenAMP/libmetal/lib/system/generic/time.c
)

target_link_directories(stm32mp1_hal INTERFACE
)

target_link_libraries(stm32mp1_hal INTERFACE )

# Validate that STM32mp1_hal code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


