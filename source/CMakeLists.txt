# CMakeList.txt : CMake project for a-mini-dictionary-v3, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (dictionary "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dictionary PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
  set_property(TARGET dictionary PROPERTY WIN32_EXECUTABLE TRUE)
  target_sources(dictionary PRIVATE ".manifest")
endif()


# TODO: Add tests and install targets if needed.
target_link_libraries(dictionary PRIVATE wx::base wx::core wx::aui)
target_link_libraries(dictionary PRIVATE uni-algo::uni-algo)
add_custom_command(TARGET dictionary POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	${CMAKE_SOURCE_DIR}/resources
	${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory("back")
add_subdirectory("front")