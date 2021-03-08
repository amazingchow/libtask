cmake_minimum_required(VERSION 3.5)

project(libtask)

############################################################
# Create a library
############################################################

add_library(task SHARED
    src/channel.c
    src/fd.c
    src/net.c
    src/print.c
    src/qlock.c
    src/rendez.c
    src/task.c
)

target_include_directories(task
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create the tester
############################################################

add_executable(httpload
    test/httpload.c
)

target_link_libraries(httpload
    PRIVATE
        task
)

add_executable(primes
    test/primes.c
)

target_link_libraries(primes
    PRIVATE 
        task
)

add_executable(tcpproxy
    test/tcpproxy.c
)

target_link_libraries(tcpproxy
    PRIVATE 
        task
)

add_executable(testdelay
    test/testdelay.c
)

target_link_libraries(testdelay
    PRIVATE 
        task
)

############################################################
# Install
############################################################

# Library
install (TARGETS task
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)
