cmake_minimum_required(VERSION 3.0.0)
project(SmartBell VERSION 0.0.0)
# The version number.
set (SmartBell_VERSION_MAJOR 1)
set (SmartBell_VERSION_MINOR 0)

#add_subdirectory(lib/mosq) 
add_subdirectory(Logging) 
add_subdirectory(Serialize)
add_subdirectory(Units)
add_subdirectory(Utilities)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/SmartBell.h.in"
#  "${PROJECT_BINARY_DIR}/SmartBell.h"
#  )

include(CTest)
enable_testing()
# Adding libraries

include_directories(${SmartBell_SOURCE_DIR}
  #${SmartBell_SOURCE_DIR}/lib
  ${SmartBell_SOURCE_DIR}/Logging
  ${SmartBell_SOURCE_DIR}/Serialize
  ${SmartBell_SOURCE_DIR}/Units
  ${SmartBell_SOURCE_DIR}/Utilities
  ${STDBOOL_H_PATH} ${STDINT_H_PATH}
  ${OPENSSL_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})

add_executable(SmartBell main.cpp main.h)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


target_compile_options( SmartBell PUBLIC -std=c++11 -fpermissive -w -Wall )

#target_link_libraries( main_test Logging -L/usr/lib64 -ldl )
target_link_libraries( SmartBell Logging -L/usr/lib64 -ldl )
# Allow -DLIB_INSTALL_DIR=<path> to be passed on the command line
  if(NOT DEFINED LIB_INSTALL_DIR)
      set(LIB_INSTALL_DIR lib)
  endif()

# install(TARGETS SmartBell 
#   RUNTIME DESTINATION "${BINDIR}" 
#   LIBRARY DESTINATION ${LIB_INSTALL_DIR})