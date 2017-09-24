cmake_minimum_required(VERSION 2.8.9)
project (A_star)

# CMAKE has lot of global variables, by changing them with set command
# we can get desired behaviour

# set the ouput folder where the executables will  be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# add compiler options, flags ..
add_compile_options(-std=c++14 -g)

include_directories(${CMAKE_SOURCE_DIR}/include
                    /usr/include)

add_library(${PROJECT_NAME} 
            src/${PROJECT_NAME}/AStarGrid.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME} -lsfml-graphics -lsfml-window -lsfml-system)

add_executable(sfml_test src/sfml_test.cpp)
target_link_libraries(sfml_test -lsfml-graphics -lsfml-window -lsfml-system)
