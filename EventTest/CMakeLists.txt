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


if (MSVC)
   add_custom_command(
      TARGET  EventTest
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy EventTest.exe c:/aaa_prime/EventLib/EventTest.exe
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_EventLib/EventTest)
elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS EventTest DESTINATION "/opt/prime/bin")
else()
add_custom_command(
   TARGET  EventTest
   POST_BUILD
   COMMAND rsync -azv --chmod=ugo=rwx EventTest rsync://debian@bby1/prime/bin
   WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_EventLib/EventTest)
endif()
