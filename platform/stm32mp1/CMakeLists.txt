cmake_minimum_required(VERSION 3.22)

add_subdirectory(cmake/stm32mp1_hal)

file(GLOB_RECURSE DRIVER_SOURCES CONFIGURE_DEPENDS "driver/*.c" "driver/*.cpp")
add_library(drivers ${DRIVER_SOURCES})
target_link_libraries(drivers serialcomlib stm32mp1_hal freertos_kernel freertos_kernel_port)