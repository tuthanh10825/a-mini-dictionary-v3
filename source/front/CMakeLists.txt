target_sources(dictionary PRIVATE "base-frame.h" "base-frame.cpp")
target_sources(dictionary PRIVATE "home-page.cpp" "home-page.h")
target_sources(dictionary PRIVATE "search-page.cpp" "search-page.h") 
target_sources(dictionary PRIVATE "game-setting-page.cpp" "game-setting-page.h")
target_sources(dictionary PRIVATE "more-page.h" "more-page.cpp") 
target_sources(dictionary PRIVATE "list-window.h" "list-window.cpp")
target_sources(dictionary PRIVATE "gameplay-page.h" "gameplay-page.cpp")
target_sources(dictionary PRIVATE "add-page.h" "add-page.cpp")
target_sources(dictionary PRIVATE "edit-page.h" "edit-page.cpp")



target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
