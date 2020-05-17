# Set up CMakeLists
cmake_minimum_required(VERSION 3.16)
project(Gbuster)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE) # Used for mixing libraries into 1 executable

include_directories(exec hashes) # Search in these folders for headers

# Set up wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(Gbuster exec/UI.cpp exec/UI.h exec/gFrame.cpp exec/gFrame.h hashes/md5.cpp hashes/md5.h hashes/binary.cpp hashes/binary.h exec/debugFrame.cpp exec/debugFrame.h exec/HashTestPanel.cpp exec/HashTestPanel.h exec/IDs.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})