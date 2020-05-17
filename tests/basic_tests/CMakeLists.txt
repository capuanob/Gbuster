include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(This runGbusterTests)

set(HASH_TESTS_SOURCES
        hashTests.cpp
        binaryTests.cpp
)

add_executable(${This} ${HASH_TESTS_SOURCES})

target_link_libraries(${This} gtest gtest_main)
target_link_libraries(${This} hash) # Library we want to test