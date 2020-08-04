#pragma once
#include "simple_fft/fft.h"
template<int S>
class delayfinder
{

    int arraySize;
    std::array<float,4*S> A;
    std::array<float,4*S> B;
    std::array<std::complex<float>,4*S> outputA;
    std::array<std::complex<float>,4*S> outputB;
    std::array<std::complex<float>,4*S> outputCorr;
    std::array<std::complex<float>,4*S> outputAlmost;
    std::array<float,4*S> output;
    bool b;
    const char * error = NULL;
    float currentmax;
    int currentmaxsample;

public:
    delayfinder()
    {
    arraySize=S;
    outputA.fill(0);
    outputB.fill(0);
    outputCorr.fill(0);
    output.fill(0);
    outputAlmost.fill(0);
    }
    inline void setAB(tapearray<float,S>&  tempA , tapearray<float,S> tempB)
    {
        A.fill(0);
        B.fill(0);
        for(int i=0;i<arraySize;i++){
            A[i]=tempA[i];
            //B[3*arraySize+i]=tempB[arraySize-1-i];
            B[i]=tempB[i];
        }

        currentmax=0;
        currentmaxsample=0;


    }
    inline void elementwisemultiply()
    {
        for(int i=0;i<4*arraySize;i++)
        {
            outputCorr[i]=(outputA[i]*conj(outputB[i]));
        }
    }
    void xcorr(tapearray<float,S>&  tempA , tapearray<float,S> tempB)
    {
        setAB(tempA,tempB);
        simple_fft::FFT(A,outputA,4*arraySize,error);
        simple_fft::FFT(B,outputB,4*arraySize,error);


        elementwisemultiply();
        simple_fft::IFFT(outputCorr,outputAlmost,4*arraySize,error);
        amplitude();


    }
    inline void amplitude(){
        for(int i=0;i<4*arraySize;i++)
        {
            output[i]=abs(outputAlmost[i]);
        }
    }
    int finddelay( tapearray<float,S>&  tempA ,
                   tapearray<float,S>& tempB)
    {
        xcorr(tempA,tempB);

        return (4*S-maxarg()+1)%(4*S);

    }
    inline int maxarg(void){
        for(int i=0;i<4*arraySize;i++)
        {
            if(currentmax<output[i]){
                currentmax=output[i];
                currentmaxsample=i+1;
            }
        }
        return currentmaxsample;
    }
    void printOutput()
    {
        for(int i=0;i<4*S;i++){
            std::cout<<output[i]<<" ";
        }
                        std::cout<<"\n";
    }
};


