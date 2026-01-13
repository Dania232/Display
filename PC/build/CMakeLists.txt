cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(MyProject VERSION 1.0)        # Project name and version

set(CMAKE_CXX_STANDARD 17)            # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add executable target
add_executable(flush ../scr/cli/flush.cpp ../scr/libs/io.cpp ../scr/libs/flush.hpp)
add_executable(mkmnchrom ../scr/cli/mkmnchrom.cpp ../scr/libs/io.cpp)
add_executable(remapimg ../scr/cli/remapimg.cpp ../scr/libs/io.cpp)
add_executable(show ../scr/cli/show.cpp ../scr/libs/io.cpp)


add_executable(app ../scr/app/main.cpp ../scr/app/Canvas.cpp ../scr/app/ICanvasImg.hpp ../scr/app/Flusher.hpp)