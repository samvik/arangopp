 
# Set cpr options
set(BUILD_CPR_TESTS OFF CACHE BOOL "")
set(USE_SYSTEM_CURL ON CACHE BOOL "")
add_subdirectory(cpr)
set_target_properties(cpr PROPERTIES COMPILE_FLAGS "-fPIC")
