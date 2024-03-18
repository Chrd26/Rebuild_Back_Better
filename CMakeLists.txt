cmake_minimum_required(VERSION 3.28.3)
project("RebuildBackBetter" LANGUAGES CXX VERSION 0.1 DESCRIPTION "Originally made during GGJ22") 
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ./src/main.cpp)
