target_sources(dictionary PRIVATE "main-frame.h" "main-frame.cpp")
target_sources(dictionary PRIVATE "home-frame.h" "home-frame.cpp")
target_sources(dictionary PRIVATE "base-frame.h" "base-frame.cpp")
target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
