cmake_minimum_required(VERSION 3.28.3)
project("RebuildBackBetter" LANGUAGES CXX VERSION 0.1 DESCRIPTION "Originally made during GGJ22") 

# handle submldules: https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html 
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY "./modules/"
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/SDL/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ./src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

