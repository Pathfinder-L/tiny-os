TOOLPATH = ../tools/
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del


default :
	$(MAKE) img


ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

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
