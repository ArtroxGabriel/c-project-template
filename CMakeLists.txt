cmake_minimum_required(VERSION 3.15)
project(c_project_template VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Create library from source files
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main\\.c$")
add_library(${PROJECT_NAME}_lib ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

# Create executable
add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

# Enable testing
enable_testing()
add_subdirectory(test)

# Find clang-format for code formatting
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    # Get all source files
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/src/*.h"
        "${CMAKE_SOURCE_DIR}/include/*.h"
        "${CMAKE_SOURCE_DIR}/test/*.c"
        "${CMAKE_SOURCE_DIR}/test/*.h"
    )
    
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format on source files"
    )
    
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_SOURCE_FILES}
        COMMENT "Checking code formatting"
    )
endif()

# Find cppcheck for static analysis
find_program(CPPCHECK "cppcheck")
if(CPPCHECK)
    add_custom_target(lint
        COMMAND ${CPPCHECK}
            --enable=warning,style,performance,portability
            --std=c99
            --verbose
            --error-exitcode=1
            --inline-suppr
            -I ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/test
        COMMENT "Running cppcheck static analysis"
    )
endif()

# Package configuration
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "C Project Template")
set(CPACK_PACKAGE_CONTACT "developer@example.com")
include(CPack)

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_lib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Print configuration summary
message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  Project Name: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C Standard: C${CMAKE_C_STANDARD}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
if(CLANG_FORMAT)
    message(STATUS "  clang-format: Found (${CLANG_FORMAT})")
else()
    message(STATUS "  clang-format: Not found")
endif()
if(CPPCHECK)
    message(STATUS "  cppcheck: Found (${CPPCHECK})")
else()
    message(STATUS "  cppcheck: Not found")
endif()
message(STATUS "")