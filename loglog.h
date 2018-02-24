#include "common.h"
#include "hash.h"

#define LOGLOG_HEIGHT 64

class LogLog {
private:
    uint sketch[LOGLOG_HEIGHT];
    uint bucket_seed;
    uint hash_seed[LOGLOG_HEIGHT];
    uint dividend;
public:
    LogLog(uint dividend):dividend(dividend){
        memset(sketch, 0, sizeof(sketch));
        bucket_seed = rand()%LOGLOG_HEIGHT;
        for (int i = 0; i < LOGLOG_HEIGHT; ++i)
            hash_seed[i] = rand()%50;
    }
    void insert(uchar* str, uint len);
    double query(double adjust);
    void print();
};

void LogLog::insert(uchar* str, uint len) {
    uint index = BOB32(str, len, bucket_seed)%LOGLOG_HEIGHT;
    uint pos = GD_BOB128(str, len, hash_seed[index], dividend);
    sketch[index] = max(sketch[index], pos);
}

double LogLog::query(double adjust=0.39701) {
    double sum = 0;
    for(int i = 0; i < LOGLOG_HEIGHT; ++i) {
        sum += sketch[i];
        //sum += (dividend-1.0)*pow(dividend/(dividend-1.0), (double)pos)/adjust;
    }
    return adjust*LOGLOG_HEIGHT*(dividend-1.0)*pow(dividend/(dividend-1.0), sum/LOGLOG_HEIGHT);
}

void LogLog::print() {
    for(int i = 0; i < LOGLOG_HEIGHT; ++i) {
        printf("%u ", sketch[i]);
    }
    printf("\n");
}