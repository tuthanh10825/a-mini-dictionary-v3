# CMakeList.txt : CMake project for a-mini-dictionary-v3, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (a-mini-dictionary-v3 "a-mini-dictionary-v3.cpp" "a-mini-dictionary-v3.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET a-mini-dictionary-v3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
