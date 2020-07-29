cmake_minimum_required (VERSION 3.8)

project (EventLib CXX)

my_find_src_files (src_files EventLib)
my_find_inc_files (inc_files)
add_library (EventLib SHARED ${src_files})
my_add_compile_options_so (EventLib)
my_add_pch (EventLib)

target_include_directories(EventLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(EventLib)

if (MSVC OR CMAKE_SYSTEM_VERSION EQUAL 101)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/EventLib")
   install(TARGETS EventLib DESTINATION "C:/MyTools/MyLib/lib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/EventLib")
   install(TARGETS EventLib DESTINATION "/usr/local/lib")
endif()

if(CMAKE_SYSTEM_VERSION EQUAL 101)
   add_custom_command(
      TARGET  EventLib
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx libEventLib.so rsync://debian@bby1/prime/stage
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_EventLib/EventLib)
endif()

