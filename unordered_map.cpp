#include<iostream>
#include<string>
#include<typeinfo>
#define q 3
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
        while(temp) {
            cout<<temp->key<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
}

template <typename T1, typename T2>
void HTable<T1, T2>::insert(T1 key, T2 value) {
    int h=Hash<T1>(key);    //use to_string() if key is not string
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
    cout << "Hash value :" << h << endl;
}

template <typename T1, typename T2>
void HTable<T1, T2>::erase(T1 key) {
    int h=Hash<T1>(key);    //use to_string() if key is not string
    Node<T1, T2> *temp = new Node<T1, T2>();
    temp=arr[h];
    if(arr[h]==nullptr) {
        cout<<"Not Found"<<endl;
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
            cout<<"found"<<endl;
            to_del=temp->next;
            temp->next=temp->next->next;
            delete to_del;
            return;
        }
        temp=temp->next;
    }
    cout<<"Not Found"<<endl;
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
}

int main () {
    int n;
    double key;
    HTable<double, double> h;
    double value;
    cin>>n;
    //HTable<string, int> h;
    //h.erase("gargi");
    for(int i=0; i<n; i++) {
//        cin.ignore();
  //      getline(cin, key);
        cin >> key;
        cin>>value;
        h.insert(key, value);
    }
    //h.erase("gargi");
    //h.erase("gargi");
    //cout<<h.find("gargi");
    //h.insert("gargi", 2);
    //cout<<h.find("gargi");
    //h.erase("gargi");
    //cout<<h.find("gargi");
    h.traverse();
    int k; cin >> k;
    for(int i =0; i < k; i++){
        double inp;
        cin >> inp;
        cout << h[inp] << endl;
    }
}
