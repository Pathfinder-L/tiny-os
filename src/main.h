#define MAX_SHEET  256
#define true 1
#define false 0

/*定义颜色*/
#define COL8_000000        0
#define COL8_FF0000        1
#define COL8_00FF00        2
#define COL8_FFFF00        3
#define COL8_0000FF        4
#define COL8_FF00FF        5
#define COL8_00FFFF        6
#define COL8_FFFFFF        7
#define COL8_C6C6C6        8
#define COL8_840000        9
#define COL8_008400        10
#define COL8_848400        11
#define COL8_000084        12
#define COL8_840084        13
#define COL8_008484        14
#define COL8_848484        15

/*int.c*/
#define PIC0_ICW1        0x0020
#define PIC0_OCW2        0x0020
#define PIC0_IMR        0x0021
#define PIC0_ICW2        0x0021
#define PIC0_ICW3        0x0021
#define PIC0_ICW4        0x0021
#define PIC1_ICW1        0x00a0
#define PIC1_OCW2        0x00a0
#define PIC1_IMR        0x00a1
#define PIC1_ICW2        0x00a1
#define PIC1_ICW3        0x00a1
#define PIC1_ICW4        0x00a1


struct BOOTINFO {
    char cyls;  /*启动区读硬盘何处为止*/
    char leads; /*启动键盘的LED的状态*/
    char vmode; /*显卡多少多少位颜色*/
    char reserve;
    short scrnx, scrny; /*画面分辨率*/
    char *vram;
};

/*多认为*/
struct TSS32 {
    int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
    int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    int es, cs, ss, ds, fs, gs;
    int ldtr, iomap;
};


/*nasfunc.nas*/
void io_hlt(void);

void io_cli(void);

void io_sti(void);

int io_in8(int port);

void io_out8(int port, int data);

void io_stihlt(void);

int io_load_eflags(void);

void io_store_eflags(int eflags); // 保存 eflags


/*graphic.c*/
void init_palette(void);

void set_palette(int start, int end, unsigned char *rgb);