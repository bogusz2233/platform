function(build_image APP_NAME)
    if(NOT ARGN)
        message(FATAL_ERROR "No app libraries provided: build_image(build_image APP_NAME [APP_LIBRARIES])")
    endif()

    add_executable(${APP_NAME})

    target_sources(
        ${APP_NAME}
        PRIVATE
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/main.cpp
    )

    target_link_libraries(
        ${APP_NAME}
        PRIVATE
        ${PROJECT_NAME}
        ${ARGN}
    )
endfunction()

add_subdirectory(drivers)