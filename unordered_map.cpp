#include<iostream>
#include<string>
#include<typeinfo>
#define q 101
using namespace std;

template <typename T1, typename T2>
struct Node {
    T1 key;
    T2 value;
    Node* next;
};

string to_string(string str) {
    return str;
}

template <typename T1>
int Hash (T1 x) {
    string a=to_string(x);
    int M = a.length();
    int d = 256;
    int h=0;
    for (int i = 0; i < M; i++)
        h = (d * h + a[i]) % q;
    return h;
}

template <typename T1, typename T2>
class HTable {
private:
    Node<T1, T2> *arr[q];
public:
    HTable<T1, T2>() {
        for(int i=0; i<q; i++)
            arr[i] = nullptr;
    }
    void insert(T1 key, T2 value);
    void erase(T1 key);
    bool find(T1 key);
    T2 operator[] (T1);
    void traverse();
};

template <typename T1, typename T2>
void HTable<T1, T2> ::traverse() {
    Node<T1, T2> *temp = new Node<T1, T2>();
    for(int i=0; i<q; i++) {
        temp=arr[i];
        if(arr[i]==nullptr)
            continue;
        while(temp) {
            cout<<temp->key<<": "<<temp->value<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
}

template <typename T1, typename T2>
void HTable<T1, T2>::insert(T1 key, T2 value) { //replace if already exists.
    if(find(key))
        erase(key);
    int h=Hash<T1>(key);
    Node<T1, T2> *temp = new Node<T1, T2>();
    temp->key=key;
    temp->value=value;
    temp->next=nullptr;
    if(arr[h]==nullptr) {
        arr[h]=temp;
    }
    else {
        temp->next=arr[h];
        arr[h]=temp;
    }
}

template <typename T1, typename T2>
void HTable<T1, T2>::erase(T1 key) {
    int h=Hash<T1>(key);    //use to_string() if key is not string
    Node<T1, T2> *temp = new Node<T1, T2>();
    temp=arr[h];
    if(arr[h]==nullptr) {
//        cout<<"Not Found"<<endl;
        return;
    }
    if(arr[h]->key==key) {
       arr[h]=arr[h]->next;
       delete temp;
       return;
    }
    Node<T1, T2> *to_del = new Node<T1, T2>();
    while(temp->next!=nullptr) {
        if(key==temp->next->key) {
//            cout<<"found"<<endl;
            to_del=temp->next;
            temp->next=temp->next->next;
            delete to_del;
            return;
        }
        temp=temp->next;
    }
//    cout<<"Not Found"<<endl;
}

template <typename T1, typename T2>
bool HTable<T1, T2>::find(T1 key) {
    int h=Hash<T1>(key);    //use to_string() if key is not string
    Node<T1, T2> *temp = new Node<T1, T2>();
    temp=arr[h];

    while(temp!=nullptr) {
        if(key==temp->key) {
            return true;
        }
        temp=temp->next;
    }
    return false;
}

template <typename T1, typename T2>
T2 HTable<T1, T2>:: operator[] (T1 key) {
    int h=Hash<T1>(key);    //use to_string() if key is not string
    Node<T1, T2> *temp = new Node<T1, T2>();
    temp=arr[h];

    while(temp!=nullptr) {
        if(key==temp->key) {
            return temp->value;
        }
        temp=temp->next;
    }
    return temp->value; //just to remove warning. control never comes here.
}

template <typename T1>
void countDistinct (T1 A[], int n, int k, int res[])
    {
        HTable<T1, int> count;
        int distinct=0, i;
        for(i=0; i<k; i++)
            if(count.find(A[i])) {
                count.insert(A[i], count[A[i]]+1);
            }
            else {
                count.insert(A[i], 1);
                distinct+=1;
            }
        res[0]=distinct;
        int rem=0;
        while(i<n) {
            if(!count.find(A[i])) {
                count.insert(A[i],1);
                distinct++;
            }
            else {
                count.insert(A[i], count[A[i]]+1);
            }
            if(count[A[rem]]==1) {
                count.erase(A[rem]);
                distinct--;
            }
            else {
                count.insert(A[rem], count[A[rem]]-1);
            }
            i++;
            rem++;
            res[rem]=distinct;
        }
    res[++rem]=-1;
}

int main () {
    string a[]={"gargi", "bhairavi", "gargi", "stuti", "angel", "gargi", "stuti"};
    int ans[100];
    countDistinct<string>(a, 7, 4, ans);
    int i=0;
    while(ans[i]!=-1) {
        cout<<ans[i]<<" ";
        i++;
    }
}

