#include <jni.h>
#include <android/log.h>
#include <ucontext.h>
#include <pthread.h>

#include "main.h"
#include "JniUtils.h"

#include "sa.h"
#include "samp.h"
#include "settings.h"

uintptr_t g_libGTASA = 0;
uintptr_t g_libSAMP = 0;

CSettings *pSettings = nullptr;
ARMHook *pARMHook = nullptr;

void InstallGlobalPatches();

const char* g_pszStorage = nullptr;

void *Init(void *p)
{
	if(!g_pszStorage)
	{
		g_pszStorage = (const char*)(g_libGTASA + 0x006D687C);

		if(!g_pszStorage) std::terminate();
	}

	while(*(uintptr_t *)(g_libGTASA + 0x00A987C8) != 7) usleep(500);

	// init settings
	pSettings = new CSettings();

	// patches
	InstallGlobalPatches();

	// hooks
	InstallSAHooks();
	InstallSAMPHooks();

	pthread_exit(0);
}

void handler(int signum, siginfo_t *info, void* contextPtr)
{
	ucontext* context = (ucontext_t*)contextPtr;

	if(!pARMHook) return;
	uintptr_t libPtr = pARMHook->getLibraryAddress("libsamp.so");

	if(info->si_signo == SIGSEGV)
	{
		LOGI(">>> crash occurred! >>>");
		LOGI("1: libsamp.so + 0x%X", context->uc_mcontext.arm_pc - libPtr);
		LOGI("2: libsamp.so + 0x%X", context->uc_mcontext.arm_lr - libPtr);

		std::terminate();
	}

	return;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	LOGI("arzmhax library loaded! Build time: " __DATE__ " " __TIME__);

	// JNIEnv
	JNIEnv* m_pJniEnv = getJniEnv(vm);
	if(!m_pJniEnv) return NULL;

	// arm funcs
	pARMHook = new ARMHook();
	srand(time(0));

	// sa
	g_libGTASA = pARMHook->getLibraryAddress("libGTASA.so");
	if(g_libGTASA == 0) std::terminate();

	// sa hook system
	pARMHook->sa_initializeTrampolines(0x1A9E0C, 0x400);

	// sa-mp
	if(!Jni_Load(m_pJniEnv, "/data/data/com.rockstargames.gtasa/lib/libsamp_orig.so")) return NULL;
	g_libSAMP = pARMHook->getLibraryAddress("libsamp_orig.so");
	if(g_libSAMP == 0) std::terminate();

	// sa-mp hook system
	pARMHook->samp_initializeTrampolines(0x03525C, 0x400);

	// thread
	pthread_t thread;
	pthread_create(&thread, 0, Init, 0);

	struct sigaction act;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &act, 0);

	return JNI_VERSION_1_6;
}

uint32_t GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (tv.tv_sec*1000+tv.tv_usec/1000);
}

void LOGI(const char *fmt, ...)
{	
	char buffer[0xFF];
	static FILE* flLog = nullptr;

	if(flLog == nullptr && g_pszStorage != nullptr)
	{
		sprintf(buffer, "%sSAMP/plugin_log.txt", g_pszStorage);
		flLog = fopen(buffer, "a");
	}

	memset(buffer, 0, sizeof(buffer));

	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, arg);
	va_end(arg);

	__android_log_write(ANDROID_LOG_INFO, "AXL", buffer);

	if(flLog == nullptr) return;
	fprintf(flLog, "%s\n", buffer);
	fflush(flLog);

	return;
}