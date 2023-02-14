/*鼠标*/
#include "../main.h"
// 将数据加入偏置 放入一个队列里面
void inthandler2c(int *esp) {
    int data;
    io_out8(PIC1_OCW2, 0x64);
    io_out8(PIC0_OCW2, 0x62);
    data = io_in8(PORT_KEYDAT);
    return;
}
