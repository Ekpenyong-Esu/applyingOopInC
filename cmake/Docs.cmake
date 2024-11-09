find_package(Doxygen)

if(DOXYGEN_FOUND)
    add_custom_target(
        docs
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs)
    message("Doxygen has been setup and documentation is now available.")
endif()
