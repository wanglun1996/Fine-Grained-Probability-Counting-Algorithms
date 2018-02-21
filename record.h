#include "common.h"
#include "hash.h"

class Record {
private:
    map<string, uint> record;
public:
    void insert(string str);
    uint query();
};

void Record::insert(string str) {
    map<string, uint>::iterator iter = record.find(str);
    if(iter!=record.end()) {
        ++iter->second;
    }
    else {
        record.insert(pair<string, uint>(str, 1));
    }
}

uint Record::query() {
    return record.size();
}