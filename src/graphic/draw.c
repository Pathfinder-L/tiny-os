

/*管理一切的绘图问题*/
#include "../main.h"

/*配置调色板*/
void set_palette(int start, int end, unsigned char *rgb) {
    int i, eflags;
    eflags = io_load_eflags();    /* 记录中断许可标志的值 */
    io_cli();                    /* 将中断标志设置为0，禁止中断*/
    io_out8(0x03c8, start);
    for (i = start; i <= end; i++) {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }
    io_store_eflags(eflags);    /* 复原中断许可标志 */
}

void init_palette(void) {
    // 初始化调色板
    static unsigned char table_rgb[16 * 3] = {
            0x00, 0x00, 0x00,    /*  0:黑*/
            0xff, 0x00, 0x00,    /*  1:亮红色*/
            0x00, 0xff, 0x00,    /*  2:亮绿色*/
            0xff, 0xff, 0x00,    /*  3:亮黄色*/
            0x00, 0x00, 0xff,    /*  4:亮蓝色*/
            0xff, 0x00, 0xff,    /*  5:亮紫色*/
            0x00, 0xff, 0xff,    /*  6:浅亮蓝*/
            0xff, 0xff, 0xff,    /*  7:白色*/
            0xc6, 0xc6, 0xc6,    /*  8:亮灰*/
            0x84, 0x00, 0x00,    /*  9:暗红色*/
            0x00, 0x84, 0x00,    /* 10:暗绿色*/
            0x84, 0x84, 0x00,    /* 11:暗黄色*/
            0x00, 0x00, 0x84,    /* 12:暗青色*/
            0x84, 0x00, 0x84,    /* 13:暗紫色*/
            0x00, 0x84, 0x84,    /* 14:前暗色*/
            0x84, 0x84, 0x84    /* 15:暗灰色*/
    };
    set_palette(0, 15, table_rgb);
    return;

    /* static char 定义*/
}

/*初始化主屏幕*/
void init_screen(unsigned char *vram, int x, int y) {
    // 大上部分
    boxfill(vram, x, COL8_008484, 0, 0, x, y - 20);
    boxfill(vram, x, COL8_00FFFF, x / 2 - 6, y - 16, x / 2 + 6, y - 4);
    //COL8_000000
    boxfill(vram, x, COL8_000000, x / 2 - 6, y - 10,
            x / 2 + 6, y - 10);
    boxfill(vram, x, COL8_000000, x / 2, y - 16,
            x / 2, y - 4);
}

/*启动信息*/
void init_bootInfo() {

}

void boxfill(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}

