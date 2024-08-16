target_sources(dictionary PRIVATE "tst.h" "dictionary.h" "WordNDef.h" "Globals.cpp" "Globals.h")
target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
