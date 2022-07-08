# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "C:/Users/evely/Documents/Pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(melty-firmware C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(melty-firmware melty-firmware.cpp LIS331.cpp dshot.cpp ibus.cpp)

pico_generate_pio_header(melty-firmware ${CMAKE_CURRENT_LIST_DIR}/dshot.pio)

pico_set_program_name(melty-firmware "melty-firmware")
pico_set_program_version(melty-firmware "0.1")

pico_enable_stdio_uart(melty-firmware 0)
pico_enable_stdio_usb(melty-firmware 1)

# Add the standard library to the build
target_link_libraries(melty-firmware pico_stdlib)

# Add any user requested libraries
target_link_libraries(melty-firmware
        hardware_i2c
        hardware_pio
        )

pico_add_extra_outputs(melty-firmware)

