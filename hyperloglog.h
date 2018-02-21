#include "common.h"
#include "hash.h"

#define HYPERLOGLOG_HEIGHT 1024

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
    void query();
};

void HyperLogLog::insert(uchar* str, uint len) {

}

void HyperLogLog::query() {

}