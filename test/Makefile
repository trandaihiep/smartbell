CFLAGS=-Wall -ggdb -I../Serialize -I../Units
LDFLAGS= -L. 

.PHONY: all clean

all: testcamera

testcamera: testcamera.o CameraData.o CameraHandler.o 
	${CXX} $^ -o $@ ${LDFLAGS} `pkg-config --libs opencv` -lstdc++fs
testcurl: testcurl.o ClientAPI.o CameraData.o BellData.o
	${CXX} $^ -o $@ ${LDFLAGS} -lcurl `pkg-config --libs opencv` `pkg-config --libs RapidJSON`
testcurl.o: test_curl.cpp
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
ClientAPI.o: ../Units/ClientAPI.cpp
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS} `pkg-config --cflags RapidJSON`
testcamera.o: test_camera.cpp 
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
BellData.o: ../Serialize/BellData.cpp
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
CameraData.o: ../Serialize/CameraData.cpp
	${CXX} -c -std=c++11 $^ -o $@ ${CFLAGS}
CameraHandler.o: ../Units/CameraHandler.cpp
	${CXX} -c -std=c++11 $^ -I/usr/local/include/opencv -I/usr/local/include -o $@ ${CFLAGS} 
clean :
	-rm -f *.o testcurl testcamera
