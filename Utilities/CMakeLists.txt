cmake_minimum_required(VERSION 3.0.0)
project(Ultilities)

include(CTest)
enable_testing()

include_directories(${Ultilities_SOURCE_DIR}
			${STDBOOL_H_PATH} ${STDINT_H_PATH}
			${OPENSSL_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})

add_library(Ultilities SHARED
	util.cpp util.h)

#add_executable(main_test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (UNIX)
	install(CODE "EXEC_PROGRAM(/sbin/ldconfig)")
endif (UNIX)


target_compile_options( Ultilities PUBLIC -std=c++11 -fpermissive -w -Wall )

#target_link_libraries( main_test Ultilities -L/usr/lib64 -ldl )
#target_link_libraries( main_test Ultilities )