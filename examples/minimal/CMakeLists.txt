set(APP_NAME minimal)
set(APP_LIB_NAME ${APP_NAME}_src)

add_library(${APP_LIB_NAME})

target_sources(
    ${APP_LIB_NAME}
    PRIVATE
    app_main.cpp
)

build_image(${APP_NAME} ${APP_LIB_NAME})