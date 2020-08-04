#pragma once
#include <math.h>
#include <iostream>
#define CONSTMOD 16807
//Mark Miller Random Gen Algoritm
//thanks to Robin Whittle
namespace akos{
class Random{
long unsigned int tempseed;
long unsigned int high,low;

public:
long unsigned int next_rand(){
    low=CONSTMOD * (tempseed & 0xFFFF);
    high=CONSTMOD * (tempseed >> 16);
    low+=(high & 0xFFF)<<16;
    low+=high>>15;
    if(low>0x7FFFFFFF) low -= 0x7FFFFFFF;
    tempseed=(long)low;
    return low<<15;

}
Random(){
    tempseed=1;
}
Random(long unsigned int seedin){
    if(seedin==0) seedin=1;
    tempseed=seedin;
}
void setseed(long unsigned int seedin){
    if(seedin==0) seedin=1;
    tempseed=seedin;
}
};
}
