KERNELDIR=/lib/modules/`uname -r`/build

# This the the Makefile for the device driver (not your demonstration program)

#Change the base name here to your module file name - no extension
BASENAME=helloworld


MODULES =secure_notes.ko 
obj-m +=secure_notes.o 

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean

install:	
	make -C $(KERNELDIR) M=$(PWD) modules_install

quickInstall:
	cp $(MODULES) /lib/modules/`uname -r`/extra
