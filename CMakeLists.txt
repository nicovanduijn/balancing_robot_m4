cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
enable_language(CXX C ASM)
project(balancing_robot C CXX ASM)

include_directories(
    ${CMAKE_SOURCE_DIR} 
    extern/rtos/include 
    ${FREERTOS_CONFIG} 
    ${FREERTOS_PORT_DIR})

add_subdirectory(common)
add_subdirectory(${PLATFORM_DIR})

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${FREERTOS_CONFIG})
add_subdirectory(extern/rtos)