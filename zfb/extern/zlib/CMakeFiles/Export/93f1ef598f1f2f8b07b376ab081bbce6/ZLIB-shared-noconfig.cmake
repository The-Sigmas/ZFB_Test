#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ZLIB::ZLIB" for configuration ""
set_property(TARGET ZLIB::ZLIB APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ZLIB::ZLIB PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libz.so.1.4.1.1"
  IMPORTED_SONAME_NOCONFIG "libz.so.1"
  )

list(APPEND _cmake_import_check_targets ZLIB::ZLIB )
list(APPEND _cmake_import_check_files_for_ZLIB::ZLIB "${_IMPORT_PREFIX}/lib/libz.so.1.4.1.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
