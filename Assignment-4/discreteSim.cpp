//
//  discreteSim.cpp
//
//
//  Created by Shyam Ramamoorthy on 05/03/16.
//
//

#include <iostream>
#include "minMaxHeap.hpp"

using namespace std;

struct operation{
    int id, time, op, strength, period;
    operation(int a, int b, int c, int d, int e){
        id = a;
        time = b;
        op = c;  //op = 1 for death, op = 2 for infection, op = 3 for division
        strength = d;
        period = e;
    }
    
    bool operator< (operation o){
        if (this->time < o.time) return true;
        else if (this->time > o.time) return false;
        
        if (this->op < o.op) return true;
        else if (this->op > o.op) return false;
        
        if (this->id < o.id) return true;
        else if (this->id > o.id) return false;
        
        return true;
    }
};

class InfectionPred: public Predicate<operation>{
private:
    int id, time;
public:
    bool toDelete (operation a){
        if (a.id == this->id){
            if (a.time >= this->time) return true;
        }
        return false;
    }
    void set_vars(int id, int time){
        this->id = id;
        this->time = time;
    }
};

int main(){
    MinMaxHeap<operation> *heap = new MinMaxHeap<operation>();
    int N;
    cin >> N;
    vector<int> str, abc;
    
    for (int i = 0; i < N; i ++){
        int strength;
        cin >> strength;
        str.push_back(strength);
        abc.push_back(strength);
        int n = ((i + strength)*29)%37 + 7;
        operation *d = new operation (i, n, 3, strength, n);
        heap -> insert(*d);
    }
    
    int M;
    cin >> M;
    InfectionPred inf_obj;
    for (int i = 0; i < M; i++){
        int id;
        cin >> id;
        int infectTime;
        cin >> infectTime;
        
        inf_obj.set_vars(id, infectTime);
        heap->deleteElems(inf_obj);
        operation *d = new operation (id, infectTime, 2, -1, -1);
        heap->insert(*d);
    }
    
    int T;
    cin >> T;
    
    int population = N;
    int next = N;
    
    for (int i = 0; i <= T; i ++){
        while ((heap->getMin()).time == i){
            int cur_op = (heap->getMin()).op;
            int cur_id = (heap->getMin()).id;
            
            if (cur_op == 1){
                cout << "d " << cur_id << " " << i << endl;
                heap->deleteMin();
            }
            
            if (cur_op == 2){
                operation *d = new operation (cur_id, i + str[cur_id], 1, -1, -1);
                inf_obj.set_vars(cur_id, i);
                heap->deleteMin();
                heap->deleteElems(inf_obj);
                heap->insert(*d);
            }
            
            if (cur_op == 3){
                if ((heap->getMin()).strength > 0){
                    operation *d = new operation(cur_id, i + (heap->getMin()).period, 3,
                                                 (heap->getMin()).strength-1, (heap->getMin()).period);
                    int n = ((next + abc[cur_id])*29)%37 + 7;
                    operation *e = new operation(next, i + n, 3, abc[cur_id], n);
                    str.push_back(abc[cur_id]);
                    abc.push_back(abc[cur_id]);
                    
                    str[cur_id] -= 1;
                    heap->deleteMin();
                    heap->insert(*d);
                    heap->insert(*e);
                    cout << "b " << next << " " << i << endl;
                    next += 1;
                }
                
                else{
                    operation *d = new operation(cur_id, i + (heap->getMin()).period, 1, -1, -1);
                    heap->deleteMin();
                    heap->insert(*d);
                }
            }
        }        
    }
}


