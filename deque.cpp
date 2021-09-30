#include<iostream>
using namespace std;

template <class T>
class deque {
private:
    T *arr;
    int capacity;
    int size;
    int head, tail;
public:
    deque() {arr = new T[100]; capacity=100; size=0; head=tail=50;}
    deque(int n, int d) {
        if(n<100) {
            arr = new T[100]; capacity=100;
        }
        else {
            arr = new T[n+2];
            capacity=n+2;
        }
        size = n;
        int x=0;
        head=tail=(capacity)/2;
        for(int i=0; i<n; i++)
            if(x==0)
                arr[--head];
            else
                arr[tail++];
            x=(x+1)%2;
    }
     push_back(x) - append data x at the end. -O(1)
    pop_back() - erase data at the end. -O(1)
    push_front(x)
    pop_front()
    front()
    back()
    empty();
    size();
    resize(x, d);
    clear();
    D[n];
