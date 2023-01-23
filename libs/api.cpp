#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT extern "C" __attribute__((visibility("default"))) __attribute__((used))
#endif

#include <cstring>
#include <ctype.h>


EXPORT
double getAngleFR() {
    return 0.0;
}

EXPORT 
double getAngleFL() {
    return 1.0;
}

EXPORT
double getAngleRR() {
    return 2.0;
}

EXPORT
double getAngleRL() {
    return 3.0;
}


