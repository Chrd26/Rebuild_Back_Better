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



message("Building MacOS Version")
# Add resource files
# Read more on adding files https://stackoverflow.com/questions/41121000/cmake-os-x-bundle-recursively-copy-directory-to-resources
file(GLOB_RECURSE FONT_SOURCES "./fonts/*.ttf")
file(GLOB MENU_LIGHT_UP_SOUND "./audio/menulightup/lightup.wav")
file(GLOB MENU_MUSIC "./audio/music/onceuponatime.mp3")
file(GLOB DEFAULT_CURSOR "./graphics/player/cursor_main.png")
file(GLOB ATTACK_CURSOR "./graphics/player/sword_cursor.png")
file(GLOB GAMEPLAY_ENVIRONMENT_BACKGROUND "./graphics/enviroment/Game_Enviroment_Alternative Sky.jpg") 
file(GLOB LEAF_IMAGE "./graphics/player/leaf.png")
file(GLOB INTERACTABLE_CURSOR "./graphics/player/interactable_cursor.png")
file(GLOB MENU_ENVIRONMENT_BACKGROUND "./graphics/enviroment/Main_Menu_Environment.jpg")
file(GLOB UPGRADE_BUTTON_IMAGES "./graphics/interface/*.png")

# Create Executable
add_executable(	${PROJECT_NAME} MACOSX_BUNDLE 
				./src/main.cpp ./src/audioplayer.h ./src/audioplayer.cpp ./src/fighter.h
				./src/game.h ./src/game.cpp ./src/gameobject.h ./src/gatherer.h ./src/main.cpp
				./src/mainmenu.h ./src/mainmenu.cpp ./src/player.h ./src/player.cpp ./src/text.h
				./src/text.cpp ./src/text.h ./src/thief.h
				./src/pausemenu.h ./src/pausemenu.cpp
				./src/gameplay.h ./src/gameplay.cpp
				${FONT_SOURCES} ${MENU_LIGHT_UP_SOUND}
				${MENU_MUSIC} ${DEFAULT_CURSOR} ${ATTACK_CURSOR}
                ${GAMEPLAY_ENVIRONMENT_BACKGROUND} ${LEAF_IMAGE} ${INTERACTABLE_CURSOR}
                ${MENU_ENVIRONMENT_BACKGROUND})
				
#Add Interactable Cursor
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${INTERACTABLE_CURSOR} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${INTERACTABLE_CURSOR}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")
				
#Add Default Cursor
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${DEFAULT_CURSOR} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${DEFAULT_CURSOR}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")

#Add Attack Cursor
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${ATTACK_CURSOR} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${ATTACK_CURSOR}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")

#Add Enviroment Background
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${GAMEPLAY_ENVIRONMENT_BACKGROUND} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${GAMEPLAY_ENVIRONMENT_BACKGROUND}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")

#Add Menu Enviroment Background
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${MENU_ENVIRONMENT_BACKGROUND} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${MENU_ENVIRONMENT_BACKGROUND}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")

#Add Leaf 
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${LEAF_IMAGE} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${LEAF_IMAGE}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")
				
# Add Menu Music
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${MENU_MUSIC} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${MENU_MUSIC}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")
				
# Add menu light sfx
file(RELATIVE_PATH GET_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${MENU_LIGHT_UP_SOUND} )
get_filename_component(FILE_PATH "${GET_REL_PATH}" DIRECTORY)
set_property(SOURCE "${MENU_LIGHT_UP_SOUND}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${FILE_PATH}")
				
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
	

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE cpplocate::cpplocate)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_mixer::SDL3_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
