cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#[[
    Check if SPlatform is being used directly or via add_subdirectory.
#]]
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PLATFORM_MASTER_PROJECT ON)
else()
    set(PLATFORM_MASTER_PROJECT OFF)
endif()

option(BUILD_TESTS "Build unit tests" OFF)

if(NOT DEFINED PLATFORM_NAME)
    message(FATAL_ERROR "'PLATFORM_NAME' is not defined")
endif()

if(BUILD_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/platform/x86.cmake)
else()
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/platform/${PLATFORM_NAME}.cmake)
        message(FATAL_ERROR "platform/${PLATFORM_NAME}.cmake not exists")
    endif()

    include(${CMAKE_CURRENT_SOURCE_DIR}/platform/${PLATFORM_NAME}.cmake)
endif()


add_compile_definitions(
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG> 
)

add_compile_options(
    $<$<CONFIG:Debug>:-Og>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    -fdiagnostics-color=always
    -Wall
    -Wreturn-type
    -Werror=return-type
)

set (CMAKE_CXX_STANDARD 17)

if(BUILD_TESTS)
    project("unit-test")
    add_library(${PROJECT_NAME} STATIC)
    include(CTest)
    add_subdirectory(unit_tests)
else()
    project("firmare")
    add_library(${PROJECT_NAME} STATIC)
    add_subdirectory(libs)

    add_subdirectory(src)

    if(${PLATFORM_MASTER_PROJECT})
        add_subdirectory(examples)
    endif()
endif()
