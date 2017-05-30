#===============================================================================
# Compile Tests
#===============================================================================
add_executable(ConwayLibraryTests
        conway_class_tests.cpp
        game_grid_class_tests.cpp
        utilities_tests.cpp
        io_tests.cpp)

#===============================================================================
# Link
#===============================================================================
target_link_libraries(ConwayLibraryTests Conway)

#===============================================================================
# Copy Resources
#===============================================================================
add_custom_command(
        TARGET ConwayLibraryTests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory   # Copy resources
        ${CMAKE_SOURCE_DIR}/testing/library_tests/resources
        $<TARGET_FILE_DIR:ConwayLibraryTests>/resources
)