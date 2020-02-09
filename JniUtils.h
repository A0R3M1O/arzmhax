#pragma once

extern JNIEnv* getJniEnv(JavaVM *vm);
extern bool Jni_Load(JNIEnv* p, const char * libPath);