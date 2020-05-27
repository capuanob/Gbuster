set(HASH_SOURCES
        md5.cpp
        )

set(HASH_HEADERS
        md5.h
        hashModel.h)

add_library(hash STATIC ${HASH_SOURCES} ${HASH_HEADERS})
target_include_directories(hash PUBLIC ./)