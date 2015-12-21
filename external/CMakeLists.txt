 
# Set cpr options
set(USE_SYSTEM_CURL ON)
set(BUILD_CPR_TESTS OFF)
set(INSECURE_CURL ON)
set(GENERATE_COVERAGE OFF)
set(USE_SYSTEM_GTEST ON)

add_subdirectory(cpr)
set_target_properties(cpr PROPERTIES COMPILE_FLAGS "-fPIC")
