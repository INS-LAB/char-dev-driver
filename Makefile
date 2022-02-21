obj-m := skeleton.o

KDIR := /home/  # 타겟 시스템 커널 경로 작성
PWD := $(shell pwd)
 
default:
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C$(KDIR) M=$(PWD) modules
 
clean:
    make -C$(KDIR) M=$(PWD) clean
