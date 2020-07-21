#pragma once
#include <iostream>
template <class T>
class tapearray{
    T * data;
    int Index;
    int size;
public:
    tapearray(int s){
        data=new T[s];
        size=s;
        Index=size-1;
        for(int i=0;i<size;i++)
        {
            data[i]=0;
        }
    }
    ~tapearray(){
        delete [] data;
    }
    int& operator[] (const int num){
        return data[calcIndex(Index+num+1)];

    }
    void shift(const int num){
        data[Index]=num;
        if(Index>0)
            Index--;
        else
            Index=size-1;

    }
    inline int calcIndex(const int num){
        return (num)%size;
    }
    void printArray(){
        for(int i=0;i<size;i++){
            std::cout<<data[i]<<" ";

        }
        std::cout<<"\n";
    }
    int getSize(void){
        return size;
    }
    void printTape(void){
        for(int i=0;i<size;i++){
            std::cout<<(*this)[i]<<" ";

        }
        std::cout<<"\n";

    }

};

