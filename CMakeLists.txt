cmake_minimum_required(VERSION 3.16)


project(compressedarray VERSION 1.0.0 LANGUAGES C)

add_library(compressedarray
    src/compressedarray.c
    src/textutil.c
)
add_library(comparr::Lib ALIAS compressedarray)
set_target_properties(compressedarray PROPERTIES
    OUTPUT_NAME compressedarray
    EXPORT_NAME compressedarray
)

target_include_directories(compressedarray PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers) 

configure_package_config_file(
  "cmake/compressedarrayConfig.cmake.in"
  "compressedarrayConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/compressedarray"
)

install(
    TARGETS compressedarray 
    EXPORT compressedarrayTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
        PATTERN "*.h"
)
install(EXPORT compressedarrayTargets
    FILE compressedarrayTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/compressedarray
    NAMESPACE comparr::
)
write_basic_package_version_file( 
  "compressedarrayConfigVersion.cmake" 
  VERSION ${PROJECT_VERSION} 
  COMPATIBILITY AnyNewerVersion 
)
install(FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/compressedarrayConfig.cmake" 
  "${CMAKE_CURRENT_BINARY_DIR}/compressedarrayConfigVersion.cmake" 
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/compressedarray" 
)