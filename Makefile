CC=/home/craig/Documents/craigs/beaglebone/cross-compiler/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/arm-linux-gnueabihf-gcc
CFLAGS= -c  -g -Wall
LDFLAGS=-lrt -lpthread -g -lm

all: hello_beagleblack updatetelemetryd

updatetelemetryd: updatetelemetryd.o

updatetelemetryd.o:
		$(CC) $(CFLAGS) updatetelemetryd.c

hello_beagleblack: hello_beagleblack.o

hello_beagleblack.o:
		$(CC) $(CFLAGS) hello_beagleblack.c

clean:
	rm hello_beagleblack hello_beagleblack.o updatetelemetryd updatetelemetryd.o