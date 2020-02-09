#pragma once

void GTAHook_UnFuck(uintptr_t ptr);
void GTAHook_NOP(uintptr_t addr, unsigned int count);
void GTAHook_WriteMemory(uintptr_t dest, uintptr_t src, size_t size);
void GTAHook_ReadMemory(uintptr_t dest, uintptr_t src, size_t size);
void GTAHook_Init();
void GTAHook_JMPCode(uintptr_t func, uintptr_t addr);
void GTAHook_WriteHookProc(uintptr_t addr, uintptr_t func);
void GTAHook_SetUpHook(uintptr_t addr, uintptr_t func, uintptr_t *orig);
void GTAHook_InstallMethodHook(uintptr_t addr, uintptr_t func);
void GTAHook_CodeInject(uintptr_t addr, uintptr_t func, int reg);