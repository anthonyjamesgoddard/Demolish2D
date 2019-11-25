cmake_minimum_required(VERSION 3.10)

project(demolish)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
# for completion in vim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

# these are in a specific order (we use the fact that
# linear algebra will inherit utils and geometry
# will inherit linear algebra which will inherit utils
add_subdirectory(geometry)
add_subdirectory(utils)
add_subdirectory(world)
add_subdirectory(demolish)

add_subdirectory(docs)
