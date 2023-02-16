#define MAX_SHEET  256
#define true 1
#define false 0
#define ADDRESS_BOOTINFO 0X00000ff0

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

/*destble.c*/
#define ADR_IDT            0x0026f800
#define LIMIT_IDT        0x000007ff
#define ADR_GDT            0x00270000
#define LIMIT_GDT        0x0000ffff
#define ADR_BOTPAK        0x00280000
#define LIMIT_BOTPAK    0x0007ffff
#define AR_DATA32_RW    0x4092
#define AR_CODE32_ER    0x409a
#define AR_TSS32        0x0089
#define AR_INTGATE32    0x008e

/*keyboard.c*/
#define PORT_KEYSTA                0x0064
#define KEYSTA_SEND_NOTREADY    0x02
#define KEYCMD_WRITE_MODE        0x60
#define KBC_MODE                0x47
#define PORT_KEYDAT        0x0060
#define PORT_KEYCMD        0x0064

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

struct SEGMENT_DESCRIPTOR {
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
};

struct GATE_DESCRIPTOR {
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
};


struct FIFO32 {
    unsigned int *buf;
    int p, q, size, free, flags;
};

struct MOUSE_DEC {
    unsigned char buf[3], phase;
    int x, y, btn;
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

void load_gdtr(int limit, int address);

void load_idtr(int limit, int address);

int load_cr0(void);

void store_cr0(int cr0);


/*graphic.c*/
void init_palette(void);

void set_palette(int start, int end, unsigned char *rgb);

void init_screen(unsigned char *vram, int x, int y);

void boxfill(unsigned char *vram, int xSize, unsigned char c, int x0, int y0, int x1, int y1);

void putStr(unsigned char *vram, int xSize, int x, int y, char c, unsigned char *s);

void putFont(char *vram, int xSize, int x, int y, char c, char *font);

/*int.c*/
void init_pic(void);

void inthandler27(int *esp);

/*destble.c*/
void init_gdtidt(void);

void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);

/*int.c*/
void asm_inthandler21(void);

void asm_inthandler27(void);

void asm_inthandler2c(void);

void asm_inthandler20(void);

void inthandler21(int *esp);

void inthandler27(int *esp);

void inthandler2c(int *esp);

void inthandler20(int *esp);


/*keyboard.c*/
void wait_KBC_sendready(void);

void init_keyboard(struct FIFO32 *kq, int offset);

/*mouse.c*/


void enable_mouse(struct FIFO32 *mf, int data);

/*fifo.c*/
void fifo32_init(struct FIFO32 *fifo, int size, int *buf);

int fifo32_put(struct FIFO32 *fifo, int data);

int fifo32_get(struct FIFO32 *fifo);

int fifo32_status(struct FIFO32 *fifo);

/*memory.c*/
#define MEM_FREES 4090
#define MEM_MANAGER_ADDRESS 0x003C0000 // 内存管理人员所在的内存地址

struct FREEINFO {
    unsigned int address, size;
};

struct MEMMANAGER {
    int frees, maxFrees, lostSize, losts;
    struct FREEINFO freeInfo[MEM_FREES];
};


void memmanager_init(struct MEMMANAGER *manager);

unsigned int memory_total(struct MEMMANAGER *man);

unsigned int memory_alloc(struct MEMMANAGER *man, unsigned int size);

int memory_free(struct MEMMANAGER *man, unsigned int address, unsigned int size);

unsigned int alloc4k(struct MEMMANAGER *man, unsigned int size);

int free4k(struct MEMMANAGER *man, unsigned int address, unsigned int size);

unsigned int memtest_sub(unsigned int start, unsigned int end);

unsigned int memtest(unsigned int start, unsigned int end);

void init_mem();


/*Timer.c*/

#define MAX_TIMER        500
struct TIMER {
    struct TIMER *next;
    unsigned int timeout, flags;
    struct FIFO32 *fifo;
    int data;
};
struct TIMERCTL {
    unsigned int count, next;
    struct TIMER *t0;
    struct TIMER timers0[MAX_TIMER];
};
extern struct TIMERCTL timerctl;

void init_pit(void);

struct TIMER *timer_alloc(void);

void timer_free(struct TIMER *timer);

void timer_init(struct TIMER *timer, struct FIFO32 *fifo, int data);

void timer_settime(struct TIMER *timer, unsigned int timeout);

