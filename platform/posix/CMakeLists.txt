file(GLOB_RECURSE SRCS *.cpp)

add_library(drivers ${SRCS})
target_link_libraries(drivers serialcomlib freertos_kernel freertos_kernel_port)