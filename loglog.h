#include "common.h"
#include "hash.h"

#define LOGLOG_HEIGHT 128

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
    void query();
};

void LogLog::insert(uchar* str, uint len) {

}

void LogLog::query() {

}