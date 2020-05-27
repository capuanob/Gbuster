set(CPU_SOURCES
        scheduler.cpp
        HashThread.cpp
)

set(CPU_HEADERS
        scheduler.h
        HashThread.h)

# Find wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(cpuThreading STATIC ${CPU_SOURCES} ${CPU_HEADERS})
target_link_libraries(cpuThreading foundation hash)
target_include_directories(cpuThreading PUBLIC ./)