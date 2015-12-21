include_directories(../)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
file(GLOB SRC_LIST *.cpp *.h)
add_executable(arango-test ${SRC_LIST})
target_link_libraries(arango-test arango++)
