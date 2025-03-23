# Add an executable target
add_executable(GDSIIParser main.cpp gdsii_reader.cpp)

# Include directories for headers
target_include_directories(GDSIIParser PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add compiler flags for Debug and Release builds
target_compile_options(GDSIIParser PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra -Werror -Wshadow -Wsign-conversion -Wunreachable-code -Wuninitialized -Winit-self>
    $<$<CONFIG:Release>:-O3 -Wall -Wextra -Werror -Wshadow -Wsign-conversion -Wunreachable-code -Wuninitialized -Winit-self>
)