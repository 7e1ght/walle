cmake_minimum_required(VERSION 3.0.0)

project(walle)

enable_language(CXX C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(EXECUTABLE ${PROJECT_NAME}.elf)
set(STARTUP_INIT_PATH "${CMAKE_SOURCE_DIR}/cmsis/startup/startup.s")
set(LINKER_SCRIPT_PATH "${CMAKE_SOURCE_DIR}/cmsis/startup/linker/STM32F103C8TX_FLASH.ld")

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.cpp")

add_executable(${EXECUTABLE} ${SOURCE_FILES} ${STARTUP_INIT_PATH})

target_include_directories(${EXECUTABLE} PRIVATE
    cmsis/
)

target_compile_definitions(${EXECUTABLE} PRIVATE 
    ${BUILD}
)

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -fdata-sections
    -ffunction-sections
    -Wall
    -nostartfiles 
    -nodefaultlibs 
    -nostdlib
    -ggdb
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${LINKER_SCRIPT_PATH}
    -mcpu=cortex-m3
    -mthumb
    -specs=nano.specs
    -lc
    -lm
    -lnosys
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND arm-none-eabi-size ${EXECUTABLE}
)

# Create hex file
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
)