cmake_minimum_required (VERSION 3.8)

project (EventLib CXX)

my_find_src_files (src_files EventLib)
my_find_inc_files (inc_files)
add_library (EventLib STATIC ${src_files})
my_add_compile_options (EventLib)
my_add_pch (EventLib)

target_include_directories(EventLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(EventLib)

