cmake_minimum_required (VERSION 3.8)

project (EventTest CXX)
my_find_src_files (src_files EventTest)
add_executable (EventTest ${src_files})
my_add_compile_options (EventTest)
my_add_pch (EventTest)

my_inc_import_RisLib(EventTest)
my_inc_import_EventLib(EventTest)

my_lib_import_EventLib(EventTest)
my_lib_import_RisLib(EventTest)
