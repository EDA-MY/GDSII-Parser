# Create a list of all test files ending with _test.cpp
file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp)

# Create test executable
add_executable(GDSIIParserTests ${TEST_SOURCES})
target_link_libraries(GDSIIParserTests gtest gtest_main)

# Add compiler flags for Debug and Release builds
target_compile_options(GDSIIParserTests PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra -Werror -Wshadow -Wsign-conversion -Wunreachable-code -Wuninitialized -Winit-self>
    $<$<CONFIG:Release>:-O3 -Wall -Wextra -Werror -Wshadow -Wsign-conversion -Wunreachable-code -Wuninitialized -Winit-self>
)

# Register tests with CTest
add_test(NAME UnitTests COMMAND GDSIIParserTests)