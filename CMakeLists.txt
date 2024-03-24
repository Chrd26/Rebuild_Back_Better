cmake_minimum_required(VERSION 3.28.3)
project("RebuildBackBetter" LANGUAGES CXX VERSION 0.1 DESCRIPTION "Originally made during GGJ22") 
if (APPLE)
	enable_language(OBJCXX)
endif()
set(CMAKE_CXX_STANDARD 20)
set(SDL3_ttf_DIR "${PROJECT_SOURCE_DIR}/modules/SDL_ttf/build")

# Handle Submodules: https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html 
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

# Add the following for each submodule to make sure that it exists

# Has SDL been downloaded?
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/SDL/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Has SDL_ttf been downloaded?
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/SDL_ttf/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


# Add resource files
# Read more on adding files https://stackoverflow.com/questions/41121000/cmake-os-x-bundle-recursively-copy-directory-to-resources
file(GLOB_RECURSE FONT_SOURCES "fonts/*.ttf")

# Handle Libraries
add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL")
add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL_ttf")
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
add_executable(${PROJECT_NAME} MACOSX_BUNDLE 
				./src/main.cpp ./src/game.h 
				./src/game.cpp ./src/gameobjects.h 
				./src/player.h ./src/thief.h 
				./src/gatherer.h ./src/fighter.h
				./src/macos.h ./src/macos.mm 
				${FONT_SOURCES})
				
#individually set the file's path properties
foreach(FONT_FILE ${FONT_SOURCES})
	message(FONT_FILE="${FONT_FILE}")


  # Get the folder and the file name
  file(RELATIVE_PATH RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${FONT_FILE})
  message(RELATIVE_PATH="${RES_PATH}")
  
  # keep only the name of the folder
  get_filename_component(NEW_FILE_PATH ${RES_PATH} DIRECTORY)
  message(NEW_RELATIVE_PATH="${NEW_FILE_PATH}")

  # Add the FONT_FILE into the NEW_FILE_PATH folder
  set_property(SOURCE ${FONT_FILE} PROPERTY MACOSX_PACKAGE_LOCATION "${NEW_FILE_PATH}")

endforeach(FONT_FILE)

# Build MacOs Build file
# Read More: 
# https://stackoverflow.com/questions/76486081/mix-c-and-objective-c-code-using-cmake-and-get-c-executable
add_library(macosbuild MODULE
    ./src/macoswrapper.mm
)

target_sources(macosbuild
  PRIVATE
    ./src/macos.h
    ./src/macos.mm
)

target_link_libraries(macosbuild
    PRIVATE "-framework Cocoa"
    PRIVATE "-framework Foundation"
    PRIVATE "-framework AppKit"
)

# Set the language for the library to Objective-C++
set_target_properties(macosbuild PROPERTIES
    LINKER_LANGUAGE "CXX"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES YES
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_WEAK YES
)
				
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
# Code from here: https://stackoverflow.com/questions/17070101/why-i-cannot-link-the-mac-framework-file-with-cmake

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation")
endif()

