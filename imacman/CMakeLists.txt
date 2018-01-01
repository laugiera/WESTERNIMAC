include_directories(include)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

set(MAIN main.cpp include/CactusMan.hpp src/BlinkyGhost.cpp include/BlinkyGhost.hpp src/PinkyGhost.cpp include/PinkyGhost.hpp src/InkyGhost.cpp include/InkyGhost.hpp src/ClydeGhost.cpp include/ClydeGhost.hpp src/Ghost.cpp include/Ghost.hpp)
set(OUTPUT imacman)

add_executable(${OUTPUT} ${MAIN} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})

#file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../tests/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})