#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <jni.h>

#define RAKSAMP_CLIENT
#define NETCODE_CONNCOOKIELULZ 0x6969
#include "vendor/RakNet/SAMP/samp_netencr.h"
#include "vendor/RakNet/SAMP/SAMPRPC.h"

#include "util/armhook.h"

extern uintptr_t g_libGTASA;
extern uintptr_t g_libSAMP;

uint32_t GetTickCount();
void LOGI(const char *fmt, ...);

extern const char* g_pszStorage;

typedef unsigned long DWORD;
typedef unsigned char BYTE;