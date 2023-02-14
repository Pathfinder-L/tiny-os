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
    init_palette();
    init_gdtidt();
}


void HariMain(void) {
    init();

    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);
    putStr(bootInfo->vram, bootInfo->scrnx, 0, 0, COL8_FFFFFF, "hello");
    for (;;)
        io_hlt();
}

