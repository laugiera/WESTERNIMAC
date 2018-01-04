cmake_minimum_required(VERSION 2.8)

project(ImacMan)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories( ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_LIBRARIES} ${SDL2_MIXER_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLU_INCLUDE_DIR} glimac/include third-party/include glcustom/include)

if(UNIX)
    set(ALL_LIBRARIES glimac glcustom ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARY} ${GLU_LIBRARY})
endif(UNIX)

if(WIN32)
    set(ALL_LIBRARIES mingw32 glcustom glimac SDL2main SDL2 glew32s opengl32 freeglut glu32)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES} ${SDL2_MIXER_INCLUDE_DIR})
endif(WIN32)

add_subdirectory(glimac)


#add_subdirectory(SDL2_mixer)
add_subdirectory(glcustom)
#add_subdirectory(imacman)
add_subdirectory(tests)

#if all files grey in CLion and red cross on build (or debug not found) -> build, click "build" in error popup, click ok -> let it do its thing -> try to build again
#if findXXX.cmake not included error -> look up a def of said file on the internet and include in CMake folder
#if lib not found through findXXX.cmake -> install said lib
#if '% error -> delete build files in cmake-build-debug folder

