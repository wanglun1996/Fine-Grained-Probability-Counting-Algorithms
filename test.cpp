#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"
#include "loglog.h"
#include "hyperloglog.h"

#define STR_LEN 128
#define STR_NUM 1000
#define REPEAT_TIME 16

uchar str[STR_LEN];
uint histogram[256];

double learn_random() {
    double sum[3];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        FM fm(4);
        LogLog loglog(4);
        HyperLogLog hyperloglog(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            fm.insert(str, len);
            loglog.insert(str, len);
            hyperloglog.insert(str, len);
        }
        sum[0] += fm.query(1)/record.query();
        sum[1] += loglog.query(1)/record.query();
        sum[2] += hyperloglog.query(1)/record.query();
    }
    printf("FM amendment coefficient: %lf\n", sum[0]/REPEAT_TIME);
    printf("LogLog amendment coefficient: %lf\n", sum[1]/REPEAT_TIME);
    printf("HyperLogLog amendment coefficient: %lf\n", sum[2]/REPEAT_TIME);
}

double learn_trace() {
    FILE* trace = fopen("./dataset/trace", "r");
    double sum[3];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        FM fm(4);
        LogLog loglog(4);
        HyperLogLog hyperloglog(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm.insert(str, len);
            loglog.insert(str, len);
            hyperloglog.insert(str, len);
        }
        sum[0] += fm.query(1)/record.query();
        sum[1] += loglog.query(1)/record.query();
        sum[2] += hyperloglog.query(1)/record.query();
    }
    printf("FM amendment coefficient: %lf\n", sum[0]/REPEAT_TIME);
    printf("LogLog amendment coefficient: %lf\n", sum[1]/REPEAT_TIME);
    printf("HyperLogLog amendment coefficient: %lf\n", sum[2]/REPEAT_TIME);
    fclose(trace);

}

double learn_caida() {
    FILE* caida = fopen("./dataset/caida", "r");
    double sum[3];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        FM fm(4);
        LogLog loglog(4);
        HyperLogLog hyperloglog(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm.insert(str, len);
            loglog.insert(str, len);
            hyperloglog.insert(str, len);
        }
        sum[0] += fm.query(1)/record.query();
        sum[1] += loglog.query(1)/record.query();
        sum[2] += hyperloglog.query(1)/record.query();
    }
    printf("FM amendment coefficient: %lf\n", sum[0]/REPEAT_TIME);
    printf("LogLog amendment coefficient: %lf\n", sum[1]/REPEAT_TIME);
    printf("HyperLogLog amendment coefficient: %lf\n", sum[2]/REPEAT_TIME);
    fclose(caida);
}

double learn_penntreebank() {
    FILE* ptb = fopen("./dataset/ptb", "r");
    double sum[3];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        FM fm(4);
        LogLog loglog(4);
        HyperLogLog hyperloglog(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, ptb);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm.insert(str, len);
            loglog.insert(str, len);
            hyperloglog.insert(str, len);
        }
        sum[0] += fm.query(1)/record.query();
        sum[1] += loglog.query(1)/record.query();
        sum[2] += hyperloglog.query(1)/record.query();
    }
    printf("FM amendment coefficient: %lf\n", sum[0]/REPEAT_TIME);
    printf("LogLog amendment coefficient: %lf\n", sum[1]/REPEAT_TIME);
    printf("HyperLogLog amendment coefficient: %lf\n", sum[2]/REPEAT_TIME);
    fclose(ptb);
}

void test_loglog() {
    FILE* trace = fopen("./dataset/trace", "r");
    FILE* caida = fopen("./dataset/caida", "r");
    FILE* penntreebank = fopen("./dataset/ptb", "r");
    // random_str
    double sum[2];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        LogLog loglog_2(2);
        LogLog loglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            loglog_2.insert(str, len);
            loglog_4.insert(str, len);
        }
        sum[0] += loglog_2.query(1)/record.query();
        sum[1] += loglog_4.query(1)/record.query();
    }
    //trace
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        LogLog loglog_2(2);
        LogLog loglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            loglog_2.insert(str, len);
            loglog_4.insert(str, len);
        }
        sum[0] += loglog_2.query(1)/record.query();
        sum[1] += loglog_4.query(1)/record.query();
    }
    //caida
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        LogLog loglog_2(2);
        LogLog loglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            loglog_2.insert(str, len);
            loglog_4.insert(str, len);
        }
        sum[0] += loglog_2.query(1)/record.query();
        sum[1] += loglog_4.query(1)/record.query();
    }
    //penn tree bank
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        LogLog loglog_2(2);
        LogLog loglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, penntreebank);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            loglog_2.insert(str, len);
            loglog_4.insert(str, len);
        }
        sum[0] += loglog_2.query(1)/record.query();
        sum[1] += loglog_4.query(1)/record.query();
    }
}

void test_hyper() {
    FILE* trace = fopen("./dataset/trace", "r");
    FILE* caida = fopen("./dataset/caida", "r");
    FILE* penntreebank = fopen("./dataset/ptb", "r");
    // random_str
    double sum[2];
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        HyperLogLog hyperloglog_2(2);
        HyperLogLog hyperloglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            hyperloglog_2.insert(str, len);
            hyperloglog_4.insert(str, len);
        }
        sum[0] += hyperloglog_2.query(1)/record.query();
        sum[1] += hyperloglog_4.query(1)/record.query();
    }
    //trace
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        HyperLogLog hyperloglog_2(2);
        HyperLogLog hyperloglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hyperloglog_2.insert(str, len);
            hyperloglog_4.insert(str, len);
        }
        sum[0] += hyperloglog_2.query(1)/record.query();
        sum[1] += hyperloglog_4.query(1)/record.query();
    }
    //caida
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        HyperLogLog hyperloglog_2(2);
        HyperLogLog hyperloglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hyperloglog_2.insert(str, len);
            hyperloglog_4.insert(str, len);
        }
        sum[0] += hyperloglog_2.query(1)/record.query();
        sum[1] += hyperloglog_4.query(1)/record.query();
    }
    //penn tree bank
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        HyperLogLog hyperloglog_2(2);
        HyperLogLog hyperloglog_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, penntreebank);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hyperloglog_2.insert(str, len);
            hyperloglog_4.insert(str, len);
        }
        sum[0] += hyperloglog_2.query(1)/record.query();
        sum[1] += hyperloglog_4.query(1)/record.query();
    }
}
int main() {
    srand(time(0));

    learn_random();
    // FILE* trace = fopen("./dataset/trace", "r");
    // FILE* caida = fopen("./dataset/caida", "r");
    // FILE* penntreebank = fopen("./dataset/ptb", "r");
    // double sum = 0;
    // for(int k = 0; k < REPEAT_TIME; ++k) {
    //   Record record;
    //   FM fm(2);
    //   for(int i = 0; i < STR_NUM; ++i) {
    //     //uint len = rand()%STR_LEN;
    //     //random_str(str, len);
    //     //penntreebank_str(str, penntreebank);
    //     trace_str(str, trace1);
    //     //record.insert(string((char*)str, (size_t)len));
    //     //fm.insert(str, len);
    //     record.insert(string((char*)str, (size_t)strlen((const char*)str)));
    //     fm.insert(str, strlen((const char*)str));
    //   }
    //   printf("%u %lf\n", record.query(), fm.query(1));
    //   sum += fm.query(1)/record.query();
    // }
    // printf("%lf\n", sum/REPEAT_TIME);


    // double fm_sum = 0;
    // double loglog_sum = 0;
    // double hyperloglog_sum = 0;
    // for(int k = 0; k < REPEAT_TIME; ++k) {
    //   Record record;
    //   FM fm(2);
    //   LogLog loglog(2);
    //   HyperLogLog hyperloglog(2);
    //   for(int i = 0; i < STR_NUM; ++i) {
    //     //penntreebank_str(str, penntreebank);
    //     //trace_str(str, trace1);
    //     caida_str(str, caida0);
    //     record.insert(string((char*)str, (size_t)strlen((const char*)str)));
    //     fm.insert(str, strlen((const char*)str));
    //     loglog.insert(str, strlen((const char*)str));
    //     hyperloglog.insert(str, strlen((const char*)str));
    //   }
    //   fm.print();
    //   //hyperloglog.print();
    //   printf("%u %lf %lf %lf\n", record.query(), fm.query(), loglog.query(1), hyperloglog.query(1));
    //   //printf("%lf\n", result[k]);
    //   fm_sum += fabs(fm.query()/record.query()-1);
    //   loglog_sum += fabs(loglog.query(1)/record.query()-1);
    //   hyperloglog_sum += fabs(hyperloglog.query(1)/record.query()-1);
    // }
    // printf("%lf %lf %lf\n", fm_sum/REPEAT_TIME, loglog_sum/REPEAT_TIME, hyperloglog_sum/REPEAT_TIME);
    // fclose(penntreebank);
    // fclose(trace1);
    // fclose(trace2);
    // fclose(caida0);
    return 0;
}