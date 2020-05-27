set(HASH_SOURCES
        binary.cpp
        md5.cpp
        hashModel.cpp
)

set(HASH_HEADERS
        binary.h
        md5.h
        hashModel.h)

add_library(hash STATIC ${HASH_SOURCES} ${HASH_HEADERS})
target_include_directories(hash PUBLIC ./)