cmake_minimum_required(VERSION 3.26)
project(Rebuild_Back_Better)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rebuild_Back_Better main.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE SDL2::SDL2_gfx)
find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
find_package(SDL2_mixer CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)
find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
find_package(SDL2_mixer_ext CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer_ext::SDL2_mixer_ext>,SDL2_mixer_ext::SDL2_mixer_ext,SDL2_mixer_ext::SDL2_mixer_ext_Static>)
find_package(SDL2_net CONFIG REQUIRED)
target_link_libraries(Rebuild_Back_Better PRIVATE $<IF:$<TARGET_EXISTS:SDL2_net::SDL2_net>,SDL2_net::SDL2_net,SDL2_net::SDL2_net-static>)