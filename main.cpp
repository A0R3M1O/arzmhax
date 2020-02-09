#include <jni.h>
#include <android/log.h>
#include <ucontext.h>
#include <pthread.h>

#include "main.h"
#include "JniUtils.h"
#include "util/gtahook.h"
#include "util/samphook.h"

#include "sa.h"
#include "samp.h"
#include "settings.h"

uintptr_t g_libGTASA;
uintptr_t g_libSAMP;

CSettings *pSettings = nullptr;

void InstallGlobalPatches();

void *Init(void *p)
{
	while(*(uintptr_t *)(g_libGTASA + 0x00A987C8) != 7) usleep(500);

	// init settings
	pSettings = new CSettings();

	pthread_exit(0);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	JNIEnv* p_JNIEnv = nullptr;
	p_JNIEnv = getJniEnv(vm);

	if(!p_JNIEnv)
		return NULL;
	
	if(!Jni_Load(p_JNIEnv, "/data/data/com.rockstargames.gtasa/lib/libsamp_orig.so"))
		return NULL;

	g_libGTASA = FindLibrary("libGTASA.so");
	g_libSAMP = FindLibrary("libsamp_orig.so");

	srand(time(0));

	if(!g_libGTASA || !g_libSAMP) std::terminate();

	// hook system
	GTAHook_Init();
	SAMPHook_Init();

	// patches
	InstallGlobalPatches();

	// hooks
	InstallSAHooks();
	InstallSAMPHooks();

	// thread
	pthread_t thread;
	pthread_create(&thread, 0, Init, 0);

	return JNI_VERSION_1_6;
}

uint32_t GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (tv.tv_sec*1000+tv.tv_usec/1000);
}
