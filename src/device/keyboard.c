/*keyboard.c*/

#include "../main.h"

extern struct BOOTINFO *bootInfo;
int offset_keyboard;
struct Queue *kq;

void inthandler21(int *esp) {
    int data;
    io_out8(PIC0_OCW2, 0x61);    /* IRQ-01��t������PIC�ɒʒm */
    data = io_in8(PORT_KEYDAT);
    return;
}

