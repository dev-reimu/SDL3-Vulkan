# Initial configuration
cmake_minimum_required(VERSION 3.16)
project(sdl3-vulkan)

# Executable and include header files
add_executable(${CMAKE_PROJECT_NAME} src/main.c src/reimus-sdl-extensions.c src/headers/reimus-sdl-extensions.h)

# Include SDL
add_subdirectory(SDL EXCLUDE_FROM_ALL)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)

# Include Vulkan
find_package(Vulkan REQUIRED)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})

# Set build output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
