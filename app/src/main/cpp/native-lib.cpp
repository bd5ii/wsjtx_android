#include <jni.h>
#include <string>

void fast_decode_(short id2[], int narg[], int* ntrperiod,
                  char msg[], char mycall[], char hiscall[],
                  int len1, int len2, int len3);

extern "C"
JNIEXPORT jstring JNICALL
Java_vvanders_com_wsjt_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
