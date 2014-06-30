macro(copy_dll)
  # TODO : Refactor to make the message appear at make-time as well.
  set(FOUND_DLL off)
  set(FIRST_DLL "")

  foreach(f ${ARGN})
    if(FIRST_DLL STREQUAL "")
      set(FIRST_DLL ${f})
    endif()
    if(EXISTS ${f})
      add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                         COMMAND ${CMAKE_COMMAND} -E
                         copy_if_different ${f} ${PROJECT_BINARY_DIR})
      set(FOUND_DLL on)
      break()
    endif()
  endforeach()

  if(NOT FOUND_DLL)
    get_filename_component(DLL_NAME ${FIRST_DLL} NAME)
    message(WARNING "Could not find ${DLL_NAME}, you'll need to copy it yourself.")
  endif()
endmacro(copy_dll)
