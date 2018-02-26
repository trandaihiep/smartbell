cmake_minimum_required(VERSION 3.0.0)
project(Logging)

include(CTest)
enable_testing()

include_directories(${Logging_SOURCE_DIR}
			${STDBOOL_H_PATH} ${STDINT_H_PATH}
			${OPENSSL_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})

add_library(Logging SHARED
            Logging.cpp Logging.h
            LogHandler.cpp LogHandler.h)

add_executable(test_log test_log.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (UNIX)
	install(CODE "EXEC_PROGRAM(/sbin/ldconfig)")
endif (UNIX)


target_compile_options( Logging PUBLIC -std=c++11 -fpermissive -w -Wall )

target_link_libraries( test_log Logging -L/usr/lib64 -ldl )
# target_link_libraries( test_log Logging )