#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_LogLib _target)

   target_link_libraries(${_target} LogLib)

endfunction()

function(my_inc_import_LogLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:LogLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

