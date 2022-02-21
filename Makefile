obj-m = this_device_name.o
 
KDIR := /home/user1/pi/linux
PWD := $(shell pwd)
 
default:
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KDIR) SUBDIRS=$(PWD) modules
 
clean:
    make -C $(KDIR) SUBDIRS=$(PWD) clean