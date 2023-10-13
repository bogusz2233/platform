set(ETL_LIB_NAME etl                    PARENT_SCOPE)
set(FREERTOS_LIB_NAME freertos_kernel   PARENT_SCOPE)

set_property(GLOBAL PROPERTY LIBS_LIST)

function(enable_lib LIB_NAME)
    get_property(LIBS_LIST GLOBAL PROPERTY LIBS_LIST)
    if(${LIB_NAME} IN_LIST LIBS_LIST)
        return()
    endif()

    list(APPEND LIBS_LIST ${LIB_NAME})
    message("LIBS LIST: ${LIBS_LIST}")
    set_property(GLOBAL PROPERTY LIBS_LIST ${LIBS_LIST})
    
endfunction()


function(attach_libs)
    get_property(LIBS_LIST GLOBAL PROPERTY LIBS_LIST)

    foreach(LIB_NAME ${LIBS_LIST})
        add_subdirectory(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${LIB_NAME})
    endforeach()
    
    
endfunction()
