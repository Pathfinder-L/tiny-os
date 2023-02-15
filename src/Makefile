TOOLPATH = ../tools/
TOP      = $(CURDIR)
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
BOOTPATH = $(TOP)/boot/
GRAPHICPATH =$(TOP)/graphic/
CONFIGPATH = $(TOP)/config/
DEVICEPATH = $(TOP)/device/
STRUCTRUEPATH = $(TOP)/structrue/

COPY     = copy
DEL      = del

CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
NASK     = $(TOOLPATH)nask.exe
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
RULEFILE = $(TOP)\config\haribote.rul
BIM2HRB  = $(TOOLPATH)\bim2hrb.exe

OBJS = main.obj $(BOOTPATH)nasfunc.obj  \
		 $(CONFIGPATH)config.obj   $(CONFIGPATH)fonts.obj $(CONFIGPATH)memory.obj \
		 $(GRAPHICPATH)draw.obj \
		 $(DEVICEPATH)keyboard.obj $(DEVICEPATH)mouse.obj $(DEVICEPATH)int.obj $(DEVICEPATH)dsctbl.obj 	 \
		 $(STRUCTRUEPATH)fifo.obj



%.gas : %.c main.h Makefile
	$(CC1) -o $*.gas $*.c -std=c99

%.nas : %.gas Makefile
	$(GAS2NASK) $*.gas $*.nas

%.obj : %.nas Makefile
	$(NASK) $*.nas $*.obj $*.lst


$(BOOTPATH)ipl.bin: $(BOOTPATH)ipl.nas Makefile
	 $(NASK) $(BOOTPATH)ipl.nas $(BOOTPATH)ipl.bin

$(BOOTPATH)basic.bin: $(BOOTPATH)basic.nas Makefile
	$(NASK) $(BOOTPATH)basic.nas $(BOOTPATH)basic.bin

main.bim : $(OBJS) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:main.bim stack:3136k map:main.map \
		  $(OBJS)
# 3MB+64KB=3136KB

main.hrb :main.bim Makefile
	$(BIM2HRB) main.bim main.hrb 0

os.sys:$(BOOTPATH)basic.bin main.hrb Makefile
	copy /B .\boot\basic.bin+.\main.hrb os.sys

os.img :$(BOOTPATH)ipl.bin os.sys Makefile
	$(EDIMG)  imgin:../tools/fdimg0at.tek \
		wbinimg src:$(BOOTPATH)ipl.bin len:512 from:0 to:0 \
					copy from:os.sys to:@: \
							imgout:os.img


asm :
	$(MAKE) ipl.bin

img :
	$(MAKE) os.img

run :
	$(MAKE) img
	$(COPY) os.img ..\tools\qemu\fdimage0.bin
	$(MAKE) -C ../tools/qemu

install :
	$(MAKE) img
	$(IMGTOL) w a: os.img

clean :
	-$(DEL) ipl.bin
	-$(DEL) ipl.lst
	-$(DEL) main.map
	-$(DEL) main.bim
	-$(DEL) main.hrb
	-$(DEL) main.nas
	-$(DEL) *.gas
	-$(DEL) *.lst
	-$(DEL) *.obj
	-$(DEL) os.sys
	-$(DEL) os.img
	-$(DEL) .\config\config.obj
	-$(DEL) .\config\config.lst
	-$(DEL) .\device\dsctbl.lst
	-$(DEL) .\device\dsctbl.obj
	-$(DEL) .\device\keyboard.obj
	-$(DEL) .\device\keyboard.lst
	-$(DEL) .\device\mouse.lst
	-$(DEL) .\device\mouse.obj



src_only :
	$(MAKE) clean
	$(DEL) os.img

