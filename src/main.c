/***********************************************************
  > File Name: main.c
  > Author: admin
  > Mail:2185845875@qq.com
  > Created Time: 2023/2/14 14:27:42
    > Modified Time:2023/2/14 14:28:12
 *******************************************************/

#include "main.h"

extern struct BOOTINFO *bootInfo;


void init() {
    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);
    init_palette();
    init_gdtidt();
    init_pic();
    io_sti();
    io_out8(PIC0_IMR, 0xf9);
    io_out8(PIC1_IMR, 0xef);

    init_keyboard(); // 开启鼠标之前必须激活键盘电路
    enable_mouse();


}


void HariMain(void) {
    init();


    for (;;)
        io_hlt();
}

