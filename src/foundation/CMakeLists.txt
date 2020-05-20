set(FOUNDATION_SOURCES
        CpuHardware.cpp
        hardware.cu
        cpustring.cpp
)

set(FOUNDATION_HEADERS
        CpuHardware.h
        hardware.cuh
        characterSets.h
        cpustring.h
)

add_library(foundation STATIC ${FOUNDATION_SOURCES} ${FOUNDATION_HEADERS})
target_include_directories(foundation PUBLIC ./)