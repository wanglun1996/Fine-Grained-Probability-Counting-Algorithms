#include "common.h"
#include "hash.h"

#define FM_HEIGHT 64
#define FM_WIDTH 64

class FM {
private:
    uint sketch[FM_HEIGHT][FM_WIDTH];
    uint hash_seed[FM_HEIGHT];
    uint dividend;
    set<string> validator[FM_HEIGHT];
public:
    FM(uint dividend):dividend(dividend){
        memset(sketch, 0, sizeof(sketch)); 
        for (int i = 0; i < FM_HEIGHT; ++i) 
            hash_seed[i]=rand()%50; 
    }
    void insert(uchar* str, uint len);
    double query(double adjust);
    void print();
};

void FM::insert(uchar* str, uint len) {
    for(int i = 0; i < FM_HEIGHT; ++i) {
        uint pos = GD_BOB128(str, len, hash_seed[i], dividend);
        //++sketch[i][pos];
        if(validator[i].find(string((char*)str, len))==validator[i].end()) {
            ++sketch[i][pos];
            validator[i].insert(string((char*)str, len));
        }
    }
}

// Now only apply for dividend = 2
// later version will be updated after mathematical derivation
double FM::query(double adjust) {
    double sum = 0;
    for(int i = 0; i < FM_HEIGHT; ++i) {
        uint pos = 0;
        for(; pos<FM_WIDTH && sketch[i][pos]; ++pos);
        sum += (dividend-1.0)*pow(dividend/(dividend-1.0), (double)pos)/adjust;
    }
    return sum/FM_HEIGHT;
}

void FM::print() {
    for(int i = 0; i < FM_HEIGHT; ++i) {
        for(int j = 0; j < FM_WIDTH; ++j) {
            printf("%d ", sketch[i][j]);
        }
        printf("\n");
    }
}