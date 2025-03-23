cmake_minimum_required(VERSION 3.15)

project(
    GDSIIParser
    VERSION 0.1
    LANGUAGES CXX
)

# Set default build type to Debug if not specified (only for single-config generators)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type: (Debug, Release, etc.)" FORCE)
endif()



if (CMAKE_PROJECT STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(CTest)

    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(WARNING "Doxygen not found. Documentation will not be built.")
    endif()
endif()

include(FetchContent)

# Use existing Google Test if available, otherwise fetch it
if(EXISTS "${CMAKE_SOURCE_DIR}/extern/googletest")
    message(STATUS "Using existing Google Test from extern/googletest")
    add_subdirectory(extern/googletest)
else()
    message(STATUS "Google Test not found in extern/googletest. Fetching it...")

    # Fetch Google Test
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0 # Use a valid stable release tag
    )

    # Make Google Test available
    FetchContent_MakeAvailable(googletest)
endif()

find_package(Boost REQUIRED HINTS /usr/include/boost)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Enable testing
enable_testing()

# Add source files
add_subdirectory(src)
add_subdirectory(tests)
