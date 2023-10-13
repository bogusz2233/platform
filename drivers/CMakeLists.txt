set(${DRIVERS_MODULE} drivers)

add_library(${DRIVERS_MODULE} static)

target_include_directories(
    ${DRIVERS_MODULE}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)