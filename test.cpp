#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"
#include "loglog.h"
#include "hyperloglog.h"

#define STR_LEN 128
#define STR_NUM 100000
#define REPEAT_TIME 1

uchar str[STR_LEN];
uint histogram[256];

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
    double fm_sum = 0;
    double loglog_sum = 0;
    double hyperloglog_sum = 0;
    for(int k = 0; k < REPEAT_TIME; ++k) {
      Record record;
      FM fm(2);
      LogLog loglog(2);
      HyperLogLog hyperloglog(2);
      for(int i = 0; i < STR_NUM; ++i) {
        //penntreebank_str(str, penntreebank);
        //trace_str(str, trace1);
        caida_str(str, caida0);
        record.insert(string((char*)str, (size_t)strlen((const char*)str)));
        fm.insert(str, strlen((const char*)str));
        loglog.insert(str, strlen((const char*)str));
        hyperloglog.insert(str, strlen((const char*)str));
      }
      loglog.print();
      hyperloglog.print();
      printf("%u %lf %lf %lf\n", record.query(), fm.query(1), loglog.query(1), hyperloglog.query(1));
      //printf("%lf\n", result[k]);
      fm_sum += fabs(fm.query(1)/record.query()-1);
      loglog_sum += fabs(loglog.query(1)/record.query()-1);
      hyperloglog_sum += fabs(hyperloglog.query(1)/record.query()-1);
    }
    printf("%lf %lf %lf\n", fm_sum/REPEAT_TIME, loglog_sum/REPEAT_TIME, hyperloglog_sum/REPEAT_TIME);
    fclose(penntreebank);
    return 0;
}