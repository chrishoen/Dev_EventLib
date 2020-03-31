#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_global_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:\\MyTools\\MyLib\\include\\RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:\\MyTools\\MyLib\\lib\\RisLib.lib" PARENT_SCOPE)
      set (MyDspLibIncludePath "C:\\MyTools\\MyLib\\include\\DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "C:\\MyTools\\MyLib\\lib\\DspLib.lib" PARENT_SCOPE)
   elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.a" PARENT_SCOPE)
      set (MyDspLibIncludePath "/usr/local/include/DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "/usr/local/lib/libDspLib.a" PARENT_SCOPE)
      set (MyPThreadImportPath "/usr/lib/arm-linux-gnueabihf/libpthread.so" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/libRisLib.a" PARENT_SCOPE)
      set (MyPThreadImportPath "C:/Beagle/toolchain/arm-linux-gnueabihf/lib/libpthread.so" PARENT_SCOPE)
      set (MyDspLibIncludePath "C:/MyTools/MyLib/include/DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "C:/MyTools/MyLib/lib/libDspLib.a" PARENT_SCOPE)
   endif()

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   add_library(RisLib STATIC IMPORTED)
   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})
   
   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      add_library(PThreadLib SHARED IMPORTED)
      set_target_properties(PThreadLib PROPERTIES IMPORTED_LOCATION ${MyPThreadImportPath})
      target_link_libraries(RisLib INTERFACE PThreadLib)
   endif()

   target_link_libraries(${_target} RisLib)

endfunction()

function(my_inc_import_RisLib _target)

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_pthread _target)

   add_library(RisLib STATIC IMPORTED)
   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})
   target_link_libraries(${_target} RisLib)
   
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_DspLib _target)

   add_library(DspLib STATIC IMPORTED)
   set_target_properties(DspLib PROPERTIES IMPORTED_LOCATION ${MyDspLibImportPath})

   target_link_libraries(${_target} DspLib)

endfunction()

function(my_inc_import_DspLib _target)

   target_include_directories(${_target} PUBLIC ${MyDspLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
