cmake_minimum_required(VERSION 3.10)

# set the project name
project(BPM_Timer)

# set path to findSFML.cmake file
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# find SFML components
find_package(SFML 2.4 COMPONENTS graphics window system audio REQUIRED)

# list .cpp files
set(SOURCES main.cpp LP.cpp MP.cpp LoadImage.cpp Game.cpp BPMScene.cpp UIManager.cpp UIText.cpp)

# add the executable
add_executable(BPM_Timer ${SOURCES}) 

# link SFML libraries
target_link_libraries(BPM_Timer sfml-graphics sfml-window sfml-system sfml-audio)