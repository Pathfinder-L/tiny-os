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
    struct TIMER *timer, *timer2, *timer3;
    int fifobuf[128];
    char s[12];


    init_gdtidt();
    init_pic();
    io_sti();
    init_pit();
    fifo32_init(&fifo, 128, fifobuf);
    init_keyboard(&fifo, 256);
    enable_mouse(&fifo, 512);
    dataStream = &fifo;

    io_out8(PIC0_IMR, 0xf8);
    io_out8(PIC1_IMR, 0xef);

    init_mem();
    init_palette();
    init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);


    timer = timer_alloc();
    timer_init(timer, &fifo, 10);
    timer_settime(timer, 1000);
    timer2 = timer_alloc();
    timer_init(timer2, &fifo, 3);
    timer_settime(timer2, 300);
    timer3 = timer_alloc();
    timer_init(timer3, &fifo, 1);
    timer_settime(timer3, 500);

    putStr(bootInfo->vram, bootInfo->scrnx, 0, 0, COL8_000000, s);
    for (;;) {
        if (fifo32_status(dataStream) != 0) {
            int data = fifo32_get(dataStream);
            if (data > 100) {
                boxfill(bootInfo->vram, bootInfo->scrnx, COL8_008484, 20, 30, 100, 50);
                sprintf(s, "e:%d", data);
                putStr(bootInfo->vram, bootInfo->scrnx, 20, 30,
                       COL8_000000, s);
            }else if(data == 1)
            {
                boxfill(bootInfo->vram, bootInfo->scrnx, COL8_008484, 50, 40, 100, 50);
                putStr(bootInfo->vram, bootInfo->scrnx, 50, 40,
                       COL8_000000, "5sec");
            }
        }
    }
}

