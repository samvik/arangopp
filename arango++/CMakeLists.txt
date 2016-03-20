set(ARANGO_DRIVER_VERSION 0.1.0)
set(ARANGO_DRIVER_ABI_VERSION 0)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

file(GLOB SRC_LIST *.cpp *.h)

add_library(arango++ SHARED ${SRC_LIST})
set_target_properties (arango++ PROPERTIES
	OUTPUT_NAME arango++
	VERSION ${ARANGO_DRIVER_VERSION}
	SOVERSION ${ARANGO_DRIVER_ABI_VERSION}
)

target_include_directories(arango++
	PRIVATE ./ ${CPR_INCLUDE_DIRS}
	PUBLIC ${arango++_SOURCE_DIR}
	PUBLIC ${arango++_SOURCE_DIR}/external/json/src)
target_link_libraries(arango++ PUBLIC ${CPR_LIBRARIES})

# Install
install(TARGETS arango++ LIBRARY
				DESTINATION lib
				COMPONENT runtime)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/arango++/
				DESTINATION "include/arango++"
				COMPONENT development
				FILES_MATCHING PATTERN "*.h")


