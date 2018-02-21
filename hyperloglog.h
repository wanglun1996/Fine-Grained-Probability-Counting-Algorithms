#include "common.h"
#include "hash.h"

#define HYPERLOGLOG_HEIGHT 1024

class HyperLogLog {
private:
    ull sketch[HYPERLOGLOG_HEIGHT];
public:
    void insert();
    void query();
};

void HyperLogLog::insert() {

}

void HyperLogLog::query() {

}