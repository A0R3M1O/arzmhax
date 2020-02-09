#pragma once

void SAMPHook_UnFuck(uintptr_t ptr);
void SAMPHook_NOP(uintptr_t addr, unsigned int count);
void SAMPHook_WriteMemory(uintptr_t dest, uintptr_t src, size_t size);
void SAMPHook_ReadMemory(uintptr_t dest, uintptr_t src, size_t size);
void SAMPHook_Init();
void SAMPHook_JMPCode(uintptr_t func, uintptr_t addr);
void SAMPHook_WriteHookProc(uintptr_t addr, uintptr_t func);
void SAMPHook_SetUpHook(uintptr_t addr, uintptr_t func, uintptr_t *orig);
void SAMPHook_InstallMethodHook(uintptr_t addr, uintptr_t func);
void SAMPHook_CodeInject(uintptr_t addr, uintptr_t func, int reg);