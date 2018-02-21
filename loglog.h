#include "common.h"
#include "hash.h"

#define LOGLOG_HEIGHT 1024

class LogLog {
private:
    ull sketch[LOGLOG_HEIGHT];
public:
    void insert();
    void query();
};

void LogLog::insert() {

}

void LogLog::query() {

}