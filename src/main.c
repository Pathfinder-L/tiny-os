/***********************************************************
  > File Name: main.c
  > Author: admin
  > Mail:2185845875@qq.com
  > Created Time: 2023/2/14 14:27:42
    > Modified Time:2023/2/14 14:28:12
 *******************************************************/

#include "main.h"

extern struct BOOTINFO *bootInfo;
extern struct MEMMANAGER *memmanager;
struct MOUSE_DEC mdec;
struct FIFO32 *dataStream;
// 没有加入内存 ！！
// todo: 0.将数据放入队列  t: 测试数据是否放入成功
//       1.解析鼠标数据
//       2.解析键盘数据

void HariMain(void) {

    struct FIFO32 fifo;
    int fifobuf[128];
    char s[12];


    init_gdtidt();
    init_pic();
    io_sti();
    fifo32_init(&fifo, 128, fifobuf);
    init_keyboard(&fifo, 256);
    enable_mouse(&fifo, 512);
    dataStream = &fifo;

    io_out8(PIC0_IMR, 0xf9);
    io_out8(PIC1_IMR, 0xef);

    init_mem();
    init_palette();
    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);

    int memtotal = memtest(0x00400000, 0xbfffffff);

    /*测试bootInfo*/
    int xSize = bootInfo->scrnx;
    int ySize = bootInfo->scrny;
    sprintf(s, "(%d,%d)",
            xSize, ySize);
    putStr(bootInfo->vram, bootInfo->scrnx, bootInfo->scrnx / 2, bootInfo->scrny / 2, COL8_000000, s);

    /*测试分配内存*/
    sprintf(s, "address:%p", memmanager);
    putStr(bootInfo->vram, bootInfo->scrnx, 0, 0, COL8_000000, s);
    for (;;) {
        io_cli();
        if (fifo32_status(dataStream) == 0) {
            io_sti();
        } else {
            int data = fifo32_get(dataStream);
            boxfill(bootInfo->vram, bootInfo->scrnx, COL8_008484, 20, 30, 100, 50);
            sprintf(s, "e:%d", data);
            putStr(bootInfo->vram, bootInfo->scrnx, 20, 30,
                   COL8_000000, s);
        }
    }
}

