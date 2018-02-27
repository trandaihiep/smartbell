CFLAGS=-Wall -ggdb -ILogging -ISerialize -IUnits -IUtilities -Ilib/mosq/cpp  -Ilib/mosq
LDFLAGS=-Llib lib/mosq/cpp/libmosquittopp.so.1 lib/mosq/libmosquitto.so.1 -lpthread

DIRS=Logging Serialize Units

LOGGING_OBJS=LogHandler.o\
				Logging.o

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

# smartbell: main.o Logging Serialize Units
smartbell: main.o ${LOGGING_OBJS} ${SERIALIZE_OBJS} ${UNIT_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS} ${CFLAGS} `pkg-config --libs opencv` -lcurl -lstdc++fs

# Logging
Logging: ${LOGGING_OBJS}
	# ${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv`
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
LogHandler.o : Logging/LogHandler.cpp #Logging/LogHandler.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
Logging.o : Logging/Logging.cpp #Logging/Logging.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}

# Serialize
Serialize: ${SERIALIZE_OBJS}
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
BellData.o : Serialize/BellData.cpp #Serialize/BellData.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
CameraData.o : Serialize/CameraData.cpp #Serialize/CameraData.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
SmartBellData.o : Serialize/SmartBellData.cpp #Serialize/SmartBellData.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}

#Units
Units: ${UNIT_OBJS}
	${CXX} -c -std=c++11 $^ -I/usr/local/include/opencv -I/usr/local/include -o $@ ${CFLAGS}
CameraHandler.o : Units/CameraHandler.cpp  #Units/CameraHandler.h 
	${CXX} -c -std=c++11 $^ -I/usr/local/include/opencv -I/usr/local/include -o $@ ${CFLAGS} 
ClientAPI.o : Units/ClientAPI.cpp  #Units/ClientAPI.h  
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS} `pkg-config --cflags RapidJSON`
MQTTConnector.o : Units/MQTTConnector.cpp  #Units/MQTTConnector.h
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}


main.o: main.cpp
	${CXX} -c -std=c++11 `pkg-config --cflags opencv` $^ -o $@ ${CFLAGS}
clean : 
	-rm -f *.o smartbell
