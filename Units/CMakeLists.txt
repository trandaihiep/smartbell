cmake_minimum_required(VERSION 3.0.0)
project(Units)

include(CTest)
enable_testing()

include_directories(${Units_SOURCE_DIR}
			${STDBOOL_H_PATH} ${STDINT_H_PATH}
			${OPENSSL_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})

add_library(Units SHARED
	CameraHandler.cpp CameraHandler.h
	MQTTConnector.cpp MQTTConnector.h
	mosquittopp.cpp mosquittopp.h
	)

#add_executable(test_Units test_Units.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (UNIX)
	install(CODE "EXEC_PROGRAM(/sbin/ldconfig)")
endif (UNIX)


target_compile_options( Units PUBLIC -std=c++11 -fpermissive -w -Wall )

#target_link_libraries( main_test Units -L/usr/lib64 -ldl )
target_link_libraries( Units Logging SmartBell libmosquitto )