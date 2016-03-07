#include "MinMaxHeap.hpp"
#include "MinMaxHeap.cpp"
#include <iostream>

using namespace std;

class EvenPred: public Predicate<int> {
  bool toDelete (int a) {
    return ((a % 2) == 0);
  }
};

// i: insert, g i: getMin, g a: metMax, d i: deleteMin; d a: deleteMax, d e: deleteElems

int main () {
  MinMaxHeap<int> *heap = new MinMaxHeap<int>();
  int N;
  cin >> N;
  for (; N > 0; --N) {
    char op, sub_op;
    int elem;
    cin >> op;
    if (op == 'i') {
      cin >> elem;
      heap->insert(elem);
    }
    else if (op == 'g') {
      cin >> sub_op;
      if (sub_op == 'i') {
        cout << heap->getMin() << endl;
      }
      else if (sub_op == 'a') {
        cout << heap->getMax() << endl;
      }
    }
    else if (op == 'd') {
      cin >> sub_op;
      if (sub_op == 'i') {
        heap->deleteMin();
      }
      else if (sub_op == 'a') {
        heap->deleteMax();
      }
      else if (sub_op == 'e') {
        EvenPred obj;
        heap->deleteElems(obj);
      }
    }
  }
}