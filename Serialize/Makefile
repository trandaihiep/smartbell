.PHONY: all clean

SERIALIZE_OBJS=BellData.o\
				CameraData.o\
				SmartBellData.o

all : serializedata.so serializedata.a


serializedata.so.${SOVERSION} : ${SERIALIZE_OBJS}
	${CROSS_COMPILE}$(CC) -shared $(LIB_LDFLAGS) $^ -o $@ ${LIB_LIBS}

serializedata.a : ${SERIALIZE_OBJS}
	${CROSS_COMPILE}$(AR) cr $@ $^
BellData.o : BellData.c BellData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@

CameraData.o : CameraData.c CameraData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@

SmartBellData.o : SmartBellData.c SmartBellData.h
	${CROSS_COMPILE}$(CC) $(LIB_CFLAGS) -c $< -o $@

clean :
	-rm -f *.o *.a
