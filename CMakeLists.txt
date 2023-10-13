cmake_minimum_required(VERSION 3.27)

if(NOT DEFINED PLATFORM_NAME)
    message(FATAL_ERROR "'PLATFORM_NAME' is not defined")
endif()

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/platform/${PLATFORM_NAME}.cmake)
    message(FATAL_ERROR "platform/${PLATFORM_NAME}.cmake not exists")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/platform/${PLATFORM_NAME}.cmake)

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

add_subdirectory(libs)

enable_lib(${ETL_LIB_NAME})

attach_libs()

function(BUILD_IMAGE APP_NAME ...)
    message("BUILD_IMAGE: ${ARGN}")

    add_executable(${APP_NAME})

    target_sources(
        ${APP_NAME}
        PRIVATE
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/main.cpp
    )

    target_link_libraries(
        ${APP_NAME}
        PRIVATE
        ${ARGN}
    )
    
endfunction()




return()

include(toolchain/arm.cmake)
# include(platform/x86.cmake)

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



set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(externals)

CONFIGURE_PLATFORM()

add_compile_definitions(
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG> 
)

add_compile_options(
    $<$<CONFIG:Debug>:-Og>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    -fdiagnostics-color=always
    -Wreturn-type
    -Werror=return-type
)

set(MCU_NAME stm32f103rb)
add_subdirectory(libs)
add_subdirectory(platform)
add_subdirectory(drivers)

enable_library(${ETL_LIB_NAME})

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

set(FREERTOS_HEAP "4")
set(FREERTOS_PORT "GCC_ARM_CM3")
enable_library(${FREERTOS_LIB_NAME})

attach_libraries()


add_executable(${PROJECT_NAME})

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Wall
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    platform
    drivers
    ${ETL_LIB_NAME}
    ${FREERTOS_LIB_NAME}
)

add_custom_command(
    TARGET
    ${PROJECT_NAME}
    POST_BUILD
    COMMENT
    "HEX generation"
    COMMAND
    ${CMAKE_OBJCOPY}
    ARGS
    -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)

