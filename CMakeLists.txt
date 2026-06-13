cmake_minimum_required(VERSION 3.5)
project(2dShooter)
add_executable(2dShooter src/main.cpp)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
target_link_libraries(2dShooter PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)
set_target_properties(2dShooter PROPERTIES 
                        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
                        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)