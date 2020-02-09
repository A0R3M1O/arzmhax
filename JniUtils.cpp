#include "main.h"

JNIEnv* getJniEnv(JavaVM *vm)
{
    JavaVMAttachArgs attachArgs;
    attachArgs.version = JNI_VERSION_1_6;
    attachArgs.name = "com.rockstargames.gtasa";
    attachArgs.group = NULL;
 
    JNIEnv* env = nullptr;

    if(vm->AttachCurrentThread(&env, &attachArgs) != JNI_OK)
    {
        env = nullptr;
    }
   
    return env;
}
 
bool Jni_Load(JNIEnv* p, const char * libPath)
{
    jclass sysClass = p->FindClass("java/lang/System");
 
    if(!sysClass)
    {
        return false;
    }
 
    jmethodID loadMethod = p->GetStaticMethodID(sysClass, "load", "(Ljava/lang/String;)V");
    jstring jStr = p->NewStringUTF(libPath);
    p->CallStaticByteMethod(sysClass, loadMethod, jStr);

    return true;
}