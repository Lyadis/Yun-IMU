CC = mips-openwrt-linux-gcc
LIBS = -lpthread 
CFLAGS = -O2 -w
SRCS = LinuxSerial2.c HTTPServer.c Bridge.c MainCPUCfg.c runtime.c
OBJS = LinuxSerial2.o HTTPServer.o Bridge.o MainCPUCfg.o runtime.o

all : MainCPUCfg

.c.o :
	${CC} ${CFLAGS} -c $< 

MainCPUCfg : $(OBJS)
	$(CC) -o $@ $(OBJS) /openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib/libmicrohttpd.a $(LIBS) -lm

clean:
	rm -f *.o *~ MainCPUCfg
