#pragma once
#include <math.h>
#include "portaudio.h"
#include "random.h"
#include <random>
#include "filter.h"
#define MAX_ROW 30
#define MAX_COL 24

class white_noise{
    akos::Random rd;
    std::mt19937 gen;


public:
    white_noise(){
    rd.setseed(2222);
    gen.seed(rd.next_rand());

    }
    float generate(){
        std::uniform_real_distribution<float> dis(-1.0,1.0);
        return dis(gen);
    }
};

class pink_noise{
    white_noise white;
     const float b[4]={0.049922035, -0.095993537, 0.050612699, -0.004408786};
     const float a[4] = {1, -2.494956002, +2.017265875, -0.522189400};
     float x[4]={0,0,0,0};
     float y[4]={0,0,0,0};

public:
    pink_noise(void)
    {

    }
    float generate(void)
    {
    shift(white.generate(),x,4);
    shift(0,y,4);
    y[0]=b[0]*x[0]+b[1]*x[1]+b[2]*x[2]+b[3]*x[3]-a[1]*y[1]-a[2]*y[2]-a[3]*y[3];
    return 3*y[0];
    }
    void shift(float element,float * array,int size)
    {
    for(int i=0;i<size;i++){
        if(i!=size-1)
        array[size-1-i]=array[size-2-i];
        else{
           array[0]=element;
        }
    }
    }

  /*  inline float process(){
        b0 = 0.997886 * b0 + white.generate() * 0.0555179;
           b1 = 0.99332 * b1 + white.generate() * 0.0750759;
           b2 = 0.96900 * b2 + white.generate() * 0.1538520;
           b3 = 0.86650 * b3 + white.generate() * 0.3104856;
           b4 = 0.55000 * b4 + white.generate() * 0.5329522;
           b5 = -0.7616 * b5 - white.generate() * 0.0168980;
           output = b0 + b1 + b2 + b3 + b4 + b5 + b6 + white.generate() * 0.5362;
           b6 = white.generate() * 0.115926;
           return output*0.1;
}*/

};



