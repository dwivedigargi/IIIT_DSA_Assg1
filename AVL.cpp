#include<iostream>
using namespace std;

template <typename T>
class node {
public:
    node *parent;
    node *left;
    node *right;
    T value;
    int Count;
    int height;
    int weight;
    node() {parent=left=right=nullptr; Count=1; height=0; weight=1;}
    node(T val) {parent=left=right=nullptr; Count=1; height=0; value=val; weight=1;}
};

template <typename T>
class Comp {
public:
    int operator()(T t1, T t2) {
        if(t1<t2)
            return -1;
        else if (t1>t2)
            return 1;
        else
            return 0;
    }
};

template <typename T, typename comp=Comp<T>>
class AVL {
private:
public:
    node<T>* root;
    AVL() {root=nullptr;}
    void displayTree(node<T>*);
    node<T>* leftRotate(node<T>*);
    node<T>* rightRotate(node<T>*);
    void insert(T val, comp c=comp());
    void del(T val, node<T>* roo, comp c=comp());
    bool search(T val, comp c=comp());
    int count_occur(T val, comp c=comp());
    T LB(T val, bool &exists, comp c=comp());
    T upperbound(T val, bool &exists, comp c=comp());
    T lowerbound(T val, bool &exists, comp c=comp());
    T closestTo(T val, comp c=comp());
    T klargest(node<T>* r, int k);
    int inRange(T low, T high, comp c=comp());
};

template <typename T, typename comp>
T AVL<T,comp>::klargest(node<T>* r, int k) {
    if(W(r->right)==k-1)
        return r->value;
    else if(W(r->right)>k-1)
        return klargest(r->right, k);
    else
        return klargest(r->left, k-W(r->right)-1);
}

template <typename T, typename comp>
int AVL<T, comp>::inRange(T low, T high, comp c) {
    bool exists1, exists2;
    T lb=lowerbound(low, exists1);
    T ub=lowerbound(high, exists2);

    if(c(lb, high)==1)
        return 0;

    char *arr = new char[W(root)];
    for(int i=0; i<W(root); i++)
        arr[i]='f';

    int lesserNodes = 0, greaterNodes = 0;
    node<T>* trav = root;
    int i=0;
    while(trav!=nullptr && exists1) {
        if(c(trav->value, lb)==-1) {
            trav=trav->right;
            arr[i++]='r';
        }
        else if(c(trav->value, lb)==1) {
            trav=trav->left;
            arr[i++]='l';
        }
        else {
            lesserNodes = W(trav->left);
            break;
        }
    }
    for(int i=0; i<W(root); i++)
        cout<<arr[i]<<endl;
    i=0;
    int foundBranch = -1;
    trav = root;
    while(trav!=nullptr && exists2) {
        if(c(trav->value, ub)==-1) {
            if( foundBranch==-1 && arr[i++]!='r') {
                foundBranch = W(trav);
            }
            trav=trav->right;
        }
        else if(c(trav->value, ub)==1) {
            if(foundBranch==-1 && arr[i++]!='l') {
                foundBranch = W(trav);
            }
            trav=trav->left;
        }
        else {
            if(foundBranch==-1)
                foundBranch = W(trav);
            greaterNodes = W(trav->right);
            break;
        }
    }
    if(foundBranch==-1)
        return 0;
    return foundBranch-lesserNodes-greaterNodes;
}

template <typename T, typename comp>
node<T>* AVL<T, comp>::rightRotate(node<T>* y) {
    node<T>* x=y->left;
    node<T>* t=x->right;

    x->parent=y->parent;
    x->right=y;
    y->parent=x;
    y->left=t;
    if(t!=nullptr)
        t->parent=y;

    y->height = max(H(y->left), H(y->right))+1;
    y->weight = W(y->left) + W(y->right) + 1;
    x->height = max(H(x->left), H(x->right))+1;
    x->weight = W(x->left) + W(x->right) + 1;

    return x;
}

template <typename T, typename comp>
node<T>* AVL<T, comp>::leftRotate(node<T>* x) {
    node<T>* y=x->right;
    node<T>* t=y->left;

    y->parent=x->parent;
    y->left = x;
    x->parent=y;
    x->right=t;
    if(t!=nullptr)
        t->parent = x;

    x->height = max(H(x->left), H(x->right))+1;
    x->weight = W(x->left) + W(x->right) + 1;
    y->height = max(H(y->left), H(y->right))+1;
    y->weight = W(y->left) + W(y->right) + 1;

    return y;
}

template<typename T>
int H(node<T>* n) {
    if(n==nullptr)
        return -1;
    else
        return n->height;
}

template<typename T>
int W(node<T>* n) {
    if(n==nullptr)
        return 0;
    else
        return n->weight;
}

template<typename T>
int getBF (node<T>* n) {
    return H(n->left)-H(n->right);
}

template<typename T>
node<T>* minNode (node<T>* n) {
    node<T>* temp=new node<T>();
    temp=n;
    if(n==nullptr)
        return n;
    while(n->left!=nullptr)
        n=n->left;
    return n;
}

template <typename T, typename comp>
void AVL<T, comp>::insert(T to_be_inserted, comp c)
{
    node<T>* temp = new node<T>(to_be_inserted);
    node<T>* r = new node<T>();
    r=root;
    if(r == nullptr)
    {
        r = temp;
        root = r;
        return;
    }
    while(true)
    {
        if(c(temp->value, r->value)==1)
            if(r->right == nullptr)
            {
                temp->parent = r;
                r->right = temp;
                break;
            }
            else
                r = r->right;
        else if(c(temp->value, r->value)==-1)
            if(r->left == nullptr)
            {
                temp->parent = r;
                r->left = temp;
                break;
            }
            else
                r = r->left;
        else {
            r->Count+=1;
            r->weight+=1;
            return;
        }
    }

    node<T>* trav = new node<T>();
    trav = r;
    while(trav!=nullptr) {
        trav->height = max(H<T>(trav->left), H<T>(trav->right)) + 1;
        trav->weight = W(trav->left) + W(trav->right) + 1;
        trav=trav->parent;
    }

    int bf = getBF(r);
    while(bf>=-1 && bf<=1 && r->parent!=nullptr) {
        bf=getBF(r->parent);
        r=r->parent;
    }

    if(bf>1 &&  c(to_be_inserted, r->left->value)==-1) {
        if(r->parent==nullptr)
            root=rightRotate(r);
        else if (c(r->value, r->parent->value)==-1)
            r->parent->left=rightRotate(r);
        else if (c(r->value, r->parent->value)==1)
            r->parent->right=rightRotate(r);
        else
            cout<<"Should not come here! 1"<<endl;
    }

    else if(bf<-1 && c(to_be_inserted, r->right->value)==1) {
        if(r->parent==nullptr)
            root=leftRotate(r);
        else if (c(r->value, r->parent->value)==-1)
            r->parent->left=leftRotate(r);
        else if (c(r->value, r->parent->value)==1)
            r->parent->right=leftRotate(r);
        else
            cout<<"Should not come here! 2"<<endl;
    }

    else if(bf>1 && c(to_be_inserted, r->left->value)==1) {
        r->left = leftRotate(r->left);
        if(r->parent==nullptr)
            root=rightRotate(r);
        else if(c(r->value, r->parent->value)==-1)
            r->parent->left=rightRotate(r);
        else if (c(r->value, r->parent->value)==1)
            r->parent->right=rightRotate(r);
        else
            cout<<"Should not come here! 3"<<endl;
    }

    else if(bf<-1 && c(to_be_inserted, r->right->value)==-1) {
        r->right = rightRotate(r->right);
        if(r->parent==nullptr)
            root=leftRotate(r);
        else if(c(r->value, r->parent->value)==-1)
            r->parent->left=leftRotate(r);
        else if (c(r->value, r->parent->value)==1)
            r->parent->right=leftRotate(r);
        else
            cout<<"Should not come here! 4"<<endl;
    }

    else
        return;

    trav = r;
    while(trav!=nullptr) {
        trav->height = max(H<T>(trav->left), H<T>(trav->right)) + 1;
        trav->weight = W(trav->left) + W(trav->right) + 1;
        trav=trav->parent;
    }
    return;
}

template <typename T, typename comp>
void AVL<T,comp>::del(T val, node<T>* roo, comp c) {
    node<T>* r = new node<T>(); //regulates height

//    cout<<"Deleting "<<val<<endl;
    if(roo==nullptr) {
        return;
    }

    node<T>* trav=new node<T>();
    trav=roo;
    while(trav!=nullptr && c(trav->value, val)!=0) {
        if(c(trav->value, val)==-1)
            trav=trav->right;
        else if(c(trav->value, val)==1)
            trav=trav->left;
    }

    if(trav==nullptr)
        return;
    else if(trav->Count>1) {
        trav->Count--;
        trav->weight--;
        return;
    }
    else if(trav->left==nullptr || trav->right==nullptr) {  //has at most 1 child
        node<T>* temp = trav->left ? trav->left : trav->right;

        if (temp==nullptr) {    //no child
//            cout<<"Came here "<<trav->value<<(trav->left==nullptr)<<(trav->right==nullptr)<<endl;
            temp = trav;
            if(trav->parent!=nullptr && trav == trav->parent->left)
                trav->parent->left = nullptr;
            else if (trav->parent!=nullptr && trav == trav->parent->right)
                trav->parent->right = nullptr;
        }
        else {  //one child
            temp->parent=trav->parent;
            if(temp->parent!=nullptr) {
                if(c(temp->value, temp->parent->value)==-1)
                    temp->parent->left=temp;
                else
                    temp->parent->right=temp;
            }
            node<T>* swapp=new node<T>();
            swapp=temp;
            temp=trav;
            trav=swapp;
        }
        r=temp->parent;
        delete temp;
    }
    else {  //if 2 children
        node<T>* temp=new node<T>();
        temp = minNode<T>(trav->right);
        if(temp==nullptr) {
            cout<<"temp shouldn't be null since 1 child handled before";
            return;
        }
        T swapp;
        int cswap;
        swapp = temp->value;
        cswap = temp->Count;
        temp->value=trav->value;
        temp->Count=trav->Count;
        trav->value=swapp;
        trav->Count=cswap;
        r=trav->parent;
        del(val, temp);
    }

    node<T>* tobal = new node<T>();
    tobal = r;
    while(r!=nullptr) {
        r->height = max(H<T>(r->left), H<T>(r->right)) + 1;
        r->weight = W(r->left) + W(r->right) + 1;
//        cout<<r->value<<": "<<H<T>(r->left)<<", "<<H<T>(r->right)<<", "<<r->height<<endl;
//        cout<<r->value<<" "<<(r->parent==nullptr)<<endl;
        r=r->parent;
    }

    if (tobal == NULL) {
//        cout<<"Null tha"<<endl;
        return;
    }

    int bf = getBF(tobal);
    while(bf>=-1 && bf<=1 && tobal->parent!=nullptr) {
        bf=getBF(tobal->parent);
        tobal=tobal->parent;
    }

    if (bf > 1 && getBF(tobal->left) >= 0) {
        if(tobal->parent==nullptr)
            root=rightRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==-1)
            tobal->parent->left=rightRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==1)
            tobal->parent->right=rightRotate(tobal);
        else
            cout<<"Should not come here! del1"<<endl;
//        tobal = rightRotate(tobal);
    }

    else if (bf > 1 && getBF(tobal->left) < 0)
    {
        tobal->left = leftRotate(tobal->left);
        if(tobal->parent==nullptr)
            root=rightRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==-1)
            tobal->parent->left=rightRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==1)
            tobal->parent->right=rightRotate(tobal);
        else
            cout<<"Should not come here! del2"<<endl;
//        tobal = rightRotate(tobal);
    }

    else if (bf < -1 && getBF(tobal->right) <= 0) {
        if(tobal->parent==nullptr)
            root=leftRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==-1)
            tobal->parent->left=leftRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==1)
            tobal->parent->right=leftRotate(tobal);
        else
            cout<<"Should not come here! del3"<<endl;
//        tobal = leftRotate(tobal);
    }

    else if (bf < -1 && getBF(tobal->right) > 0)
    {
        tobal->right = rightRotate(tobal->right);
        if(tobal->parent==nullptr)
            root=leftRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==-1)
            tobal->parent->left=leftRotate(tobal);
        else if (c(tobal->value, tobal->parent->value)==1)
            tobal->parent->right=leftRotate(tobal);
        else
            cout<<"Should not come here! del4"<<endl;
//        tobal = leftRotate(tobal);
    }

    while(tobal!=nullptr) {
        tobal->height = max(H<T>(tobal->left), H<T>(tobal->right)) + 1;
        tobal->weight = W(tobal->left) + W(tobal->right) + 1;
        tobal=tobal->parent;
    }
    return;
}

template <typename T, typename comp>
void AVL<T, comp>::displayTree(node<T>* root)
{
    if(root==nullptr)
        return;
    if(root->left != nullptr)
        displayTree(root->left);
    for(int i=0; i<root->Count; i++) {
        cout<<root->value<<": "<<root->height<<", "<<root->weight<<endl;
    }
    if(root->right != nullptr)
        displayTree(root->right);
}

template <typename T, typename comp>
bool AVL<T,comp>::search(T val, comp c) {
    node<T>* trav = root;
    while(trav!=nullptr) {
        if(c(trav->value, val)==-1)
            trav=trav->right;
        else if(c(trav->value, val)==1)
            trav=trav->left;
        else
            return true;
    }
    return false;
}

template <typename T, typename comp>
int AVL<T,comp>::count_occur(T val, comp c) {
    node<T>* trav = root;
    while(trav!=nullptr) {
        if(c(trav->value, val)==-1)
            trav=trav->right;
        else if(c(trav->value, val)==1)
            trav=trav->left;
        else
            return trav->Count;
    }
    return 0;
}

template <typename T, typename comp>
T AVL<T,comp>::LB(T val, bool &exists, comp c) {
    node<T>* trav=root;
    T lb;
    int flag = 0;
    exists = true;
    while(trav) {
        if(c(trav->value, val)==0)
            return trav->value;
        if(c(val, trav->value)==1) {
            lb=trav->value;
            flag = 1;
            trav = trav->right;
        }
        else
            trav = trav->left;
    }
    if (!flag)
        exists=false;
    return lb;
}

template <typename T, typename comp>
T AVL<T,comp>::upperbound(T val, bool &exists, comp c) {
    node<T>* trav = root;
    T ub;
    exists = true;
    int flag = 0;
    while (trav) {
        if(c(val, trav->value)>=0)
            trav=trav->right;

        else {
            ub = trav->value;
            trav=trav->left;
            flag = 1;
        }
    }

    if (!flag)
        exists = false;
    return ub;
}

template <typename T, typename comp>
T AVL<T,comp>::lowerbound(T val, bool &exists, comp c) {
    node<T>* trav = root;
    T ub;
    exists = true;
    int flag = 0;
    while (trav) {
        if(c(val, trav->value)==1)
            trav=trav->right;

        else {
            ub = trav->value;
            trav=trav->left;
            flag = 1;
        }
    }
    if (!flag)
        exists = false;
    return ub;
}

template <typename T, typename comp>
T AVL<T,comp>::closestTo(T val, comp c) {
    bool exists1, exists2;
    T lb = LB(val, exists1, c);
    T ub = upperbound(val, exists2, c);
    if(exists1 && exists2)
        if(c(val-lb,ub-val)==-1)
            return lb;
        else
            return ub;
    else if(exists1)
        return lb;
    else
        return ub;
}

class test {
public:
    int x;
    test() {x=0;}
    test(int v) {x=v;}
    friend ostream& operator<<(ostream& os, const test& dt);
};

ostream& operator<<(ostream& os, const test& dt)
{
    os << dt.x;
    return os;
}

class compare {
public:
    int operator()(test t1, test t2) {
        if(t1.x<t2.x)
            return -1;
        else if (t1.x>t2.x)
            return 1;
        else
            return 0;
    }
};

int main() {
    AVL<test, compare> a;
    bool exists;
    test t1(2);
    test t2(4);
    test t3(1);
    test t4(7);
    test t5(5);
    test t6(3);
    a.insert(t1);
    a.insert(t2);
    a.insert(t3);
    a.insert(t4);
    a.insert(t5);
    a.insert(t5);
    cout<<a.klargest(a.root, 5);
//    a.del(t3, a.root);
//    a.insert(t8);
//    a.insert(t9);
//    a.insert(t10);
//    a.insert(t11);
//    a.displayTree(a.root);
}
