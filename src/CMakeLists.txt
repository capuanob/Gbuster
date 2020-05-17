cmake_minimum_required(VERSION 3.16)
project(Gbuster_exe)

set(SRC_SOURCES mainUI.cpp)

set(SRC_HEADERS
        mainUI.h
)

add_subdirectory(hashes)
add_subdirectory(ui)


# Set up wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(Gbuster ${SRC_HEADERS} ${SRC_SOURCES})
target_link_libraries(Gbuster ui) # Transitively links hashes as well