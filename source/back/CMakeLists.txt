target_sources(dictionary PRIVATE "tst.h" "dictionary.h" "WordNDef.h" "Globals.cpp" "Globals.h" "suffix-array.h")
target_sources(dictionary PRIVATE "red-black-tree.h" )
target_include_directories(dictionary PRIVATE ${CMAKE_CURRENT_LIST_DIR})
