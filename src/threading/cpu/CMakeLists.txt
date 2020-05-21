set(CPU_SOURCES
        scheduler.cpp
)

set(CPU_HEADERS
        scheduler.h
)

add_library(cpuThreading STATIC ${CPU_SOURCES} ${CPU_HEADERS})
target_link_libraries(cpuThreading foundation hash)
target_include_directories(cpuThreading PUBLIC ./)