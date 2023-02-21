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


// todo: 1. 解析鼠标数据 绘制 鼠标
//

void HariMain(void) {

    struct FIFO32 fifo;
    struct TIMER *timer, *timer2, *timer3;
    int fifobuf[128];
    char s[12];
    char mouseBuf[256];
    struct SHTCTL *shtctl;
    struct SHEET *sht_back, *sht_mouse;
    unsigned char *buf_back, *buf_mouse;
    struct MOUSE_DEC mouseDec;

    init_mem();

    shtctl = shtctl_init(memmanager, bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);
    sht_back = sheet_alloc(shtctl);
    sht_mouse = sheet_alloc(shtctl);

    buf_back = (unsigned char *) alloc4k(memmanager, bootInfo->scrnx * bootInfo->scrny);
    buf_mouse = (unsigned char *) alloc4k(memmanager, 16 * 16);

    sheet_setbuf(sht_back, buf_back, bootInfo->scrnx, bootInfo->scrny, COLOR_INV);
    sheet_setbuf(sht_mouse, buf_mouse, 16, 16, COLOR_INV);
    init_screen(buf_back, bootInfo->scrnx, bootInfo->scrny);
    init_mouse_cursor(buf_mouse);

    mouseDec.x = 0;
    mouseDec.y = 0;
    mouseDec.sx = (bootInfo->scrnx - 16) / 2;
    mouseDec.sy = (bootInfo->scrny - 16) / 2;
    sheet_slide(sht_back, 0, 0);
    sheet_slide(sht_mouse, mouseDec.sx, mouseDec.sy);

    sheet_updown(sht_back, 1);
    sheet_updown(sht_mouse, 2);

    init_gdtidt();
    init_pic();
    io_sti();
    init_pit();
    fifo32_init(&fifo, 128, fifobuf);
    init_keyboard(&fifo, 256);
    init_mouse_cursor(mouseBuf);


    enable_mouse(&fifo, 512);
    dataStream = &fifo;

    io_out8(PIC0_IMR, 0xf8);
    io_out8(PIC1_IMR, 0xef);


    init_palette();
    //  init_screen(bootInfo->vram, bootInfo->scrnx, bootInfo->scrny);


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
            // 鼠标数据
            if (data >= 512) {
                data -= 512;
                mouse_decode(&mouseDec, data);
                mouseDec.sx += mouseDec.x;
                mouseDec.sy += mouseDec.y;
                sheet_slide(sht_mouse, mouseDec.sx, mouseDec.sy);
            } else if (data >= 256 && data <= 511) {

            } else {

            }
        }
    }
}

