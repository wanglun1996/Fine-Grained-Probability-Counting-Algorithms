#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"

#define STR_LEN 16
#define STR_NUM 10000
#define REPEAT_TIME 100

uchar str[STR_LEN];
uint histogram[256];
double result[REPEAT_TIME];

void random_str(uchar* str, uint len) {
    for(int i = 0; i < len; ++i) {
        str[i] = rand()%256;
    }
}

int main() {
    srand(time(0));
    double sum = 0;
    for(int k = 0; k < REPEAT_TIME; ++k) {
      Record record;
      FM fm(4);
      for(int i = 0; i < STR_NUM; ++i) {
        uint len = rand()%STR_LEN;
        random_str(str, len);
        record.insert(string((char*)str, (size_t)len));
        fm.insert(str, len);
      }
      printf("%u %lf\n", record.query(), fm.query(0.85));
      result[k] = fm.query(0.85)/record.query();
      //printf("%lf\n", result[k]);
      sum += result[k];
    }
    printf("%lf\n", sum/REPEAT_TIME);
    return 0;
}