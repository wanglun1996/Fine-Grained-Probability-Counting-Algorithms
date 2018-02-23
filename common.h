#ifndef COMMON_H
#define COMMON_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "string"
#include "map"
#include "set"
using namespace std;

#define min(x, y) (x<y?x:y)
#define max(x, y) (x>y?x:y)

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ull;

void random_str(uchar* str, uint len) {
    for(int i = 0; i < len; ++i) {
        str[i] = rand()%256;
    }
}

void penntreebank_str(uchar* str, FILE* stream) {
    fscanf(stream, "%s", str);
}

void trace_str(uchar* str, FILE* stream) {
    char tmp[128];
    fscanf(stream, "%s", str);
    for(int i = 0; i < 4; ++i) {
        fscanf(stream, "%s", tmp);
        strcat((char*)str, tmp);
    }
}

void caida_str(uchar* str, FILE* stream) {
    for(int i = 0; i < 13; ++i)
        str[i] = fgetc(stream); 
    str[13] = 0;
}

#endif