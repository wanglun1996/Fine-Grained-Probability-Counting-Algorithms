#include "common.h"
#include "hash.h"

#define HYPERLOGLOG_HEIGHT 64

class HyperLogLog {
private:
    uint sketch[HYPERLOGLOG_HEIGHT];
    uint bucket_seed;
    uint hash_seed[HYPERLOGLOG_HEIGHT];
    uint dividend;
public:
    HyperLogLog(uint dividend):dividend(dividend){
        memset(sketch, 0, sizeof(sketch));
        bucket_seed = rand()%HYPERLOGLOG_HEIGHT;
        for (int i = 0; i < HYPERLOGLOG_HEIGHT; ++i)
            hash_seed[i] = rand()%50;
    }
    void insert(uchar* str, uint len);
    double query(double adjust);
    void print();
};

void HyperLogLog::insert(uchar* str, uint len) {
    uint index = BOB32(str, len, bucket_seed)%HYPERLOGLOG_HEIGHT;
    uint pos = GD_BOB128(str, len, hash_seed[index], dividend);
    sketch[index] = max(sketch[index], pos);
}

double HyperLogLog::query(double adjust) {
    double sum = 0;
    for(int i = 0; i < HYPERLOGLOG_HEIGHT; ++i) {
        sum += 1.0/sketch[i];
        //sum += (dividend-1.0)*pow(dividend/(dividend-1.0), (double)pos)/adjust;
    }
    printf("%lf\n", sum);
    return adjust*HYPERLOGLOG_HEIGHT*(dividend-1.0)*pow(dividend/(dividend-1.0), HYPERLOGLOG_HEIGHT/sum);
}

void HyperLogLog::print() {
    for(int i = 0; i < HYPERLOGLOG_HEIGHT; ++i) {
        printf("%u ", sketch[i]);
        printf("\n");
    }
}