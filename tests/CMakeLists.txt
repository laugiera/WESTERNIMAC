file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)

set(MAIN main.cpp)
set(OUTPUT menu)




add_executable(${OUTPUT} ${MAIN} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})

#file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#target_link_libraries(${ImacMan} pthread)
#target_link_libraries(${ImacMan} pthread)
