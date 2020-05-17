include_directories(../lib/googletest-master/googletest/include)
include_directories(../lib/googletest-master/googlemock/include)

add_executable(runBasicGBusterTests hashTests.cpp)

target_link_libraries(runBasicGBusterTests gtest gtest_main)
target_link_libraries(runBasicGBusterTests exec)