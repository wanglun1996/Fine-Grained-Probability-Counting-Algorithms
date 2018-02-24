#include "common.h"
#include "hash.h"
#include "record.h"
#include "fm.h"
#include "loglog.h"
#include "hyperloglog.h"

#define STR_LEN 128
#define STR_NUM 100000
#define REPEAT_TIME 16

uchar str[STR_LEN];
double result[REPEAT_TIME][2];

char name[STR_LEN];
char name_posix[STR_LEN];

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

void test_random_fm() {
    double sum[4];
    //random_str
    sprintf(name, "%s", "./result/detail/randomfmaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/randomfmare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        FM fm_2(2);
        FM fm_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            fm_2.insert(str, len);
            fm_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(fm_2.query()-record.query()), fabs(fm_4.query(0.829)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(fm_2.query()/record.query()-1), fabs(fm_4.query(0.829)/record.query()-1));
        sum[0] += fm_2.query()-record.query();
        sum[1] += fm_4.query(0.829)-record.query();
        sum[2] += fm_2.query()/record.query();
        sum[3] += fm_4.query(0.829)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);     
}

void test_random_loglog() {
    double sum[4];
    //random_str
    sprintf(name, "%s", "./result/detail/randomllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/randomllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        LogLog ll_2(2);
        LogLog ll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            ll_2.insert(str, len);
            ll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(ll_2.query()-record.query()), fabs(ll_4.query(0.21)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(ll_2.query()/record.query()-1), fabs(ll_4.query(0.21)/record.query()-1));
        sum[0] += ll_2.query()-record.query();
        sum[1] += ll_4.query(0.21)-record.query();
        sum[2] += ll_2.query()/record.query();
        sum[3] += ll_4.query(0.21)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);     
}

void test_random_hyperloglog() {
    double sum[4];
    //random_str
    sprintf(name, "%s", "./result/detail/randomhllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/randomhllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        HyperLogLog hll_2(2);
        HyperLogLog hll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            uint len = rand()%STR_LEN;
            random_str(str, len);
            record.insert(string((char*)str, len));
            hll_2.insert(str, len);
            hll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(hll_2.query()-record.query()), fabs(hll_4.query(0.378)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(hll_2.query()/record.query()-1), fabs(hll_4.query(0.378)/record.query()-1));
        sum[0] += hll_2.query()-record.query();
        sum[1] += hll_4.query(0.378)-record.query();
        sum[2] += hll_2.query()/record.query();
        sum[3] += hll_4.query(0.378)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);     
}

void test_trace_fm() {
    double sum[4];
    FILE* trace = fopen("./dataset/trace", "r");
    // trace
    sprintf(name, "%s", "./result/detail/tracefmaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/tracefmare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        FM fm_2(2);
        FM fm_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm_2.insert(str, len);
            fm_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(fm_2.query()-record.query()), fabs(fm_4.query(0.45)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(fm_2.query()/record.query()-1), fabs(fm_4.query(0.45)/record.query()-1));
        sum[0] += fm_2.query()-record.query();
        sum[1] += fm_4.query(0.45)-record.query();
        sum[2] += fm_2.query()/record.query();
        sum[3] += fm_4.query(0.45)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(trace);
}

void test_trace_loglog() {
    double sum[4];
    FILE* trace = fopen("./dataset/trace", "r");
    // trace
    sprintf(name, "%s", "./result/detail/tracellaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/tracellare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        LogLog ll_2(2);
        LogLog ll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            ll_2.insert(str, len);
            ll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(ll_2.query()-record.query()), fabs(ll_4.query(0.250)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(ll_2.query()/record.query()-1), fabs(ll_4.query(0.250)/record.query()-1));
        sum[0] += ll_2.query()-record.query();
        sum[1] += ll_4.query(0.250)-record.query();
        sum[2] += ll_2.query()/record.query();
        sum[3] += ll_4.query(0.250)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(trace);
}

void test_trace_hyperloglog() {
    double sum[4];
    FILE* trace = fopen("./dataset/trace", "r");
    // trace
    sprintf(name, "%s", "./result/detail/tracehllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/tracehllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        HyperLogLog hll_2(2);
        HyperLogLog hll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            trace_str(str, trace);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hll_2.insert(str, len);
            hll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(hll_2.query()-record.query()), fabs(hll_4.query(0.95)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(hll_2.query()/record.query()-1), fabs(hll_4.query(0.95)/record.query()-1));
        sum[0] += hll_2.query()-record.query();
        sum[1] += hll_4.query(0.95)-record.query();
        sum[2] += hll_2.query()/record.query();
        sum[3] += hll_4.query(0.95)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(trace);
}

void test_caida_fm() {
    double sum[4];
    FILE* caida = fopen("./dataset/caida", "r");
    //caida
    sprintf(name, "%s", "./result/detail/caidafmaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/caidafmare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        FM fm_2(2);
        FM fm_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm_2.insert(str, len);
            fm_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(fm_2.query()-record.query()), fabs(fm_4.query(0.808)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(fm_2.query()/record.query()-1), fabs(fm_4.query(0.808)/record.query()-1));
        sum[0] += fm_2.query()-record.query();
        sum[1] += fm_4.query(0.808)-record.query();
        sum[2] += fm_2.query()/record.query();
        sum[3] += fm_4.query(0.808)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(caida);
}

void test_caida_loglog() {
    double sum[4];
    FILE* caida = fopen("./dataset/caida", "r");
    //caida
    sprintf(name, "%s", "./result/detail/caidallaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/caidallare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        LogLog ll_2(2);
        LogLog ll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            ll_2.insert(str, len);
            ll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(ll_2.query()-record.query()), fabs(ll_4.query(0.220)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(ll_2.query()/record.query()-1), fabs(ll_4.query(0.220)/record.query()-1));
        sum[0] += ll_2.query()-record.query();
        sum[1] += ll_4.query(0.220)-record.query();
        sum[2] += ll_2.query()/record.query();
        sum[3] += ll_4.query(0.220)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(caida);
}

void test_caida_hyperloglog() {
    double sum[4];
    FILE* caida = fopen("./dataset/caida", "r");
    //caida
    sprintf(name, "%s", "./result/detail/caidahllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/caidahllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        printf("%d\n", k);
        Record record;
        HyperLogLog hll_2(2);
        HyperLogLog hll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            caida_str(str, caida);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hll_2.insert(str, len);
            hll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(hll_2.query()-record.query()), fabs(hll_4.query(0.5)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(hll_2.query()/record.query()-1), fabs(hll_4.query(0.5)/record.query()-1));
        sum[0] += hll_2.query()-record.query();
        sum[1] += hll_4.query(0.782)-record.query();
        sum[2] += hll_2.query()/record.query();
        sum[3] += hll_4.query(0.782)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(caida);
}

void test_penn_fm() {
    double sum[4];
    FILE* penntreebank = fopen("./dataset/ptb", "r");
    //penn treebank
    sprintf(name, "%s", "./result/detail/pennfmaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/pennfmare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        FM fm_2(2);
        FM fm_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, penntreebank);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            fm_2.insert(str, len);
            fm_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(fm_2.query()-record.query()), fabs(fm_4.query(0.794)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(fm_2.query()/record.query()-1), fabs(fm_4.query(0.794)/record.query()-1));
        sum[0] += fm_2.query()-record.query();
        sum[1] += fm_4.query(0.794)-record.query();
        sum[2] += fm_2.query()/record.query();
        sum[3] += fm_4.query(0.794)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(penntreebank);
}

void test_penn_loglog() {
    double sum[4];
    FILE* penntreebank = fopen("./dataset/ptb", "r");
    //penn treebank
    sprintf(name, "%s", "./result/detail/pennllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/pennllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        LogLog ll_2(2);
        LogLog ll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, penntreebank);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            ll_2.insert(str, len);
            ll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(ll_2.query()-record.query()), fabs(ll_4.query(0.09)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(ll_2.query()/record.query()-1), fabs(ll_4.query(0.09)/record.query()-1));
        sum[0] += ll_2.query()-record.query();
        sum[1] += ll_4.query(0.09)-record.query();
        sum[2] += ll_2.query()/record.query();
        sum[3] += ll_4.query(0.09)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(penntreebank);
}

void test_penn_hyperloglog() {
    double sum[4];
    FILE* penntreebank = fopen("./dataset/ptb", "r");
    //penn treebank
    sprintf(name, "%s", "./result/detail/pennhllaae");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_aae = fopen(name, "w");
    sprintf(name, "%s", "./result/detail/pennhllare");
    sprintf(name_posix, "%d", STR_NUM);
    strcat(name, name_posix);
    strcat(name, ".csv");
    FILE* detail_are = fopen(name, "w");
    memset(sum, 0, sizeof(sum));
    for(int k = 0; k < REPEAT_TIME; ++k) {
        Record record;
        HyperLogLog hll_2(2);
        HyperLogLog hll_4(4);
        for(int i = 0; i < STR_NUM; ++i) {
            penntreebank_str(str, penntreebank);
            uint len = strlen((const char*)str);
            record.insert(string((char*)str, len));
            hll_2.insert(str, len);
            hll_4.insert(str, len);
        }
        fprintf(detail_aae, "%lf,%lf\n", fabs(hll_2.query()-record.query()), fabs(hll_4.query(0.2)-record.query()));
        fprintf(detail_are, "%lf,%lf\n", fabs(hll_2.query()/record.query()-1), fabs(hll_4.query(0.2)/record.query()-1));
        sum[0] += hll_2.query()-record.query();
        sum[1] += hll_4.query(0.2)-record.query();
        sum[2] += hll_2.query()/record.query();
        sum[3] += hll_4.query(0.2)/record.query();
    }
    printf("%lf,%lf\n", fabs(sum[0]/REPEAT_TIME), fabs(sum[1]/REPEAT_TIME));
    printf("%lf,%lf\n", fabs(1-sum[2]/REPEAT_TIME), fabs(1-sum[3]/REPEAT_TIME));
    fclose(detail_aae);
    fclose(detail_are);
    fclose(penntreebank);
}

int main() {
    srand(time(0));
    //learn_penntreebank();
    test_penn_loglog();
    test_penn_hyperloglog();
    return 0;
}