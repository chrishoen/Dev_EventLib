cmake_minimum_required (VERSION 3.8)

project (LogTest CXX)
my_find_src_files (src_files LogTest)
add_executable (LogTest ${src_files})
my_add_compile_options (LogTest)
my_add_pch (LogTest)

my_inc_import_DspLib(LogTest)
my_inc_import_RisLib(LogTest)

my_lib_import_DspLib(LogTest)
my_lib_import_RisLib(LogTest)

