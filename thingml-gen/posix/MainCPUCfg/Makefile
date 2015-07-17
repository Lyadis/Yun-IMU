CC = cc
LIBS = -lpthread 
CFLAGS = -O2 -w
SRCS = WSServer.c HTTPServer.c LinuxSerial2.c Bridge.c MainCPUCfg.c runtime.c
OBJS = WSServer.o HTTPServer.o LinuxSerial2.o Bridge.o MainCPUCfg.o runtime.o

all : MainCPUCfg

.c.o :
	${CC} ${CFLAGS} -c $< 

MainCPUCfg : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) -lm

clean:
	rm -f *.o *~ MainCPUCfg