cmake_minimum_required(VERSION 3.28.3)
project("RebuildBackBetter" LANGUAGES CXX VERSION 0.1 DESCRIPTION "Originally made during GGJ22") 
set(CMAKE_CXX_STANDARD 20)
set(SDL3_DIR "${PROJECT_SOURCE_DIR}/modules/SDL/build")
set(SDL3_ttf_DIR "${PROJECT_SOURCE_DIR}/modules/SDL_ttf/build")
set(cpplocate_DIR "${PROJECT_SOURCE_DIR}/modules/cpplocate")
set(SDL3_mixer_DIR "${PROJECT_SOURCE_DIR}/modules/SDL_mixer/build")
set(SDL3_image_DIR "${PROJECT_SOURCE_DIR}/modules/SDL_image/build")


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

# Has cpplocate been downloaded?
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/cpplocate/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Has sdl_mixer been downloaded?
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/SDL_mixer/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# has sdl_image been down loaded?
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/SDL_image/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


if (CMAKE_SYSTEM_NAME MATCHES Darwin)
	message("Building MacOS Version")
	# Add resource files
	# Read more on adding files https://stackoverflow.com/questions/41121000/cmake-os-x-bundle-recursively-copy-directory-to-resources
	file(GLOB_RECURSE FONT_SOURCES "fonts/*.ttf")
	
	# Handle Libraries
	add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL")
	add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL_ttf")
	add_subdirectory("${PROJECT_SOURCE_DIR}/modules/cpplocate")
	add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL_mixer")
	add_subdirectory("${PROJECT_SOURCE_DIR}/modules/SDL_image")
	find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf)
	find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
	find_package(cpplocate REQUIRED CONFIG REQUIRED COMPONENTS cpplocate)
	find_package(SDL3_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL3_mixer)
	
	# Create Executable
	add_executable(${PROJECT_NAME} MACOSX_BUNDLE
				./src/main.cpp ./src/game.h 
				./src/game.cpp ./src/gameobjects.h 
				./src/player.h ./src/thief.h 
				./src/gatherer.h ./src/fighter.h
				./src/menuoptionsstructure.h
				${FONT_SOURCES})
				
	#individually set the file's path properties

	foreach(FONT_FILE ${FONT_SOURCES})

	# Get the folder and the file name
	file(RELATIVE_PATH RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${FONT_FILE})
  
	# keep only the name of the folder
	get_filename_component(NEW_FILE_PATH ${RES_PATH} DIRECTORY)

	# Add the FONT_FILE into the NEW_FILE_PATH folder
	set_property(SOURCE ${FONT_FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")

	endforeach(FONT_FILE)
	
	# Code from here: https://stackoverflow.com/questions/17070101/why-i-cannot-link-the-mac-framework-file-with-cmake
	target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation")

elseif (CMAKE_SYSTEM_NAME MATCHES Windows)
	message("Build Windows Version")
	
endif()


#add_executable(${PROJECT_NAME} WIN32 
#				./src/main.cpp ./src/game.h 
#				./src/game.cpp ./src/gameobjects.h 
#				./src/player.h ./src/thief.h 
#				./src/gatherer.h ./src/fighter.h
#				./src/menuoptionsstructure.h)

# Copy directories https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree
#	file(COPY "./fonts" DESTINATION "Resources")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE cpplocate::cpplocate)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_mixer::SDL3_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
