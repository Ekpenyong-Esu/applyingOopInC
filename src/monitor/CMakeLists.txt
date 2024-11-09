set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/monitor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/monitor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibMonitor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibMonitor" PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries("LibMonitor" PUBLIC "LibLogger")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibMonitor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibMonitor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibMonitor")
endif()
