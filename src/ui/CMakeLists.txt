set(UI_SOURCES
        debugFrame.cpp
        gFrame.cpp
        hashTestPanel.cpp
        mainPanel.cpp
)

set(UI_HEADERS
        debugFrame.h
        gFrame.h
        hashTestPanel.h
        IDs.h
        mainPanel.h
)

# Find wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(ui STATIC ${UI_SOURCES} ${UI_HEADERS})
target_link_libraries(ui cpuThreading ${wxWidgets_LIBRARIES})
target_include_directories(ui PUBLIC ./)
