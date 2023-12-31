cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico6502monitor)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(monitor
    monitor.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(monitor pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(monitor 1)
pico_enable_stdio_uart(monitor 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(monitor)