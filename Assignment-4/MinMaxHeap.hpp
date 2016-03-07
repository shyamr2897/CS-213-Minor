//
//  MinMaxHeap.hpp
//  
//
//  Created by Shyam Ramamoorthy on 03/03/16.
//
//

#ifndef tried_hpp
#define tried_hpp

#include <iostream>

#include <vector>

using namespace std;

template<class T>
class Predicate{
private:
public:
    virtual bool toDelete (T elem);
};

template<class T>
class MinMaxHeap{
private:
    vector<T> h; //min-max heap
    int size;  //number of elements in the min-max heap
    int level; //level of the next available leaf
public:
    MinMaxHeap();
    int getLevel(int pos);
    void BubbleUpMin(int pos);
    void BubbleUpMax(int pos);
    void BubbleUp(int pos, int lvl);
    void insert(T elem);
    void TrickleDownMin(int pos);
    void TrickleDownMax(int pos);
    void TrickleDown(int pos, int lvl);
    void deleteMin();
    void deleteMax();
    T getMin();
    T getMax();
    void deleteElems(Predicate<T> predObject);
};

#endif /* tried_hpp */
