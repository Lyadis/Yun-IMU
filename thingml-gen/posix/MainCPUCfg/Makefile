LIBS = -lpthread -lmicrohttpd -lwebsockets -lssl -lcrypto -lz -L/openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/lib -L/openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib -L/openwrt-yun/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib -L/openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/yun-gcc/lib/

CFLAGS = -O2 -w -I/openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include -I/openwrt-yun/staging_dir/target-mips_r2_uClibc-0.9.33.2/include

SRCS = WSServer.c HTTPServer.c Bridge.c LinuxSerial2.c MainCPUCfg.c runtime.c
OBJS = WSServer.o HTTPServer.o Bridge.o LinuxSerial2.o MainCPUCfg.o runtime.o 

all : MainCPUCfg

.c.o :
	${CC} ${CFLAGS} -c $< 

MainCPUCfg : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) -lm

clean:
	rm -f *.o *~ MainCPUCfg
