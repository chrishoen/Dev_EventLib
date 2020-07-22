#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_EventLib _target)

   target_link_libraries(${_target} EventLib)

endfunction()

function(my_inc_import_EventLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:EventLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

