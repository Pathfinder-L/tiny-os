/***********************************************************
  > File Name: main.c
  > Author: admin
  > Mail:2185845875@qq.com
  > Created Time: 2023/2/14 14:27:42
    > Modified Time:2023/2/14 14:28:12
 *******************************************************/

#include "main.h"

void init() {
    init_palette();
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}

void init_screen(unsigned char *vram, int x, int y) {
    // 大上部分
    boxfill8(vram, x, COL8_008484, 0, 0, x, y - 20);

    boxfill8(vram, x, COL8_00FFFF, x / 2 - 6, y - 16, x / 2 + 6, y - 4);

    //COL8_000000
    boxfill8(vram, x, COL8_000000, x / 2 - 6, y - 10,
            x / 2 + 6, y - 10);
    boxfill8(vram, x, COL8_000000, x / 2, y - 16,
            x / 2, y - 4);
}



void HariMain(void) {
    init();

    char *vram;
    int xsize, ysize;
    short *binfo_scrnx, *binfo_scrny;
    int *binfo_vram;

    init_palette();
    binfo_scrnx = (short *) 0x0ff4;
    binfo_scrny = (short *) 0x0ff6;
    binfo_vram = (int *) 0x0ff8;
    xsize = *binfo_scrnx;
    ysize = *binfo_scrny;
    vram = (char *) *binfo_vram;

    init_screen(vram, xsize, ysize);
    for (;;)
        io_hlt();
}

