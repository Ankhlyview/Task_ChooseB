# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_detect_card_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED detect_card_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(detect_card_FOUND FALSE)
  elseif(NOT detect_card_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(detect_card_FOUND FALSE)
  endif()
  return()
endif()
set(_detect_card_CONFIG_INCLUDED TRUE)

# output package information
if(NOT detect_card_FIND_QUIETLY)
  message(STATUS "Found detect_card: 0.0.0 (${detect_card_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'detect_card' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT detect_card_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(detect_card_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${detect_card_DIR}/${_extra}")
endforeach()
