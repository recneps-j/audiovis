cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(audiovis VERSION 0.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" SRC_LIST)

find_package(portaudio REQUIRED)
if(PORTAUDIO_FOUND)
    message("Found portaudio at: ${PORTAUDIO_LIBRARIES}")
    message("Found portaudio include at: ${PORTAUDIO_INCLUDE_DIRS}")
endif(PORTAUDIO_FOUND)

find_package(SDL2 REQUIRED)
message("Found SDL2 at: ${SDL2_LIBRARIES}")
message("Found SDL2 include at: ${SDL2_INCLUDE_DIRS}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
                    "${PORTAUDIO_INCLUDE_DIRS}"
                    "${SDL2_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${PORTAUDIO_LIBRARIES} ${SDL2_LIBRARIES})