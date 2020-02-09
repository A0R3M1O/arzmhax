#include "../main.h"
#include <sys/mman.h>

uintptr_t samp_mmap_start    = 0;
uintptr_t samp_mmap_end      = 0;
uintptr_t samp_memlib_start  = 0;
uintptr_t samp_memlib_end    = 0;

void SAMPHook_UnFuck(uintptr_t ptr)
{
    mprotect((void*)(ptr & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void SAMPHook_NOP(uintptr_t addr, unsigned int count)
{
    SAMPHook_UnFuck(addr);

    for(uintptr_t ptr = addr; ptr != (addr+(count*2)); ptr += 2)
    {
        *(char*)ptr = 0x00;
        *(char*)(ptr+1) = 0x46;
    }

    cacheflush(addr, (uintptr_t)(addr + count*2), 0);
}

void SAMPHook_WriteMemory(uintptr_t dest, uintptr_t src, size_t size)
{
    SAMPHook_UnFuck(dest);
    memcpy((void*)dest, (void*)src, size);
    cacheflush(dest, dest+size, 0);
}

void SAMPHook_ReadMemory(uintptr_t dest, uintptr_t src, size_t size)
{
    SAMPHook_UnFuck(src);
    memcpy((void*)dest, (void*)src, size);
}

void SAMPHook_Init()
{
    samp_memlib_start = g_libSAMP + 0x03525C;
    samp_memlib_end = g_libSAMP + 0x400;

    samp_mmap_start = (uintptr_t)mmap(0, PAGE_SIZE, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    mprotect((void*)(samp_mmap_start & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_EXEC | PROT_WRITE);
    samp_mmap_end = (samp_mmap_start + PAGE_SIZE);
}

void SAMPHook_JMPCode(uintptr_t func, uintptr_t addr)
{
    uint32_t code = ((addr-func-4) >> 12) & 0x7FF | 0xF000 | ((((addr-func-4) >> 1) & 0x7FF | 0xB800) << 16);
    SAMPHook_WriteMemory(func, (uintptr_t)&code, 4);
}

void SAMPHook_WriteHookProc(uintptr_t addr, uintptr_t func)
{
    char code[16];
    memcpy(code, HOOK_PROC, 16);
    *(uint32_t*)&code[12] = (func | 1);
    SAMPHook_WriteMemory(addr, (uintptr_t)code, 16);
}

void SAMPHook_SetUpHook(uintptr_t addr, uintptr_t func, uintptr_t *orig)
{
    if(samp_memlib_end < (samp_memlib_start + 0x10) || samp_mmap_end < (samp_mmap_start + 0x20)) std::terminate();

    SAMPHook_ReadMemory(samp_mmap_start, addr, 4);
    SAMPHook_WriteHookProc(samp_mmap_start+4, addr+4);

    *orig = samp_mmap_start+1;
    samp_mmap_start += 32;

    SAMPHook_JMPCode(addr, samp_memlib_start);
    SAMPHook_WriteHookProc(samp_memlib_start, func);
    samp_memlib_start += 16;
}

void SAMPHook_InstallMethodHook(uintptr_t addr, uintptr_t func)
{
    SAMPHook_UnFuck(addr);
    *(uintptr_t*)addr = func;
}

void SAMPHook_CodeInject(uintptr_t addr, uintptr_t func, int reg)
{
    char injectCode[12];

    injectCode[0] = 0x01;
    injectCode[1] = 0xA0 + reg;
    injectCode[2] = (0x08 * reg) + reg;
    injectCode[3] = 0x68;
    injectCode[4] = 0x87 + (0x08 * reg);
    injectCode[5] = 0x46;
    injectCode[6] = injectCode[4];
    injectCode[7] = injectCode[5];
    
    *(uintptr_t*)&injectCode[8] = func;

    SAMPHook_WriteMemory(addr, (uintptr_t)injectCode, 12);
}