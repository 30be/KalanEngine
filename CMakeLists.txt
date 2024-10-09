cmake_minimum_required(VERSION 3.16.3)

project(WorkTimer)
set(CXX_STANDARD 23)


# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp" "src/*.h")  # Adjust the file extensions as neede
add_executable(WorkTimer ${SOURCES})
target_link_libraries(my_executable ${SDL2_LIBRARIES})
