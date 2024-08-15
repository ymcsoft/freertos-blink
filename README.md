# freertos-blink
Raspberry Pi Pico Test App with FreeRTOS capabilities

## Pre-requisites

* CMake (https://cmake.org/)
* DevTools (make, git, )
* ARM Toolchain (https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
* Pico SDK (https://github.com/raspberrypi/pico-sdk)
* FreeRTOS Kernel (https://github.com/FreeRTOS/FreeRTOS-Kernel)

## How to Build

* Follow the instruction in https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico to set up the environment.

* Configure **PICO_SDK_PATH** environment variable to point to Pico SDK
* Create a build directory 
```bash
mkdir cmake-build-debug
```
* Change directory to cmake-build-debug
```bash
cd cmake-build-debug
```
* run CMake command to generate make files
```bash
cmake ..
```
* Build binaries *blink.uf2*
```bash
make
```

### How to Install

* Connect Raspberry Pi Pico to micro USB cable
* Press BOOTSEL button on the Pico board
* Connect micro USB cable to the computer
* Release the BOOTSEL button once your Pico appears as a Mass Storage Device called RPI-RP2.
* Copy *blink.uf2* file onto the RPI-RP2 volume. Your Pico will reboot.
