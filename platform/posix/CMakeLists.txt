file(GLOB_RECURSE SRCS *.cpp)

add_library(drivers OBJECT ${SRCS})
target_link_libraries(drivers freertos_kernel freertos_kernel_port)