cmake_minimum_required(VERSION 3.12)
project(Client)

SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

#add_link_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++20 )
#add_compile_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)

add_executable(Server
  ../NetWork/net_message.h
  net_server.h
  ../NetWork/net_queue.h
  ../NetWork/net_connection.h

  ../DBWork/data_base.cpp
  ../DBWork/data_base.h

  Server.h
  Server.cpp
  main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
TARGET_LINK_LIBRARIES(Server  ${PQXX_LIB} ${PQ_LIB})