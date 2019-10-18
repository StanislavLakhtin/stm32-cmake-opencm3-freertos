# stm32-cmake-opencm3-freertos
Template for new project in CLION with libopencm3 and FreeRTOS

STM32f103C8T6 Default template for Clion

FreeRTOS v 10.2
OpenCM3 as SubModule

---------------

## Pre

Define project name in line `project(BBB)` (./CMakeLists.txt),

Don't forget change {PROJECTDIR}. 

## From scratch

```
git submodule update --init --recursive

cmake -DCMAKE_BUILD_TYPE= -DCMAKE_MAKE_PROGRAM=make -DCMAKE_C_COMPILER=arm-none-eabi-gcc -DCMAKE_CXX_COMPILER=arm-none-eabi-g++ -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake -G "CodeBlocks - Unix Makefiles" {PROJECTDIR}

```

## Get ready with OpenCM3

```
cmake --build {PROJECTDIR}/build/.generated --target libopencm3 -- -j 2
```

## Finish

```
cmake --build {PROJECTDIR}/build/.generated --target {PROJECTNAME} -- -j 2
```
