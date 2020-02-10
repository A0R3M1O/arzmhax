#pragma once

#define HOOK_PROC "\x01\xB4\x01\xB4\x01\x48\x01\x90\x01\xBD\x00\xBF\x00\x00\x00\x00"

class ARMHook
{
public:
	ARMHook() {};
	~ARMHook() {};

	uintptr_t getLibraryAddress(const char* library);

	void sa_initializeTrampolines(uintptr_t start, uintptr_t end);
	void samp_initializeTrampolines(uintptr_t start, uintptr_t end);
	void unprotect(uintptr_t ptr);
	void makeNOP(uintptr_t addr, unsigned int count);
	void writeMemory(uintptr_t dest, uintptr_t src, size_t size);
	void readMemory(uintptr_t dest, uintptr_t src, size_t size);
	void JMPCode(uintptr_t func, uintptr_t addr);
	void WriteHookProc(uintptr_t addr, uintptr_t func);
	void installMethodHook(uintptr_t addr, uintptr_t func);
	void InjectCode(uintptr_t addr, uintptr_t func, int reg);
	void makeRET(uintptr_t addr);
	void installHook(uintptr_t addr, uintptr_t func, uintptr_t *orig, bool gta);
};