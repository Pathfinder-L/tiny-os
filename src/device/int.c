/*int.c*/

/* 妱傝崬傒娭學 */

#include "../header/main.h"

extern struct BOOTINFO *bootInfo;

void init_pic(void)
/* PIC初始化 */
{
    io_out8(PIC0_IMR, 0xff); /* 禁止所有的中断 */
    io_out8(PIC1_IMR, 0xff); /* 禁止所有的中断 */

    io_out8(PIC0_ICW1, 0x11); /* 边沿触发模式 */
    io_out8(PIC0_ICW2, 0x20); /* IPQ0-7由INT20-27接收 */
    io_out8(PIC0_ICW3, 1 << 2); /* PIC1由IRQ连接 */
    io_out8(PIC0_ICW4, 0x01); /* 无缓冲模式 */

    io_out8(PIC1_ICW1, 0x11); /* 边沿触发模式 */
    io_out8(PIC1_ICW2, 0x28); /* IRQ8-15由INT28-2F接收 */
    io_out8(PIC1_ICW3, 2); /* PIC1由IRQ2连接 */
    io_out8(PIC1_ICW4, 0x01); /* 无缓冲模式*/

    io_out8(PIC0_IMR, 0xfb); /* 11111011 PIC1外所有中断被禁止 */
    io_out8(PIC1_IMR, 0xff); /* 11111111 禁止所有中断*/
    return;
}


void inthandler27(int *esp)
{
    io_out8(PIC0_OCW2, 0x67);
    return;
}


