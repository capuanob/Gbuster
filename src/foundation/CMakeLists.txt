set(FOUNDATION_SOURCES
        CpuHardware.cpp
        hardware.cu
)

set(FOUNDATION_HEADERS
        CpuHardware.h
        hardware.cuh
)

add_library(foundation STATIC ${FOUNDATION_SOURCES} ${FOUNDATION_HEADERS})
target_include_directories(foundation PUBLIC ./)