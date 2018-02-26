CFLAGS=-Wall -ggdb -ILogging -ISerialize -IUnits -IUtilities
LDFLAGS=-Llib lib/cpp/libmosquittopp.so.1 lib/libmosquitto.so.1 -lpthread

DIRS=Logging Serialize Units Utilities

LOGGING_OBJS=LogHandler.o

SERIALIZE_OBJS=BellData.o\
				CameraData.o\
				SmartBellData.o
UNIT_OBJS=CameraHandler.o\
				ClientAPI.o\
				MQTTConnector.o

.PHONY: all smartbell clean

all: smartbell

# smartbelllib :
# 	set -e; for d in ${DIRS}; do $(MAKE) -C $${d}; done

smartbell: main.o 
	Logging Serialize Units
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`

# Logging
Logging: ${LOGGING_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
LogHandler.o : Logging/LogHandler.cpp Logging/LogHandler.h
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
Logging.o : Logging/Logging.cpp Logging/Logging.h
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`

# Serialize
Serialize: ${SERIALIZE_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
BellData.o : Serialize/BellData.cpp Serialize/BellData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@
CameraData.o : Serialize/CameraData.cpp Serialize/CameraData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@
SmartBellData.o : Serialize/SmartBellData.cpp Serialize/SmartBellData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@

#Units
Units: ${UNIT_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
CameraHandler.o : Units/CameraHandler.cpp  CameraHandler.h 
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
ClientAPI.o : Units/ClientAPI.cpp  ClientAPI.h  
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
MQTTConnector.o : Units/MQTTConnector.cpp  MQTTConnector.h
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`


main.o: main.cpp
	${CXX} -c -std=c++11 `pkg-config --cflags opencv` $^ -o $@ ${CFLAGS}
clean : 
	-rm -f *.o fds
