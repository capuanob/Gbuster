set(FOUNDATION_SOURCES
        CpuHardware.cpp
        hardware.cu
        characterSets.cpp
        numberSystem.cpp
)

set(FOUNDATION_HEADERS
        CpuHardware.h
        hardware.cuh
        characterSets.h
        numberSystem.h
        constants.h
        session.h
)

add_library(foundation STATIC ${FOUNDATION_SOURCES} ${FOUNDATION_HEADERS})
target_include_directories(foundation PUBLIC ./)