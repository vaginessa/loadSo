#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

typedef char* (*ZHUCE_FUNC)(char*);      //定义函数指针

extern "C"
JNIEXPORT jstring JNICALL
Java_com_reg_daliurenreg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    ZHUCE_FUNC zhuce_func = NULL;

    std::string hello = "Hello from C++";
    char* jiqima = "5607019B-14011";
    char* soPath = "/data/data/com.reg.daliurenreg/lib/libreg.so";
    void* handle = dlopen(soPath, 1);
    if(handle){
        *(void **) (&zhuce_func) = dlsym(handle, "getzhucema");
        if(zhuce_func ){
            char* str = (*zhuce_func)(jiqima);
            printf("so load successfully");
            char* result = (char*)malloc(12);
            for(int i=1; i<13; i++)
                result[i-1] = str[i];
            return env->NewStringUTF(result);
        }else{
            printf("error wihle calling JNI_OnLoad");
        }
    }else{
        printf("error while openning so");
    }

    return env->NewStringUTF(hello.c_str());
}
