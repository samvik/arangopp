set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-global-constructors")

file(GLOB SRC_LIST *.cpp)
add_executable(arango-unit ${SRC_LIST})
target_link_libraries(arango-unit arango++)

include_directories(${CMAKE_SOURCE_DIR})
