#include <iostream>
using namespace std;

template<typename T>
class Container{
private:
    T* arr;
    unsigned int sz;
    unsigned int buffer_size;
    
    void increase_buffer();
    
public:
    Container();
    ~Container();
    
    T operator[](int);
    unsigned int size();
    
    bool find(T);
    void insert(T);
    void remove_last();
};

template<typename T>
Container<T>::Container(){
    sz = 0;
    buffer_size = 10;
    arr = new T[buffer_size];
}

template<typename T>
Container<T>::~Container(){
    sz = 0;
    buffer_size = 0;
    delete[] arr;
}

template<typename T>
unsigned int Container<T>::size(){
    cout << sz << endl;
}

template<typename T>
void Container<T>::remove_last(){
    /*
        Insert code here.
    */
}

template<typename T>
bool Container<T>::find(T val){
    /*
        Insert code here.
    */
}
    
template<typename T>
void Container<T>::increase_buffer(){
    /*
        Insert code here.
        Ensure that previous buffer is properly deleted.
    */
}

template<typename T>
void Container<T>::insert(T val){
    if (sz == buffer_size){
        increase_buffer();
    }
    
    arr[sz] = val;
    sz++;
}

template<typename T>
T Container<T>::operator[](int idx){
    return arr[idx];
}

int main(){
    Container<string> C;
    C.insert("string");
}
