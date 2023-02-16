/*内存管理文件*/


#include "../main.h"

extern struct MEMMANAGER *memmanager;

void init_mem() {
    unsigned int memTotal = memtest(0x00400000, 0xbfffffff);
    memmanager_init(memmanager);

    memory_free(memmanager, 0x00001000, 0x0009e000);
    memory_free(memmanager, 0x00400000, memTotal - 0x00400000);
}


// 内存管理者初始化
void memmanager_init(struct MEMMANAGER *manager) {
    manager->frees = 0;  // 可用信息数目
    manager->maxFrees = 0; // 用于观察可用状况，frees的最大值
    manager->lostSize = 0; // 释放失败的内存大小总和
    manager->losts = 0; // 释放失败次数
}


// 统计内存容量
unsigned int memory_total(struct MEMMANAGER *man) {
    unsigned int t = 0;
    for (int i = 0; i < man->frees; i++) {
        t += man->freeInfo[i].size;
    }
    return t;
}

// 内存分配
unsigned int memory_alloc(struct MEMMANAGER *man, unsigned int size) {
    unsigned a;
    for (int i = 0; i < man->frees; i++) {
        if (man->freeInfo[i].size >= size) {
            a = man->freeInfo[i].address;
            man->freeInfo[i].address += size;
            man->freeInfo[i].size -= size;

            if (man->freeInfo[i].size == 0) {
                man->frees--;
                // 合并可用信息
                for (; i < man->maxFrees; i++) {
                    man->freeInfo[i] = man->freeInfo[i + 1];
                }
            }
            return a; // 返回分配地址
        }
    }
    return 0; // 没有可用空间
}


int memory_free(struct MEMMANAGER *man, unsigned int address, unsigned int size) {
    int i = 0;
    for (i = 0; i < man->frees; i++) {
        if (man->freeInfo[i].address > address) {
            break;
        }
    }
    if (i > 0) {
        if (man->freeInfo[i - 1].address + man->freeInfo[i - 1].size == address) {
            // 可以和前面的进行合并
            man->freeInfo[i - 1].size += size;
            if (i < man->frees) {
                if (address + size == man->freeInfo[i].address) {
                    man->freeInfo[i - 1].size += man->freeInfo[i].size;
                    man->frees--;
                    for (; i < man->frees; i++) {
                        man->freeInfo[i] = man->freeInfo[i + 1];
                    }
                }
            }
            return;
        }
    }

    if (i < man->frees) {
        // 如果可以和后面的内存进行合并
        if (address + size == man->freeInfo[i].address) {
            man->freeInfo[i].address = address;
            man->freeInfo[i].size += size;
            return 0;
        }
    }

    // 不能向前进行合并，也不能向后进行合并
    if (man->frees < MEM_FREES) {
        for (int j = man->frees; j > i; j--) {
            man->freeInfo[j] = man->freeInfo[j - 1]; // 向后移动
        }

        man->frees++;
        if (man->maxFrees < man->frees) {
            man->maxFrees = man->frees;
        }
        man->freeInfo[i].address = address;
        man->freeInfo[i].size = size;
        return 0;
    }

    man->lostSize += size;
    man->losts++;

    return -1;
}


// 分配4k的内存大小
unsigned int alloc4k(struct MEMMANAGER *man, unsigned int size) {
    unsigned int a;
    size = (size + 0xfff) & 0xfffff000;
    a = memory_alloc(man, size);
    return a;
}


// 释放4k的内存
int free4k(struct MEMMANAGER *man, unsigned int address, unsigned int size) {
    int i;
    size = (size + 0xfff) & 0xfffff000;
    i = memory_free(man, address, size);
    return i;
}

#define EFLAGS_AC_BIT        0x00040000
#define CR0_CACHE_DISABLE    0x60000000

unsigned int memtest(unsigned int start, unsigned int end) {
    char flg486 = 0;
    unsigned int eflg, cr0, i;

    /* 386偐丄486埲崀側偺偐偺妋擣 */
    eflg = io_load_eflags();
    eflg |= EFLAGS_AC_BIT; /* AC-bit = 1 */
    io_store_eflags(eflg);
    eflg = io_load_eflags();
    if ((eflg & EFLAGS_AC_BIT) != 0) { /* 386偱偼AC=1偵偟偰傕帺摦偱0偵栠偭偰偟傑偆 */
        flg486 = 1;
    }
    eflg &= ~EFLAGS_AC_BIT; /* AC-bit = 0 */
    io_store_eflags(eflg);

    if (flg486 != 0) {
        cr0 = load_cr0();
        cr0 |= CR0_CACHE_DISABLE; /* 僉儍僢僔儏嬛巭 */
        store_cr0(cr0);
    }

    i = memtest_sub(start, end);

    if (flg486 != 0) {
        cr0 = load_cr0();
        cr0 &= ~CR0_CACHE_DISABLE; /* 僉儍僢僔儏嫋壜 */
        store_cr0(cr0);
    }

    return i;
}
