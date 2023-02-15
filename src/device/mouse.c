/*鼠标*/
#include "../main.h"
extern struct BOOTINFO *bootInfo;
// 将数据加入偏置 放入一个队列里面
void inthandler2c(int *esp) {
    int data;
    io_out8(PIC1_OCW2, 0x64);
    io_out8(PIC0_OCW2, 0x62);
    data = io_in8(PORT_KEYDAT);
    putStr(bootInfo->vram,bootInfo->scrnx,0,80,COL8_000000,"mouse");
    return;
}

#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4

void enable_mouse()
{

    wait_KBC_sendready();
    putStr(bootInfo->vram,bootInfo->scrnx,40,0,COL8_000000,"st1");
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
    wait_KBC_sendready();
    putStr(bootInfo->vram,bootInfo->scrnx,40,20,COL8_000000,"st2");
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
    return;
}
