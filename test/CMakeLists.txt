# Test CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Include test sources
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Create test executables
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # Link with the main library if it exists
    if(TARGET ${PROJECT_NAME}-lib)
        target_link_libraries(${TEST_NAME} ${PROJECT_NAME}-lib)
    endif()
    
    # Link with Check library
    if(CHECK_DOWNLOADED)
        # Add dependency on the external project
        if(CHECK_EXTERNAL_TARGET)
            add_dependencies(${TEST_NAME} ${CHECK_EXTERNAL_TARGET})
        endif()
        target_include_directories(${TEST_NAME} PRIVATE ${CHECK_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME} ${CHECK_LIBRARIES})
        if(UNIX AND NOT APPLE)
            target_link_libraries(${TEST_NAME} rt pthread m)
        endif()
    else()
        target_include_directories(${TEST_NAME} PRIVATE ${CHECK_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME} ${CHECK_LIBRARIES})
        if(UNIX AND NOT APPLE)
            target_link_libraries(${TEST_NAME} rt subunit pthread m)
        endif()
    endif()
    
    # Add test to CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # Set test properties for better output
    set_tests_properties(${TEST_NAME} PROPERTIES
        TIMEOUT 30
        ENVIRONMENT "CK_FORK=no"
    )
endforeach()

# Print test information
message(STATUS "Test configuration:")
message(STATUS "  Test sources found: ${TEST_SOURCES}")
if(CHECK_FOUND OR CHECK_DOWNLOADED)
    message(STATUS "  Check library: Available")
    if(CHECK_DOWNLOADED)
        message(STATUS "  Check source: Downloaded automatically")
    else()
        message(STATUS "  Check source: System installation")
    endif()
else()
    message(STATUS "  Check library: NOT FOUND - tests will not be built")
endif()
message(STATUS "")