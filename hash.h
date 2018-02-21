#include "common.h"

#ifndef HASH_H
#define HASH_H

uint big_prime[50] = {
	20177, 20183, 20201, 20219, 20231, 20233, 20249, 20261, 20269, 20287,
	20297, 20323, 20327, 20333, 20341, 20347, 20353, 20357, 20359, 20369,
	20389, 20393, 20399, 20407, 20411, 20431, 20441, 20443, 20477, 20479,
	20483, 20507, 20509, 20521, 20533, 20543, 20549, 20551, 20563, 20593,
	20599, 20611, 20627, 20639, 20641, 20663, 20681, 20693, 20707, 20717
};

#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

#define mix64(a,b,c) \
{  \
  a -= b; a -= c; a ^= (c>>43); \
  b -= c; b -= a; b ^= (a<<9); \
  c -= a; c -= b; c ^= (b>>8); \
  a -= b; a -= c; a ^= (c>>38); \
  b -= c; b -= a; b ^= (a<<23); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>35); \
  b -= c; b -= a; b ^= (a<<49); \
  c -= a; c -= b; c ^= (b>>11); \
  a -= b; a -= c; a ^= (c>>12); \
  b -= c; b -= a; b ^= (a<<18); \
  c -= a; c -= b; c ^= (b>>22); \
}

uint BOB32(uchar* str, uint len, uint ini){
	//register a,b,c,len;
	uint a,b,c;
	/* Set up the internal state */
	//len = length;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
	c = big_prime[ini];         /* the previous hash value */

	/*---------------------------------------- handle most of the key */
	a += (str[0] +((int)str[1]<<8) +((int)str[2]<<16) +((int)str[3]<<24));
	b += (str[4] +((int)str[5]<<8) +((int)str[6]<<16) +((int)str[7]<<24));
	c += (str[8] +((int)str[9]<<8) +((int)str[10]<<16)+((int)str[11]<<24));
	mix(a,b,c);
	str += 12; len -= 12;

	/*------------------------------------- handle the last 11 bytes */
	c += len;
	a += str[0];
	mix(a,b,c);
	/*-------------------------------------------- report the result */
	return c;
}

uint GD_BOB32(uchar* str, uint len, uint ini, uint dividend) {
  uint uniform_hash = BOB32(str, len, ini);
  uint result = 0;
  while(uniform_hash%dividend) {
    ++result;
    uniform_hash /= dividend;
  }
  return result;
}

ull Murmur64 (uchar* str, uint len, uint ini)  
{  
	  uint seed = big_prime[ini];
    uint m = 0x5bd1e995;  
    uint r = 24;  
   
    uint h1 = seed ^ len;  
    uint h2 = 0;    
   
    while(len >= 8)  
    {  
        uint k1 = *str++;  
        k1 *= m; k1 ^= k1 >> r; k1 *= m;  
        h1 *= m; h1 ^= k1;  
        len -= 4;  
   
        uint k2 = *str++;  
        k2 *= m; k2 ^= k2 >> r; k2 *= m;  
        h2 *= m; h2 ^= k2;  
        len -= 4;  
    }  
   
    if(len >= 4)  
    {  
        uint k1 = *str++;  
        k1 *= m; k1 ^= k1 >> r; k1 *= m;  
        h1 *= m; h1 ^= k1;  
        len -= 4;  
    }  
     
    h2 ^= ((unsigned char*)str)[0];  
    h2 *= m;  
   
    h1 ^= h2 >> 18; h1 *= m;  
    h2 ^= h1 >> 22; h2 *= m;  
    h1 ^= h2 >> 17; h1 *= m;  
    h2 ^= h1 >> 19; h2 *= m;  
   
    ull h = h1;  
   
    h = (h << 32) | h2;  
   
    return h;  
}

uint GD_Murmur64(uchar* str, uint len, uint ini, uint dividend) {
  uint uniform_hash = Murmur64(str, len, ini);
  uint result = 0;
  while(uniform_hash%dividend) {
    ++result;
    uniform_hash /= dividend;
  }
  return result;
}

uint GD_Murmur128(uchar* str, uint len, uint ini, uint dividend) {
  uint uniform_hash1 = Murmur64(str, len, ini);
  uint uniform_hash2 = Murmur64(str, len, (ini+1)%50);
  uint result = 0;
  while(uniform_hash1%dividend) {
    ++result;
    uniform_hash1 /= dividend;
  }
  if(result>=(64/dividend)) {
    while(uniform_hash2%dividend) {
      ++result;
      uniform_hash2 /= dividend;
    }
  }
  return result;  
}

#endif