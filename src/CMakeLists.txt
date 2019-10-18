cmake_minimum_required(VERSION 3.9)

file(GLOB_RECURSE USER_SOURCES ./*.c ./*.cpp)
file(GLOB_RECURSE INC_FILES "include/*.h" "include/*.tpp")

add_executable(${PROJECT_NAME}.elf ${USER_SOURCES})

target_link_libraries(${PROJECT_NAME}.elf opencm3_stm32f1 freertos)