.PHONY: all, clean

obj-m := ssd1306_lcd_driver.o
ssd1306_lcd_driver-objs = ssd1306_lib.o ssd1306_driver.o

BBB_KERNEL := /home/gia/working_space/BBB/kernelbuildscripts/KERNEL/
TOOLCHAIN  := /home/gia/working_space/BBB/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

driver:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(PWD) modules

user_app:
	arm-linux-gnueabihf-gcc -o user_app user_app.c 

clean:
	make -C $(BBB_KERNEL) M=$(PWD) clean
	rm -rf user_app


