/*keyboard.c*/

#include "../main.h"

extern struct BOOTINFO *bootInfo;

void inthandler21(int *esp) {
    int data;
    io_out8(PIC0_OCW2, 0x61);
    data = io_in8(PORT_KEYDAT);
    putStr(bootInfo->vram,bootInfo->scrnx,0,40,COL8_000000,"KEY");
    return;
}


void wait_KBC_sendready(void)
{
    putStr(bootInfo->vram,bootInfo->scrnx,30,40,COL8_000000,"bef");
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    putStr(bootInfo->vram,bootInfo->scrnx,30,60,COL8_000000,"aft");
    return;
}

void init_keyboard(void)
{
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}
