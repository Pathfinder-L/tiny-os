/*keyboard.c*/

#include "../main.h"

extern struct BOOTINFO *bootInfo;
struct FIFO *keyfifo;
int key_offset;

char tmp[12];

void inthandler21(int *esp) {
    int data;
    io_out8(PIC0_OCW2, 0x61);
    data = io_in8(PORT_KEYDAT);

//    sprintf(tmp, "e:%p%d", keyfifo, key_offset);
//    putStr(bootInfo->vram, bootInfo->scrnx, 0, 40, COL8_000000, tmp);
//    fifo8_put(keyfifo, data + key_offset);
    return;
}


void wait_KBC_sendready(void) {
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    return;
}

//void init_keyboard(void)
//{
//    wait_KBC_sendready();
//    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
//    wait_KBC_sendready();
//    io_out8(PORT_KEYDAT, KBC_MODE);
//    return;
//}

void init_keyboard(struct FIFO32 *kq, int offset) {
    keyfifo = kq;
    key_offset = offset;

    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}
