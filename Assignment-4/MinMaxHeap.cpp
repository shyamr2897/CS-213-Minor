//
//  MinMaxHeap.cpp
//  
//
//  Created by Shyam Ramamoorthy on 03/03/16.
//
//

#include "tried.hpp"
#include <cmath>

using namespace std;
template<class T>
bool Predicate<T>::toDelete (T elem){
    return false;
}

template <class T>
MinMaxHeap<T>::MinMaxHeap(){
    size = 0;
    level = 0;
}

template <class T>
int MinMaxHeap<T>::getLevel(int pos){
    int level = 0;
    int i = 2;
    while (i <= pos) {
        i = (i << 1);
        level += 1;
    }
}

template <class T>
void MinMaxHeap<T>::BubbleUpMin(int pos){
    if ((pos>>2) > 0){
        if (h[pos-1] < h[(pos>>2)-1]){
            T temp = h[pos-1];
            h[pos-1] = h[(pos>>2)-1];
            h[(pos>>2)-1] = temp;
            MinMaxHeap<T>::BubbleUpMin(pos >>2);
        }
    }
}

template <class T>
void MinMaxHeap<T>::BubbleUpMax(int pos){
    if ((pos>>2) > 0){
        if (h[(pos>>2)-1] < h[pos-1]){
            T temp = h[pos-1];
            h[pos-1] = h[(pos>>2)-1];
            h[(pos>>2)-1] = temp;
            MinMaxHeap<T>::BubbleUpMax(pos >>2);
        }
    }
}

template <class T>
void MinMaxHeap<T>::BubbleUp(int pos, int lvl){
    if (lvl % 2 == 0){
        if ((pos >> 1) == 0) return;
        else{
            if (h[(pos>>1)-1] <h[pos-1]){
                T temp = h[pos-1];
                h[pos-1] = h[(pos>>1)-1];
                h[(pos>>1)-1] = temp;
                MinMaxHeap<T>::BubbleUpMax(pos >> 1);
            }
            else MinMaxHeap<T>::BubbleUpMin(pos);
        }
    }
    
    else {
        if ((pos >> 1) == 0) return;
        else{
            if (h[pos-1] < h[(pos>>1)-1]){
                T temp = h[pos-1];
                h[pos-1] = h[(pos>>1)-1];
                h[(pos>>1)-1] = temp;
                MinMaxHeap<T>::BubbleUpMin(pos >> 1);
            }
            else MinMaxHeap<T>::BubbleUpMax(pos);
        }
    }
}

template <class T>
void MinMaxHeap<T>::insert(T elem){
    h.push_back(elem);
    size += 1;
    MinMaxHeap<T>::BubbleUp(size, level);
    if (size == (pow(2,level+1)-1)) level += 1;
}
template <class T>
void MinMaxHeap<T>::TrickleDownMin(int pos){
    int to_check[6];
    to_check[0] = (pos << 1);
    to_check[1] = (pos << 1) + 1;
    to_check[2] = (pos << 2);
    to_check[3] = (pos << 2) + 1;
    to_check[4] = (pos << 2) + 2;
    to_check[5] = (pos << 2) + 3;
    
    int min_pos = pos;
    for (int i = 0; i < 6; i++){
        if (size >= to_check[i]){
            if (h[to_check[i] - 1] < h[min_pos - 1]) min_pos = to_check[i];
        }
        else break;
    }
    
    if (min_pos == pos) return;
    
    else{
        T temp = h[pos - 1];
        h[pos - 1] = h[min_pos - 1];
        h[min_pos - 1] = temp;
        
        if (min_pos == (pos << 1) || min_pos == ((pos << 1) + 1)) return;
        else TrickleDownMin(min_pos);
    }
}

template <class T>
void MinMaxHeap<T>::TrickleDownMax(int pos){
    int to_check[6];
    to_check[0] = (pos << 1);
    to_check[1] = (pos << 1) + 1;
    to_check[2] = (pos << 2);
    to_check[3] = (pos << 2) + 1;
    to_check[4] = (pos << 2) + 2;
    to_check[5] = (pos << 2) + 3;
    
    int max_pos = pos;
    for (int i = 0; i < 6; i++){
        if (size >= to_check[i]){
            if (h[max_pos - 1] < h[to_check[i] - 1]) max_pos = to_check[i];
        }
        else break;
    }
    
    if (max_pos == pos) return;
    
    else{
        T temp = h[pos - 1];
        h[pos - 1] = h[max_pos - 1];
        h[max_pos - 1] = temp;
        
        if (max_pos == (pos << 1) || max_pos == ((pos << 1) + 1)) return;
        else TrickleDownMax(max_pos);
    }
}

template <class T>
void MinMaxHeap<T>::TrickleDown(int pos, int lvl){
    if (lvl % 2 == 0) TrickleDownMin (pos);
    else TrickleDownMax (pos);
}

template <class T>
void MinMaxHeap<T>::deleteMin(){
    if (size == 1) {
        h.erase(h.begin());
        size -= 1;
    }
    
    else{
        h[0] = h[size - 1];
        h.erase(h.begin() + size - 1);
        size -= 1;
        TrickleDown(1,0);
    }
    if (size < pow(2, level) - 1) level -= 1;
}

template <class T>
void MinMaxHeap<T>::deleteMax(){
    if (size == 1) {
        h.erase(h.begin());
        size -= 1;
    }
    
    else {
        T temp;
        if (size == 2) {
            h.erase(h.begin()+1);
            size -= 1;
        }
        else{
            if(h[1]< h[2]) {
                if(size == 2)
                h[2] = h[size - 1];
                h.erase(h.begin() + size - 1);
                size -= 1;
                if(size >= 3) TrickleDown(3,1);
            }
            else {
                h[1] = h[size - 1];
                h.erase(h.begin() + size - 1);
                size -= 1;
                TrickleDown(2,1);
            }
        }
    }
    
    if (size < pow(2, level) - 1) level -= 1;
}

template <class T>
T MinMaxHeap<T>::getMin(){
    if(size > 0) return h.front();
}

template <class T>
T MinMaxHeap<T>::getMax(){
    if (size == 1 || size == 2) return h[size-1];
    else {
        if (h[1] < h[2]) return h[2];
        else return h[1];
    }
}

template <class T>
void MinMaxHeap<T>::deleteElems(Predicate<T> predObject){
    int pos = 1;
    while (pos <= size){
        if (predObject.toDelete(h[pos - 1])){
            if (pos == size) h.erase(h.begin() + size - 1);
            else{
                h[pos - 1] = h[size - 1];
                h.erase(h.begin() + size - 1);
                TrickleDown(pos, getLevel(pos));
                pos = 1;
            }
        }
        else pos += 1;
    }
}





    


