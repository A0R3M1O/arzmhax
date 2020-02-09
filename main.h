#pragma once

#define HOOK_PROC "\x01\xB4\x01\xB4\x01\x48\x01\x90\x01\xBD\x00\xBF\x00\x00\x00\x00"

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

#include "util/util.h"

extern uintptr_t g_libGTASA;
extern uintptr_t g_libSAMP;

uint32_t GetTickCount();

typedef unsigned long DWORD;
typedef unsigned char BYTE;