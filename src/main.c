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
}


void HariMain(void) {
    init();


    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);
    for (;;)
        io_hlt();
}

