target_sources(dictionary PRIVATE "base-frame.h" "base-frame.cpp" "home-page.cpp" "home-page.h" "search-page.cpp" "search-page.h" "game-setting-page.cpp" "game-setting-page.h"  "more-page.h" "more-page.cpp" "HistoFavor-page.h" "HistoFavor-page.cpp")

target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
