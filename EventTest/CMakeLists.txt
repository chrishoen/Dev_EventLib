cmake_minimum_required (VERSION 3.8)

project (EventThread CXX)
my_find_src_files (src_files EventThread)
add_executable (EventThread ${src_files})
my_add_compile_options (EventThread)
my_add_pch (EventThread)

my_inc_import_RisLib(EventThread)
my_inc_import_EventLib(EventThread)

my_lib_import_EventLib(EventThread)
my_lib_import_RisLib(EventThread)
