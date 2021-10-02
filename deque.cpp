#include<iostream>
#include "unordered_map.cpp"
# define ll long long
using namespace std;

template <class T>
class deque {
private:
    HTable<int, T> h;
    int min_index, curr_size;
public:
    deque() {curr_size=0; min_index=0;}
    deque(int n, T d) {
        for(int i=0; i<n; i++)
            h.insert(i, d);
        min_index = 0;
        curr_size = n;
    }
    void push_back(T x) {
        h.insert(min_index+curr_size, x);
        curr_size++;
    }
    void pop_back() {
        curr_size--;
        h.erase(min_index+curr_size);
    }
    void push_front(T x) {
        curr_size++;
        min_index--;
        h.insert(min_index, x);
    }
    void pop_front() {
        curr_size--;
        h.erase(min_index);
        min_index++;
    }
    T front() {
        return h[min_index];
    }
    T back() {
        return h[min_index+curr_size-1];
    }
    bool empty() {
        if(curr_size==0)
            return true;
        return false;
    }
    int size() {
        return curr_size;
    }
    void resize(int x, T d) {
        int temp_size=curr_size;
        if(x<=curr_size)
            for(int i=0; i<temp_size-x; i++)
                pop_back();
        else {
            for(int i=0; i<x-temp_size; i++)
                push_back(d);
        }
        curr_size = x;
    }
    void clear() {
        min_index=0;
        curr_size=0;
    }
    void dispQ() {
        for(int i=min_index; i<min_index+curr_size; i++)
            cout<<h[i]<<" ";
    }
};


//remove main from unordered map
int main () {
    deque<ll> d;
    for( ll i = 1; i <4; i++){
        d.push_back(i);
    }
    //d.push_back(3);
    //d.push_back(6);
    d.pop_front();
    d.pop_back();
    //cout<<d.size()<<endl;
    //cout<<d.back()<<endl;
    //cout << d.front() << endl;
    //cout<<d.size()<<endl;
    d.resize(7, 5);
    d.clear();
    d.dispQ();
}
