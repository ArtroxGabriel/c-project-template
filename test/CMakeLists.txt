# Test configuration
cmake_minimum_required(VERSION 3.15)

# Find or download Check testing framework
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(CHECK check)
endif()

if(NOT CHECK_FOUND)
    # Download and build Check if not found
    include(ExternalProject)
    
    set(CHECK_INSTALL_DIR ${CMAKE_BINARY_DIR}/external)
    
    ExternalProject_Add(check_ext
        URL https://github.com/libcheck/check/releases/download/0.15.2/check-0.15.2.tar.gz
        URL_HASH SHA256=a8de4e0bacfb4d76dd1c618ded263523b53b85d92a146d8835eb1a52932fa20a
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CHECK_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=Release
            -DCHECK_ENABLE_TESTS=OFF
            -DCHECK_ENABLE_TIMEOUT_TESTS=OFF
        BUILD_BYPRODUCTS
            ${CHECK_INSTALL_DIR}/lib/libcheck.a
    )
    
    # Create directory for include files
    file(MAKE_DIRECTORY ${CHECK_INSTALL_DIR}/include)
    
    # Create imported library
    add_library(check STATIC IMPORTED)
    set_target_properties(check PROPERTIES
        IMPORTED_LOCATION ${CHECK_INSTALL_DIR}/lib/libcheck.a
        INTERFACE_INCLUDE_DIRECTORIES ${CHECK_INSTALL_DIR}/include
    )
    add_dependencies(check check_ext)
    
    # Set variables for compatibility
    set(CHECK_LIBRARIES check)
    set(CHECK_INCLUDE_DIRS ${CHECK_INSTALL_DIR}/include)
    set(CHECK_FOUND TRUE)
else()
    # Use system Check
    set(CHECK_LIBRARIES ${CHECK_LIBRARIES})
    set(CHECK_INCLUDE_DIRS ${CHECK_INCLUDE_DIRS})
endif()

if(CHECK_FOUND)
    # Include check headers
    include_directories(${CHECK_INCLUDE_DIRS})
    
    # Create test executable
    add_executable(test_example test_example.c)
    target_link_libraries(test_example 
        ${PROJECT_NAME}_lib 
        ${CHECK_LIBRARIES}
    )
    
    # Add math library if needed (for some systems)
    find_library(MATH_LIBRARY m)
    if(MATH_LIBRARY)
        target_link_libraries(test_example ${MATH_LIBRARY})
    endif()
    
    # Add subunit library if available (optional dependency of check)
    find_library(SUBUNIT_LIBRARY subunit)
    if(SUBUNIT_LIBRARY)
        target_link_libraries(test_example ${SUBUNIT_LIBRARY})
    endif()
    
    # Add pthread library if needed
    find_package(Threads)
    if(Threads_FOUND)
        target_link_libraries(test_example Threads::Threads)
    endif()
    
    # Add test to CTest
    add_test(NAME example_tests COMMAND test_example)
    
    # Set test properties
    set_tests_properties(example_tests PROPERTIES
        TIMEOUT 30
        PASS_REGULAR_EXPRESSION "100%: Checks: [0-9]+, Failures: 0, Errors: 0"
    )
    
    message(STATUS "Check testing framework configured")
else()
    message(WARNING "Check testing framework not found and could not be downloaded")
endif()