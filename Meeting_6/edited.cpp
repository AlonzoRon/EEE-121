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
    // cout << sz << endl;
    return sz;
}

template<typename T>
void Container<T>::remove_last(){
    sz -= 1;
}

template<typename T>
bool Container<T>::find(T val){
    bool checker = false;
    for(int i = 0; i < sz; i++){
        if(arr[i] == val) checker = true;
    }
    return checker;
}
    
template<typename T>
void Container<T>::increase_buffer(){
    buffer_size++;

    T* arr_temp = new T[buffer_size];

    for(int i = 0; i < buffer_size; i++){
        arr_temp[i] = arr[i];    
    }

    // *arr_temp = *arr;

    delete[] arr;
    arr = new T[buffer_size];

    for(int i = 0; i < buffer_size; i++){
        arr[i] = arr_temp[i];    
    }

    // *arr = *arr_temp; 
    delete[] arr_temp;
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
    C.insert("string1");
    C.insert("string2");
    C.insert("string3");
    C.insert("string4");
    cout << C.size() << endl;
    
    C.remove_last();
    C.insert("stringnew");
    C.insert("stringnew");

    for(int i = 0; i < C.size(); i++){
        cout << C[i] << " ";
    }
    
    if (C.find("string2")) cout << "found" << endl;
    else cout << "not" << endl;
    if (C.find("string1")) cout << "found" << endl;
}
