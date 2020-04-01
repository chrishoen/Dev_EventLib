#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_boost_import_variables)

   if(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyBoostIncludePath "/usr/local/include/boost" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "/usr/local/lib/libboost_system.so" PARENT_SCOPE)
      set (MyBoostThreadImportPath  "/usr/local/lib/libboost_thread.so" PARENT_SCOPE)
      set (MySQLite3IncludePath "/usr/include" PARENT_SCOPE)
      set (MySQLite3ImportPath "/usr/lib/arm-linux-gnueabihf/libsqlite3.so" PARENT_SCOPE)
      set (MyStdFsImportPath "/usr/lib/gcc/arm-linux-gnueabihf/8/libstdc++fs.a" PARENT_SCOPE)
      set (MyAtomicImportPath "/usr/lib/gcc/arm-linux-gnueabihf/8/libatomic.so" PARENT_SCOPE)
      set (MyPhpCppIncludePath "/usr/include" PARENT_SCOPE)
      set (MyPhpCppImportPath "/usr/lib/libphpcpp.so" PARENT_SCOPE)
   else()
      set (MyBoostIncludePath "C:/Beagle/boost/include" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "C:/Beagle/boost/lib/libboost_system.so" PARENT_SCOPE)
      set (MyBoostThreadImportPath  "C:/Beagle/boost/lib/libboost_thread.so" PARENT_SCOPE)
      set (MySQLite3IncludePath "C:/Beagle/sqlite3/include" PARENT_SCOPE)
      set (MySQLite3ImportPath  "C:/Beagle/sqlite3/lib/libsqlite3.so" PARENT_SCOPE)
      set (MyStdFsImportPath  "c:/Beagle/toolchain/arm-linux-gnueabihf/sysroot/usr/lib/gcc/arm-linux-gnueabihf/8/libstdc++fs.a" PARENT_SCOPE)
      set (MyAtomicImportPath  "c:/Beagle/toolchain/arm-linux-gnueabihf/sysroot/usr/lib/gcc/arm-linux-gnueabihf/8/libatomic.so" PARENT_SCOPE)
      set (MyPhpCppIncludePath "C:/Beagle/phpcpp/include" PARENT_SCOPE)
      set (MyPhpCppImportPath  "C:/Beagle/phpcpp/lib/libphpcpp.so" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_phpcpp _target)

   add_library(phpcpp SHARED IMPORTED)
   set_target_properties(phpcpp PROPERTIES IMPORTED_LOCATION ${MyPhpCppImportPath})
   target_link_libraries(${_target} phpcpp)
   
endfunction()

function(my_inc_import_phpcpp _target)

   target_include_directories(${_target} PUBLIC ${MyPhpCppIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_boost _target)

   add_library(boost_system SHARED IMPORTED)
   add_library(boost_thread SHARED IMPORTED)

   set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION ${MyBoostSystemImportPath})
   set_target_properties(boost_thread PROPERTIES IMPORTED_LOCATION ${MyBoostThreadImportPath})

   target_link_libraries(${_target} boost_system)
   target_link_libraries(${_target} boost_thread)
   
endfunction()

function(my_inc_import_boost _target)

   target_include_directories(${_target} PUBLIC ${MyBoostIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_sqlite3 _target)

   add_library(sqlite3 SHARED IMPORTED)

   set_target_properties(sqlite3 PROPERTIES IMPORTED_LOCATION ${MySQLite3ImportPath})

   target_link_libraries(${_target} sqlite3)
   
endfunction()

function(my_inc_import_sqlite3 _target)

   target_include_directories(${_target} PUBLIC ${MySQLite3IncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_stdfs _target)

   add_library(stdc++fs STATIC IMPORTED)

   set_target_properties(stdc++fs PROPERTIES IMPORTED_LOCATION ${MyStdFsImportPath})

   target_link_libraries(${_target} stdc++fs)
   
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_atomic _target)

   target_link_options(${_target} PRIVATE "-latomic")
   return()
   
   add_library(atomic SHARED IMPORTED)

   set_target_properties(atomic PROPERTIES IMPORTED_LOCATION ${MyAtomicImportPath})

   target_link_libraries(${_target} atomic)
   
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
