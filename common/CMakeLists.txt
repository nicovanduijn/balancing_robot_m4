file(GLOB_RECURSE SRCS *.cpp)
add_executable(main ${SRCS})
target_link_libraries(main drivers freertos_kernel freertos_kernel_port)