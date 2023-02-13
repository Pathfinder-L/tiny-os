TOOLPATH = ../tools/
TOP      = $(CURDIR)
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
BOOTPATH = $(TOP)/boot/
COPY     = copy
DEL      = del


default :
	$(MAKE) img


ipl.bin : $(BOOTPATH)ipl.nas Makefile
	$(NASK) $(BOOTPATH)ipl.nas ipl.bin ipl.lst

os.img : ipl.bin Makefile
	$(EDIMG)   imgin:../tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:os.img


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

src_only :
	$(MAKE) clean
	-$(DEL) os.img

