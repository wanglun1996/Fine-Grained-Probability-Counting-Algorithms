#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"

#define STR_LEN 128
#define STR_NUM 1000000
#define REPEAT_TIME 1

uchar str[STR_LEN];
uint histogram[256];
double result[REPEAT_TIME];

int main() {
    srand(time(0));
    // double sum = 0;
    // for(int k = 0; k < REPEAT_TIME; ++k) {
    //   Record record;
    //   FM fm(4);
    //   for(int i = 0; i < STR_NUM; ++i) {
    //     uint len = rand()%STR_LEN;
    //     random_str(str, len);
    //     record.insert(string((char*)str, (size_t)len));
    //     fm.insert(str, len);
    //   }
    //   printf("%u %lf\n", record.query(), fm.query(0.85));
    //   result[k] = fm.query(0.85)/record.query();
    //   //printf("%lf\n", result[k]);
    //   sum += result[k];
    // }
    // printf("%lf\n", sum/REPEAT_TIME);
    FILE* penntreebank = fopen("./dataset/ptb.train.txt", "r");
    FILE* trace1 = fopen("./dataset/traces/1", "r");
    FILE* trace2 = fopen("./dataset/traces/2", "r");
    FILE* caida0 = fopen("./dataset/CAIDA/0.dat", "r");
    double sum = 0;
    for(int k = 0; k < REPEAT_TIME; ++k) {
      Record record;
      FM fm(2);
      for(int i = 0; i < STR_NUM; ++i) {
        //penntreebank_str(str, penntreebank);
        //trace_str(str, trace1);
        caida_str(str, caida0);
        record.insert(string((char*)str, (size_t)strlen((const char*)str)));
        fm.insert(str, strlen((const char*)str));
      }
      //fm.print();
      printf("%u %lf\n", record.query(), fm.query(0.77351));
      result[k] = fm.query(0.77351)/record.query();
      //printf("%lf\n", result[k]);
      sum += fabs(result[k]-1);
    }
    printf("%lf\n", sum/REPEAT_TIME);
    fclose(penntreebank);
    return 0;
}