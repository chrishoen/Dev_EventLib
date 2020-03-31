cmake_minimum_required (VERSION 3.8)

project (LogLib CXX)

my_find_src_files (src_files LogLib)
my_find_inc_files (inc_files)
add_library (LogLib STATIC ${src_files})
my_add_compile_options (LogLib)
my_add_pch (LogLib)

target_include_directories(LogLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(LogLib)


if (MSVC OR CMAKE_SYSTEM_VERSION EQUAL 101)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/LogLib")
   install(TARGETS LogLib DESTINATION "C:/MyTools/MyLib/lib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/LogLib")
   install(TARGETS LogLib DESTINATION "/usr/local/lib")
endif()
