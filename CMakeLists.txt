cmake_minimum_required(VERSION 3.10)
project(c-project-template VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.c")

# Create library from source files (excluding main.c)
if(SOURCES)
    add_library(${PROJECT_NAME}-lib ${SOURCES})
    target_include_directories(${PROJECT_NAME}-lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
endif()

# Main executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.c)
if(SOURCES)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif()

# Build target (default)
add_custom_target(build ALL
    DEPENDS ${PROJECT_NAME}
    COMMENT "Building the project"
)

# Find clang-format for formatting
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format clang-format-12 clang-format-11 clang-format-10)

# Create .clang-format file if it doesn't exist
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/.clang-format)
    file(WRITE ${CMAKE_SOURCE_DIR}/.clang-format
"---
Language: Cpp
BasedOnStyle: LLVM
IndentWidth: 4
TabWidth: 4
UseTab: Never
ColumnLimit: 100
AlignConsecutiveAssignments: true
AlignConsecutiveDeclarations: true
AllowShortFunctionsOnASingleLine: Empty
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
BreakBeforeBraces: Linux
IndentCaseLabels: true
SpaceAfterCStyleCast: true
SpaceBeforeParens: ControlStatements
")
endif()

# Format target
if(CLANG_FORMAT_EXECUTABLE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/test/*.c
        ${CMAKE_SOURCE_DIR}/test/*.h
    )
    
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting source code with clang-format"
        VERBATIM
    )
    
    # Format-check target
    add_custom_target(format-check
        COMMAND ${CMAKE_COMMAND} -E echo "Checking code formatting..."
        COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run --Werror ${ALL_SOURCE_FILES}
        COMMENT "Checking if source code is properly formatted"
        VERBATIM
    )
else()
    add_custom_target(format
        COMMAND ${CMAKE_COMMAND} -E echo "clang-format not found. Please install clang-format to use this target."
        COMMENT "Format target (clang-format not available)"
    )
    
    add_custom_target(format-check
        COMMAND ${CMAKE_COMMAND} -E echo "clang-format not found. Please install clang-format to use this target."
        COMMENT "Format-check target (clang-format not available)"
    )
endif()

# Find required packages for testing
find_package(PkgConfig QUIET)

# Function to download and install Check if not found
function(download_check)
    include(ExternalProject)
    ExternalProject_Add(check_external
        URL https://github.com/libcheck/check/releases/download/0.15.2/check-0.15.2.tar.gz
        URL_HASH SHA256=a8de4e0bacfb4d76dd1c618ded263523b53b85d92a146d8835eb1a52932fa20a
        PREFIX ${CMAKE_BINARY_DIR}/external/check
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/check/install
            -DCMAKE_BUILD_TYPE=Release
            -DBUILD_TESTING=OFF
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_INSTALL ON
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
    set(CHECK_FOUND TRUE PARENT_SCOPE)
    set(CHECK_LIBRARIES ${CMAKE_BINARY_DIR}/external/check/install/lib/libcheck.a PARENT_SCOPE)
    set(CHECK_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/check/install/include PARENT_SCOPE)
    set(CHECK_EXTERNAL_TARGET check_external PARENT_SCOPE)
endfunction()

# Try to find Check library
if(PkgConfig_FOUND)
    pkg_check_modules(CHECK check)
endif()

if(NOT CHECK_FOUND)
    find_path(CHECK_INCLUDE_DIRS check.h)
    find_library(CHECK_LIBRARIES NAMES check)
    if(CHECK_INCLUDE_DIRS AND CHECK_LIBRARIES)
        set(CHECK_FOUND TRUE)
    endif()
endif()

# If Check is still not found, download it
if(NOT CHECK_FOUND)
    message(STATUS "Check library not found. Downloading and building Check...")
    download_check()
    set(CHECK_DOWNLOADED TRUE)
endif()

# Enable testing
enable_testing()

# Add test subdirectory
add_subdirectory(test)

# Test target
add_custom_target(test-run
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_example
    COMMENT "Running tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Find clang-tidy for linting
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy clang-tidy-12 clang-tidy-11 clang-tidy-10)

# Lint target
if(CLANG_TIDY_EXECUTABLE)
    file(GLOB_RECURSE LINT_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/include/*.h
    )
    
    add_custom_target(lint
        COMMAND ${CLANG_TIDY_EXECUTABLE} ${LINT_SOURCE_FILES} -- -I${CMAKE_SOURCE_DIR}/include
        COMMENT "Running clang-tidy linter on source code"
        VERBATIM
    )
else()
    add_custom_target(lint
        COMMAND ${CMAKE_COMMAND} -E echo "clang-tidy not found. Please install clang-tidy to use this target."
        COMMENT "Lint target (clang-tidy not available)"
    )
endif()

# Find valgrind for memory testing
find_program(VALGRIND_EXECUTABLE NAMES valgrind)

# Test-memory target
if(VALGRIND_EXECUTABLE)
    add_custom_target(test-memory
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -T memcheck
        DEPENDS test_example
        COMMENT "Running tests with memory checking (valgrind)"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    
    # Configure CTest to use valgrind
    set(MEMORYCHECK_COMMAND ${VALGRIND_EXECUTABLE})
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1")
    include(CTest)
else()
    add_custom_target(test-memory
        COMMAND ${CMAKE_COMMAND} -E echo "valgrind not found. Please install valgrind to use memory testing."
        COMMENT "Memory test target (valgrind not available)"
    )
endif()

# Note: 'test' target is automatically created by enable_testing()
# Use 'test-run' or 'ctest' to run tests

# Print build information
message(STATUS "")
message(STATUS "C Project Template Configuration:")
message(STATUS "  Project name: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C standard: ${CMAKE_C_STANDARD}")
message(STATUS "  Source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "  Binary directory: ${CMAKE_BINARY_DIR}")
message(STATUS "")
message(STATUS "Available targets:")
message(STATUS "  build        - Build the main executable")
message(STATUS "  format       - Format code with clang-format")
message(STATUS "  format-check - Check code formatting")
message(STATUS "  test         - Run unit tests (built-in CTest target)")
message(STATUS "  test-run     - Run unit tests")
message(STATUS "  test-memory  - Run tests with memory checking")
message(STATUS "  lint         - Run clang-tidy linter on source code")
message(STATUS "")