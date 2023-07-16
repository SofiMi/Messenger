cmake_minimum_required(VERSION 3.12)
project(testas)
cmake_policy(SET CMP0072 NEW)


SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_link_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++20 )
add_compile_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)

find_package(OpenGL REQUIRED)

add_executable(testas 
  ./GrInterface/gr_interface.h
  ./GrInterface/gr_interface.cpp
  ./GrInterface/text_render.h
  ./GrInterface/text_render.cpp

  ./GrInterface/glad/glad.h
  ./GrInterface/glad/glad.c
  ./GrInterface/glad/khrplatform.h

  #./WorkDB/data_base.h
  #./WorkDB/data_base.cpp

  ./Client/client.h
  ./Client/client.cpp

  main.cpp
)

target_link_libraries(testas 
  glfw
  OpenGL::GL
)

target_link_libraries(testas -lpqxx -lpq)