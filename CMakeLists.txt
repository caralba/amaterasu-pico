cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(amaterasu)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(
  main
  Src/main.cpp
  Drivers/bme280/bme280_spi.cpp
  Drivers/Display/display.cpp
  Drivers/Display/Config/DEV_Config.c
  Drivers/Display/e-Paper/EPD_1in54_V2.c
  Drivers/Display/Fonts/font12.c
  Drivers/Display/Fonts/font12CN.c
  Drivers/Display/Fonts/font16.c
  Drivers/Display/Fonts/font20.c
  Drivers/Display/Fonts/font24.c
  Drivers/Display/Fonts/font24CN.c
  Drivers/Display/Fonts/font8.c
  Drivers/Display/GUI/GUI_Paint.c
)

pico_enable_stdio_uart(main 0)
pico_enable_stdio_usb(main 1)

pico_add_extra_outputs(main)
target_link_libraries(main pico_stdlib pico_runtime  hardware_spi)
