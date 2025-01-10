# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BLACKJACK)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable target
add_executable(blackjack main.cpp blackjack.cpp)
