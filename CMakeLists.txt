project(addressbook)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")

add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(write_message write_message.cc)
add_executable(read_message read_message.cc)
find_library(PROTOBUF NAMES libprotobuf.a)
target_link_libraries(write_message addressbook ${PROTOBUF_LIBRARY})
target_link_libraries(read_message addressbook ${PROTOBUF})
