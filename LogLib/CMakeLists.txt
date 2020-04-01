cmake_minimum_required (VERSION 3.8)

project (LogLib CXX)

my_find_src_files (src_files LogLib)
my_find_inc_files (inc_files)
add_library (LogLib STATIC ${src_files})
my_add_compile_options (LogLib)
my_add_pch (LogLib)

target_include_directories(LogLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(LogLib)

