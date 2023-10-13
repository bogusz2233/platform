add_compile_definitions(
    -DUSE_FULL_LL_DRIVER
    -DSTM32F103xB
)

add_compile_options(
    -specs=nano.specs
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -fdata-sections
    -ffunction-sections
    -fstack-usage 
    -mfloat-abi=soft 
    -mthumb
)

add_link_options(
    -mcpu=cortex-m3
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    --specs=nosys.specs
    -static 
    -mfloat-abi=soft 
    -mthumb 
    -Wl,--start-group 
    -lc 
    -lm 
    -Wl,--end-group
    -Wl,--print-memory-usage
)

set(PLATFORM_NAME stm32f103)
set(CMAKE_EXECUTABLE_SUFFIX .elf)
