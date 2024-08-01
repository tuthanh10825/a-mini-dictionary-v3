
target_sources(dictionary PRIVATE "base-frame.h" "base-frame.cpp" "home-page.cpp" "home-page.h" "search-page.cpp" "search-page.h" "game-setting-page.cpp"   "more-page.h" "more-page.cpp" "gameplay-page.cpp" "gameplay-page.h")
target_sources(dictionary PRIVATE "favorite-page.h" "favorite-page.cpp")
target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
