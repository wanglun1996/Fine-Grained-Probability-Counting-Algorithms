#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"

uchar str[1024];

void random_str(uchar* str, uint len) {
    for(int i = 0; i < len; ++i) {
        str[i] = rand()%256;
    }
}

int main() {
    srand(time(0));
    Record record;
    FM fm(4);
    for(int i = 0; i < 10000; ++i) {
      uint len = rand()%1024;
      random_str(str, len);
      record.insert(string((char*)str, (size_t)len));
      fm.insert(str, len);
    }
    printf("%u %lf\n", record.query(), fm.query());
    return 0;
}