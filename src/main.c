/***********************************************************
  > File Name: main.c
  > Author: admin
  > Mail:2185845875@qq.com
  > Created Time: 2023/2/14 14:27:42
    > Modified Time:2023/2/14 14:28:12
 *******************************************************/

#include "main.h"

extern struct BOOTINFO *bootInfo;

struct FIFO32 *fifo;

void init() {
    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);
    init_palette();
    init_gdtidt();
    init_pic();
    io_sti();


//    struct FIFO32 dataStream;
//    int dataBuf[128];
//    fifo32_init(&dataStream, 128, dataBuf);
//    init_keyboard(&dataStream, 256); // 开启鼠标之前必须激活键盘电路
//    enable_mouse(&dataStream, 512);
//    fifo = &dataStream;
    char s[24];
    int memtotal = memtest(0x00400000,0xbfffffff);

    sprintf(s, "memory %dMB",
            memtotal / (1024 * 1024));
    putStr(bootInfo->vram, bootInfo->scrnx, bootInfo->scrnx / 2, bootInfo->scrny / 2, COL8_000000, s);
    io_out8(PIC0_IMR, 0xf9);
    io_out8(PIC1_IMR, 0xef);


}
// 没有加入内存 ！！
// todo: 0.将数据放入队列  t: 测试数据是否放入成功
//       1.解析鼠标数据
//       2.解析键盘数据



void HariMain(void) {
    init();

    char s[32];
//    int size = fifo32_status(fifo);
//    sprintf(s, "size:%d", size);
//    boxfill(bootInfo->vram, bootInfo->scrnx, COL8_008484, bootInfo->scrnx / 2, bootInfo->scrny / 2,
//            bootInfo->scrnx / 2 + 8 * 5, bootInfo->scrny / 2 + 16);
//    putStr(bootInfo->vram, bootInfo->scrnx, bootInfo->scrnx / 2, bootInfo->scrny / 2, COL8_000000, s);
    for (;;) {

    }
}

